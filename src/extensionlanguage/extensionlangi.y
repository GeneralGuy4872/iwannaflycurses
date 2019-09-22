%token STRUCTPTR BITLEFT LE BITRIGHT GE LOGAND LOGOR LOGNAND LOGNOR LOGIFF LOGXOR EQ NE APPROX ASSIGN ABORT DECR INC PTRPTR PTRPTRPTR
%token <number> BOOLEAN NUMBER
%token <string> NAME UTF8 TEXT LVALUE
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

%type <dval> real
%%

varname:	NAME	{$$ = $1}
	|	varname ';' NUMBER	{$$ = strcat(strcat($1,$2),$3)}
	|	varname STRUCTPTR NAME	{$$ = strcat(strcat($1,"->"),$3)}
	|	varname '.' NAME	{$$ = strcat(strcat($1,$2),$3)}
	;

variable:	varname	{$$ = runtime__fetchbyname($1)}
	;

addrof:	'&' variable	{$$ = &($2)}
	|	LOGAND variable	{$$ = &(&($2))}
	;

deref:	'*' variable	{$$ = *($2)}
	|	PTRPTR variable	{$$ = **($2)}
	|	PTRPTRPTR variable	{$$ = ***($2)}
	|	'*' pointer	{$$ = *($2)}
	|	PTRPTR pointer	{$$ = **($2)}
	|	PTRPTRPTR pointer	{$$ = ***($2)}
	;

assignment: LVALUE ASSIGN rvalue	{$$ = {runtime__assignbyname($1) = $3}}
	;

quantity:	intergal	{$$ = $1}
	|	real	{$$ = $1}
	|	infixexpression	{$$ = $1}
	|	sexpression	{$$ = $1}
	|	function	{$$ = $1}
	|	variable	{$$ = $1}
	|	deref	{$$ = $1}
	;

pointer:	variable	{$$ = $1}
	|	addrof	{$$ = $1}
	|	TEXT	{$$ = $1}
	;

infixexpression:	'{' quantity '}'	{$$ = $2}
	|	'{' quantity '+' quantity '}'	{$$ = $2 + $4}
	|	'{' quantity '-' quantity '}'	{$$ = $2 - $4}
	|	'{' quantity '*' quantity '}'	{$$ = $2 * $4}
	|	'{' quantity '/' quantity '}'	{$$ = $2 / $4}
	|	'{' quantity PTRPTR quantity '}'	{$$ = pow($2,$4)}
	|	'{' quantity PTRPTRPTR quantity '}'	{$$ = pow($2,pow($2,$4))}
	;

deadbeef:	ABORT	{return(ERR);}
	;