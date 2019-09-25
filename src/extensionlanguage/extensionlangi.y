%token STRUCTPTR BITLEFT LE BITRIGHT GE LOGAND LOGOR LOGNAND LOGNOR LOGIFF LOGXOR EQ APPROX BITNOR NE ASSIGN NULLTOK HUP SWITCH CASE IF THEN ELSE WHILE UNTIL FOR FOREVER DO AFTER BREAK RETURN END
%token <number> BOOLEAN RAW NUMBER SIGNED ERRVAL
%token <string> NAME VAR TEXT UTF8 
%token <dval> FLOAT NANTOK 

%top {
#include stuff here
#include "../runtime.h"
%}

%union {
	long int number;
	char* string;
	double dval;
}

%{
struct parser__list {
struct parser__list *prev;
struct parser__list *next;
YYSTYPE data
}
%}

%%
varname
	:	VAR	{$$ = $1}
	|	varname '[' NUMBER ']'	{$$ = strcat($1,strcat(strcat("[",$2),"]"))}
	|	varname STRUCTPTR NAME	{$$ = strcat($1,strcat("->",$3))}
	|	varname '.' NAME	{$$ = strcat($1,strcat(".",$3))}
	;

lvalue
	:	varname
	|	NAME lvalue	{$$ = strcat(strcat($1," "),$2)}
	;

variable
	:	varname	{$$ = runtime__fetchbyname($1)}
	;

assignment
	:	varname ASSIGN anything	{$$ = {runtime__assignbyname($1) = $3}}
	|	varname ' ' ASSIGN ' ' anything	{$$ = {runtime__assignbyname($1) = $3}}
	;

anything
	:	quantity
	|	pointer
	|	expression
	|	function
	|	parenth
	;



quantity
	:	intergal
	|	real
	|	function
	|	variable
	|	pointer
	|	expression
	;

pointer
	:	variable
	|	array
	|	NULLTOK	{$$ = NULL}
	;

intergal
	:	SIGNED
	|	ERRVAL
	|	NULLTOK	{$$ = NULL}
	|	unsigned
	;

unsigned
	:	BOOLEAN
	|	RAW
	|	NUMBER
	;

real
	:	FLOAT
	|	NANTOK
	|	intergal
	;

expression
	:	anything
	|	anything ' ' '+' ' ' anything	{$$ = $2 + $4}
	|	anything ' ' '-' ' ' anything	{$$ = $2 - $4}
	|	anything ' ' '*' ' ' anything	{$$ = $2 * $4}
	|	anything ' ' '/' ' ' anything	{$$ = $2 / $4}
	|	anything ' ' '*' '*' ' ' anything	{$$ = pow($2,$4)}
	|	anything ' ' '*' '*' '*' ' ' anything	{$$ = pow($2,pow($2,$4))}
	|	expression ' ' '?' ' ' anything ':' anything	{$$ = $1 ? $2 : $3}
	/*more later*/
	;

commaval
	:	anything	{$$ = $1}
	|	' ' commaval	{$$ = $2}
	|	commaval ' '	{$$ = $1}
	;

commalist
	:	commaval ',' commaval	{
			$$ = malloc(sizeof(struct parser__list));
			$$->next = malloc(sizeof(struct parser__list));
			$$->prev = $$->next;
			$$->next->next = $$;
			$$->next->prev = $$;
			$$->data = $1;
			$$->next->data = $3;
			}
	|	commalist ',' commaval	{
			$$ = $1;	{
				foo = malloc(sizeof(struct parser__list));
				$$->prev->next = foo;
				foo->prev = $$->prev;
				$$->prev = foo;
				foo->next = $$;
				foo->data = $3;
				}
			}
	;

spacelist
	:	anything ' ' anything	{
			$$ = malloc(sizeof(struct parser__list));
			$$->next = malloc(sizeof(struct parser__list));
			$$->prev = $$->next;
			$$->next->next = $$;
			$$->next->prev = $$;
			$$->data = $1;
			$$->next->data = $3;
			}
	|	spacelist ' ' anything	{
			$$ = $1;	{
				foo = malloc(sizeof(struct parser__list));
				$$->prev->next = foo;
				foo->prev = $$->prev;
				$$->prev = foo;
				foo->next = $$;
				foo->data = $3;
				}
			}
	;

array
	:	'{' commalist '}'	{$$ = runtime__makearray($2)}
	|	TEXT
	;

parenth
	:	'(' commaval ')'	{$$ = $2}
	|	'(' assignment ')'	{$$ = $2}
	;

function
	:	NAME '(' ')'	{$$ = runtime__execute_void($1,$3)}
	|	NAME '(' anything ')'	{$$ = runtime__execute($1,$3)}
	|	NAME '(' commalist ')'	{$$ = runtime__execute_list($1,$3)}
	|	'(' NAME ')'	{$$ = runtime__execute_void($2,$3)}
	|	'(' NAME ' ' anything ')'	{$$ = runtime__execute($2,$3)}
	|	'(' NAME ' ' spacelist ')'	{$$ = runtime__execute_list($2,$3)}
	;

preparetodie
	:	HUP	{return(ERR);}
	;

dostuff
	:	expression ';'
	|	function ';'
	|	parenth ';'
	|	assignment ';'
	|	ifthen
	|	simpleloop
	|	forloop
	|	dostuff dostuff	{$1; $3;}
	;

ifthen
	:	IF '(' expression ')' THEN dostuff ifterm	{if ($3) {$6}}
	;

ifterm
	:	ELSE dostuff END	{else {$2}}
	|	ELSE ifthen	{else $2}
	|	END	{}
	;

simpleloop
	:	WHILE '(' expression ')' DO dostuff END	{while ($3) {$6}}
	|	UNTIL '(' expression ')' DO dostuff END	{while (!($3)) {$6}}
	|	DO dostuff WHILE '(' expression ')' END	{do {$2} while ($5)}
	|	DO dostuff UNTIL '(' expression ')' END	{do {$2} while (!($5))}
	|	FOREVER DO dostuff END	{for (;;) {$3}}
	;

returnval
	:	RETURN	anything	{return $2;}
	;

breaktok
	:	BREAK	{break;}

forloop
	:	FOR assignment ';' WHILE '(' expression ')' DO dostuff AFTER dostuff END {for ($2;$6;$9) {$11}}
	|	FOR assignment ';' UNTIL '(' expression ')' DO dostuff AFTER dostuff END {for ($2;!($6);$9) {$11}}
	;

switchtable
	:	SWITCH variable	DO caselist END	{switch $2 : {$4}}
	;

caseentry
	:	CASE quantity THEN dostuff END	{case $2 : $4; break;}
	|	CASE quantity LOGOR	{case $2 :;}
	|	casentry casentry	{$1 $2}
	;

casentries