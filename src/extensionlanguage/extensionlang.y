%token STRUCTPTR BITLEFT LE BITRIGHT GE LOGAND LOGOR LOGNAND LOGNOR LOGIFF LOGXOR EQ EQUALS APPROX BITNOR NE ASSIGN NULLTOK HUP SWITCH CASE IF THEN ELSE WHILE UNTIL FOR FOREVER DO AFTER BREAK RETURN FI BEGIN END
%token <number> BOOLEAN RAW NUMBER SIGNED ERRVAL
%token <string> NAME VAR TEXT UTF8 
%token <dval> FLOAT NANTOK 

%top {
#include stuff here
#include "runtime.h"
//inherits "../dummy.h"
%}

%union {
	long number;
	char* string;
	double dval;
%}

%%
varname
	:	VAR	{$$ = $1}
	|	varname '[' NUMBER ']'	{$$ = strcat($1,strcat(strcat("[",$2),"]"))}
	|	varname STRUCTPTR NAME	{$$ = strcat($1,strcat("->",$3))}
	|	varname '.' NAME	{$$ = strcat($1,strcat(".",$3))}
	;

variable
	:	varname	{$$ = runtime__fetchbyname($1)}
	;

assignment
	:	varname ASSIGN anything	{$$ = runtime__assignbyname($1,':',$3)}
	|	varname ' ' ASSIGN ' ' anything	{$$ = runtime__assignbyname($1,':',$5)}
	|	varname '+' '=' quantity	{$$ = runtime__assignbyname($1,'+',$4)}
	|	varname ' ' '+' '=' ' ' quantity	{$$ = runtime__assignbyname($1,'+',$6)}
	|	varname '-' '=' quantity	{$$ = runtime__assignbyname($1,'-',$4)}
	|	varname ' ' '-' '=' ' ' quantity	{$$ = runtime__assignbyname($1,'-',$6)}
	|	varname '*' '=' quantity	{$$ = runtime__assignbyname($1,'*',$4)}
	|	varname ' ' '*' '=' ' ' quantity	{$$ = runtime__assignbyname($1,'*',$6)}
	|	varname '/' '=' quantity	{$$ = runtime__assignbyname($1,'/',$4)}
	|	varname ' ' '/' '=' ' ' quantity	{$$ = runtime__assignbyname($1,'/',$6)}
	|	varname '%' '=' intergal	{$$ = runtime__assignbyname($1,'%',$6)}
	|	varname ' ' '%' '=' ' ' intergal	{$$ = runtime__assignbyname($1,'%',$6)}
	|	varname BITLEFT '=' intergal	{$$ = runtime__assignbyname($1,'L',$4)}
	|	varname ' ' BITLEFT '=' ' ' intergal	{$$ = runtime__assignbyname($1,'L',$6)}
	|	varname BITRIGHT '=' intergal	{$$ = runtime__assignbyname($1,'R',$6)}
	|	varname ' ' BITRIGHT '=' ' ' intergal	{$$ = runtime__assignbyname($1,'R',$6)}
	|	varname '&' '=' intergal	{$$ = runtime__assignbyname($1,'&',$4)}
	|	varname ' ' '&' '=' ' ' intergal	{$$ = runtime__assignbyname($1,'&',$6)}
	|	varname '|' '=' intergal	{$$ = runtime__assignbyname($1,'|',$4)}
	|	varname ' ' '|' '=' ' ' intergal	{$$ = runtime__assignbyname($1,'|',$6)}
	|	varname '~' '&' '=' intergal	{$$ = runtime__assignbyname($1,'N',$5)}
	|	varname ' ' '~' '&' '=' ' ' intergal	{$$ = runtime__assignbyname($1,'N',$7)}
	|	varname BITNOR '=' intergal	{$$ = runtime__assignbyname($1,'Y',$4)}
	|	varname ' ' BITNOR '=' ' ' intergal	{$$ = runtime__assignbyname($1,'N',$6)}
	|	varname '^' '=' intergal	{$$ = runtime__assignbyname($1,'^',$4)}
	|	varname ' ' '^' '=' ' ' intergal	{$$ = runtime__assignbyname($1,'^',$6)}
	|	varname EQ '=' intergal	{$$ = runtime__assignbyname($1,'E',$4)}
	|	varname ' ' EQ '=' ' ' intergal	{$$ = runtime__assignbyname($1,'E',$6)}
	|	varname '~' '=' intergal	{$$ = runtime__assignbyname($1,'~',$4)}
	|	varname ' ' '~' '=' ' ' intergal	{$$ = runtime__assignbyname($1,'~',$6)}
	;
	/*section complete!*/

anything
	:	quantity
	|	pointer
	|	function
	|	parenth
	;

quantity
	:	real
	|	NANTOK
	|	pointer
	;

quantityliteral
	:	intergaliteral
	|	FLOAT
	|	NANTOK
	|	NULLTOK	{$$ = NULL}
	;

pointer
	:	array
	|	NULLTOK	{$$ = NULL}
	;

intergal
	:	intergaliteral
	|	variable
	|	pointer
	;

intergaliteral
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
	|	intergal
	;

expression
	:	anything
	|	literalexpression
	|	expression
	/*more later*/
	;

literalexpression
	:	quantityliteral
	|	literalexpression ' ' '+' ' ' literalexpression	{$$ = $2 + $5}
	|	literalexpression ' ' '-' ' ' literalexpression	{$$ = $2 - $5}
	|	literalexpression ' ' '*' ' ' literalexpression	{$$ = $2 * $5}
	|	literalexpression ' ' '/' ' ' literalexpression	{$$ = $2 / $5}
	|	literalexpression ' ' '*' '*' ' ' literalexpression	{$$ = pow($2,$6)}
	|	literalexpression ' ' '*' '*' '*' ' ' literalexpression	{$$ = pow($2,pow($2,$7))}
	|	'!' literalexpression	{$$ = !($2)}
	|	literalexpression '!'	{$$ = util__factorial($1)}
	|	literalexpression ' ' '?' ' ' literalexpression ':' literalexpression	{$$ = $1 ? $5 : $7}
	/*more later*/
	;

commaval
	:	anything	{$$ = $1}
	|	' ' commaval	{$$ = $2}
	|	commaval ' '	{$$ = $1}
	;

commalist
	:	commaval ',' commaval	{
			$$ = malloc(sizeof(struct runtime__list));
			$$->next = malloc(sizeof(struct runtime__list));
			$$->prev = $$->next;
			$$->next->next = $$;
			$$->next->prev = $$;
			$$->string = $1->string;
			$$->number = $1->number;
			$$->ddval = $1->ddval;
			$$->next->string = $3->string;
			$$->next->number = $3->number;
			$$->next->ddval = $3->ddval;
			}
	|	commalist ',' commaval	{
			$$ = $1;	{
				foo = malloc(sizeof(struct parser__list));
				$$->prev->next = foo;
				foo->prev = $$->prev;
				$$->prev = foo;
				foo->next = $$;
				foo->string = $3->string;
				foo->number = $3->number;
				foo->ddval = $3->ddval;
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
	:	NAME '(' ')'	{$$ = runtime__queue_noargs($1)}
	|	NAME '(' anything ')'	{$$ = runtime__queue($1,$3)}
	|	NAME '(' commalist ')'	{$$ = runtime__queue_list($1,$3)}
	|	'(' NAME ')'	{$$ = runtime__queue_noargs($2)}
	|	'(' NAME ' ' anything ')'	{$$ = runtime__queue($2,$3)}
	|	'(' NAME ' ' spacelist ')'	{$$ = runtime__queue_list($2,$3)}
	|	'+' '+' variable	{$$ = runtime__queue_incr_pre($3)}
	|	'-' '-' variable	{$$ = runtime__queue_decr_pre($3)}
	|	variable '+' '+'	{$$ = runtime__queue_incr_post($1)}
	|	variable '-' '-'	{$$ = runtime__queue_decr_post($1)}
	;

preparetodie
	:	HUP	{return(ERR);}
	;

dostuff
	:	function	{$$ = $1}
	|	parenth	{$$ = NULL}
	|	assignment	{$$ = runtime__queue_sane($1)}
	|	ifthen	{$$ = $1}
	|	simpleloop	{$$ = $1}
	|	forloop	{$$ = $1}
	|	switchtable {$$ = $1}
	|	returnval	{$$ = runtime__queue_return($1)}
	|	BREAK	{$$ = runtime__queue_dobreak()}
	|	dostuff ';' dostuff	{runtime__concat_queue($1,$3)}
	;

execute
	:	BEGIN dostuff END	{$$ = runtime__execute($2)}

ifthen
	:	IF '(' expression ')' THEN dostuff else___	{$$ = runtime__queue_ifthenelse($3,$6,$7)}
	|	IF '(' expression ')' THEN dostuff END	{$$ = runtime__queue_ifthen($3,$6)}
	;

else___
	:	ELSE dostuff END	{$$ = $2}
	|	ELSE ifthen	{$$ = $2}
	|	END
	;

simpleloop
	:	WHILE '(' expression ')' DO dostuff END	{$$ = runtime__queue_while($3,$6)}
	|	UNTIL '(' expression ')' DO dostuff END	{$$ = runtime__queue_until($3,$6)}
	|	DO dostuff WHILE '(' expression ')' END	{$$ = runtime__queue_dowhile($2,$5)}
	|	DO dostuff UNTIL '(' expression ')' END	{$$ = runtime__queue_dountil($2,$5)}
	|	FOREVER DO dostuff END	{$$ = runtime__queue_forever($3)}
	;

returnval
	:	RETURN	anything	{$$ = $2}
	|	RETURN	{$$ = OK}
	;

forloop
	:	FOR assignment ';' WHILE '(' expression ')' DO dostuff AFTER dostuff END {$$ = runtime__queue_for($2,$6,$9,$11)}
	|	FOR assignment ';' UNTIL '(' expression ')' DO dostuff AFTER dostuff END {$$ = runtime__queue_fornot($2,$6,$9,$11)}
	;

switchtable
	:	SWITCH variable	DO caselist END	{$$ = runtime__queue_switch($2,$4)}
	;

caseentry
	:	CASE quantity THEN dostuff END	{$$ = runtime__case($2,$4)}
	|	CASE quantity LOGOR casentry	{$$ = runtime__case_multi($2,$4)}
	;

caselist
	:	caseentry caseentry	{$$ = runtime__concat_case($1,$2)}
	|	caselist caseentry	{$$ = runtime__concat_case($1,$2)}
	;