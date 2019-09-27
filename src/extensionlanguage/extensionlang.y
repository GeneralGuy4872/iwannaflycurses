%token LSTRUCT STRUCTPTR BITLEFT LE BITRIGHT GE LOGAND LOGOR LOGNAND LOGNOR LOGIFF LOGXOR EQ EQUALS APPROX BITNOR NE ASSIGN NULLTOK HUP SWITCH CASE IF THEN ELSE WHILE UNTIL FOR FOREVER DO AFTER BREAK RETURN FI BEGIN END
%token <number> BOOLEAN RAW NUMBER SIGNED ERRVAL
%token <string> NAME VAR TEXT UTF8 TYPENAME
%token <dval> FLOAT NANTOK 

%top {
#include stuff here
#include "runtime.c"
%}

%union
{
	intptr_t number;
	char* string;
	double dval;
}

%%
cast
	:	TYPENAME	{
			$$ = malloc(sizeof(stringlistyp))
			$$→prev = $$
			$$→next = NULL
			$$→text = $1
			}
	|	cast TYPENAME	{
			$$ = $1
			foo = malloc(sizeof(stringlistyp))
			$$→prev→next = foo
			foo→prev = $$→prev
			$$→prev = foo
			foo→next = NULL
			foo→text = $2
			}
	|	cast TYPEPTR	{
			$$ = $1
			foo = malloc(sizeof(stringlistyp))
			$$→prev→next = foo
			foo→prev = $$→prev
			$$→prev = foo
			foo→next = NULL
			foo→text = "*"
			}
	;

typecast
	:	cast anything	{$$ = runtime__cast($1,$2)}
	|	DEREF anything	{$$ = runtime__deref($2)}
	;

variable
	:	VAR	{$$ = runtime__fetch($1)}
	|	variable STRUCTPTR NAME	{$$ = runtime__struct_pointer($1,$3)}
	|	variable '.' NAME	{$$ = runtime__struct($1,$3)}
	|	variable '[' unsigned ']'	{$$ = runtime__arraysub($1,$3)}
	|	variable '[' literalparenth ']'	{$$ = runtime__arraysub($1,$3)}
	|	variable '[' anything ']'	{$$ = runtime__arraysub_noncon($1,$3)}
	;

assignment
	:	variable optsp ASSIGN optsp anything	{$$ = runtime__assign($1,0,$5)}
	|	variable optsp '+' '=' optsp quantity	{$$ = runtime__assign($1,'+',$6)}
	|	variable optsp '-' '=' optsp quantity	{$$ = runtime__assign($1,'-',$6)}
	|	variable optsp '*' '=' optsp quantity	{$$ = runtime__assign($1,'*',$6)}
	|	variable optsp '/' '=' optsp quantity	{$$ = runtime__assign($1,'/',$6)}
	|	variable optsp '%' '=' optsp intergal	{$$ = runtime__assign($1,'%',$6)}
	|	variable optsp BITLEFT '=' optsp intergal	{$$ = runtime__assign($1,'<',$6)}
	|	variable optsp BITRIGHT '=' optsp intergal	{$$ = runtime__assign($1,'>',$6)}
	|	variable optsp '&' '=' optsp intergal	{$$ = runtime__assign($1,'&',$6)}
	|	variable optsp '|' '=' optsp intergal	{$$ = runtime__assign($1,'|',$6)}
	|	variable optsp '~' '&' '=' optsp intergal	{$$ = runtime__assign($1,~'&',$7)}
	|	variable optsp '&' '~' '=' optsp intergal	{$$ = runtime__assign($1,'~',$7)}
	|	variable optsp BITNOR '=' optsp intergal	{$$ = runtime__assign($1,~'|',$6)}
	|	variable optsp '^' '=' optsp intergal	{$$ = runtime__assign($1,'^',$6)}
	|	variable optsp EQ '=' optsp intergal	{$$ = runtime__assign($1,~'^',$6)}
	|	variable optsp '~' '=' optsp intergal	{$$ = runtime__assign($1,-1,$6)}
	;
	/* section complete! */

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
	|	typecast
	;
	/* more later */

literalexpression
	:	quantityliteral
	|	literalparenth
	|	literalexpression ' ' '+' ' ' literalexpression	{$$ = $2 + $5}
	|	literalexpression ' ' '-' ' ' literalexpression	{$$ = $2 - $5}
	|	literalexpression ' ' '*' ' ' literalexpression	{$$ = $2 * $5}
	|	literalexpression ' ' '/' ' ' literalexpression	{$$ = $2 / $5}
	|	literalexpression ' ' '*' '*' ' ' literalexpression	{$$ = pow($2,$6)}
	|	literalexpression ' ' '*' '*' '*' ' ' literalexpression	{$$ = pow($2,pow($2,$7))}
	|	'!' literalexpression	{$$ = !($2)}
	|	literalexpression '!'	{$$ = util__factorial($1)}
	|	literalexpression optsp '?' optsp literalexpression optsp ':' optsp literalexpression	{$$ = $1 ? $5 : $9}
	;
	/* more later
	 * these are the reducibles
	 */

commalist
	:	anything ',' anything	{
			$$ = malloc(sizeof(struct runtime__list));
			$$->next = malloc(sizeof(struct runtime__list));
			$$->prev = $$->next;
			$$->next->next = NULL;
			$$->next->prev = $$;
			$$->string = $1->string;
			$$->number = $1->number;
			$$->ddval = $1->ddval;
			$$->next->string = $3->string;
			$$->next->number = $3->number;
			$$->next->ddval = $3->ddval;
			}
	|	commalist ',' anything	{
			$$ = $1;	{
				foo = malloc(sizeof(struct parser__list));
				$$->prev->next = foo;
				foo->prev = $$->prev;
				$$->prev = foo;
				foo->next = NULL;
				foo->string = $3->string;
				foo->number = $3->number;
				foo->ddval = $3->ddval;
				}
			}
	;

spacelist
	:	anything ' ' anything	{
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
	|	spacelist ' ' anything	{
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

structure
	:	cast LSTRUCT commalist '}'	{$$ = runtime__queue_struct($1,$3)}
	;

array
	:	'{' commalist '}'	{$$ = runtime__makearray($2)}
	|	TEXT	{$$ = $1}
	|	TEXT TEXT	{$$ = strcat($1,$2)}
	;

literalparenth
	:	'(' optsp literalexpression optsp ')'	{$$ = $3}
	;

parenth
	:	'(' optsp anything optsp ')'	{$$ = $3}
	|	'(' optsp expression optsp ')'	{$$ = $3}
	|	'(' optsp assignment optsp ')'	{$$ = $3}
	|	literalparenth	{$$ = $1}
	;

function
	:	NAME '[' ']'	{$$ = runtime__queue_noargs($1)}
	|	NAME '[' anything ']'	{$$ = runtime__queue($1,$3)}
	|	NAME '[' commalist ']'	{$$ = runtime__queue_list($1,$3)}
	|	'(' optsp NAME optsp ')'	{$$ = runtime__queue_noargs($3)}
	|	'(' optsp NAME ' ' anything optsp ')'	{$$ = runtime__queue($3,$5)}
	|	'(' optsp NAME ' ' spacelist optsp ')'	{$$ = runtime__queue_list($3,$5)}
	|	'+' '+' variable	{$$ = runtime__queue_incr_pre($3)}
	|	'-' '-' variable	{$$ = runtime__queue_decr_pre($3)}
	|	variable '+' '+'	{$$ = runtime__queue_incr_post($1)}
	|	variable '-' '-'	{$$ = runtime__queue_decr_post($1)}
	;
	/* section complete! */

dostuff
	:	function	{$$ = $1}
	|	parenth	{$$ = $1}
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

optsp
	:	/* empty */
	|	' '
	;
