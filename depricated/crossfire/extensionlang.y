%token PTR LSTRUCT LARR RARR BITLEFT LE BITRIGHT GE LOGAND LOGOR LOGNAND LOGNOR LOGIFF LOGXOR DIFF CMP EQ EQUALS APPROX BITNOR NE ALLOC FREE NULLTOK NILTOK NANTOK INFTOK UNFTOK SWITCH CASE IF UNLESS THEN ELSE WHILE UNTIL FOR FOREVER FOREACH DO ONCE AFTER BREAK GOTO RETURN FI BEGIN END DIE EXIT QUANTUM CURRENT IN ASSERT
%token <number> NUMBER ERRVAL TAIL
%token <deadbeef> RAW
%token <boolean> BOOLEAN
%token <string> FNAME NAME LABEL TEXT UTF8 TYPENAME NILTOK
%token <dval> FLOAT NANTOK
%token <ptr> NULLTOK

%union
{
	bool boolean;
	int number;
	char* string;
	double dval;
	uintptr_t deadbeef;
	void* ptr;
}

%%
illegal
	:	DIE
	|	atat NULLTOK
	;

cast
	:	TYPENAME
	|	cast TYPENAME
	;

atat
	:	'@'
	|	atat '@'
	;

ptrptr
	:	PTR
	|	ptrptr PTR

pointercast
	:	cast ptrptr
	;

pointer
	:	pointercast variable
	|	'$' variable
	;

arrayinit
	:	'[' ']'
	|	'[' RAW ']'
	|	arrayinit arrayinit
	;

subscript
	:	'['  ']'
	|	'[' RAW ']'
	|	'[' TAIL ']'
	|	'[' NAME ']'
	|	'[' atat NAME ']'
	|	'[' parenth ']'
	|	'[' ']'
	;

arraycast
	:	cast arrayinit
	|	pointercast arrayinit
	;

arrayliteral
	:	TEXT
	|	'{' commalist '}'
	;

array
	:	pointervariable
	|	arraycast variable
	;

arrayfield
	:	arrayvariable subscript
	|	arrayfield subscript
	;

structliteral
	:	cast LSTRUCT commalist '}'
	;

structfield
	:	variable '.' NAME
	|	pointer RARR NAME
	|	variable '.' NAME
	|	pointer RARR NAME
	|	structfield '.' NAME
	|	structfield RARR NAME
	;

anycast
	:	cast
	|	pointercast
	|	arraycast
	;

variable
	:	NAME
	|	atat variable
	|	pointer
	|	arrayliteral
	|	array
	|	arrayfield
	|	structliteral
	|	structfield
	;	

names
	:	NAME
	|	names NAME
	;

lvalues
	:	cast names
	|	cast ptrptr names
	;

lvalue
	:	cast NAME
	|	cast ptrptr NAME
	;

larray
	:	cast NAME arrayinit
	|	cast ptrptr NAME arrayinit
	|	cast '('ptrptr NAME ')' arrayinit
	|	cast ptrptr '(' ptrptr NAME ')' arrayinit
	;

spacepointers
	:	NAME
	|	'$' NAME
	|	spacepointers ' ' NAME
	|	spacepointers ' ' '$' NAME
	;

allocate
	:	ALLOC lvalue ':' '=' quantityliteral ';'
	:	ALLOC lvalue LARR structliteral ';'
	|	ALLOC larray LARR arrayliteral ';'
	|	ALLOC lvalues ';'
	;

release
	:	FREE spacepointers ';'
	;

assignment
	:	variable ':' '=' anything
	|	variable '+' '=' quantity
	|	variable '-' '=' quantity
	|	variable '*' '=' quantity
	|	variable '/' '=' quantity
	|	variable '%' '=' intergal
	|	variable BITLEFT '=' intergal
	|	variable BITRIGHT '=' intergal
	|	variable '&' '=' intergal
	|	variable '|' '=' intergal
	|	variable '~' '&' '=' intergal
	|	variable '&' '~' '=' intergal
	|	variable BITNOR '=' intergal
	|	variable '^' '=' intergal
	|	variable EQ '=' intergal
	|	variable '~' '=' intergal
	|	variable LARR array
	;
	/* section complete! */

anything
	:	variable
	|	itmoves
	|	verb
	|	assertion
	|	EXIT
	;

assertion
	:	ASSERT variable
	|	ASSERT itmoves
	|	ASSERT verb
	;

constant
	:	quantityliteral
	|	arrayliteral
	|	structliteral
	;		

quantityliteral
	:	intergaliteral
	|	FLOAT
	|	NANTOK
	|	INFTOK
	|	UNFTOK
	;

intergaliteral
	:	NUMBER
	|	BOOLEAN
	|	RAW
	|	ERRVAL
	|	NULLTOK
	;

random
	:	literalexpression ' ' 'D' ' ' literalexpression
	|	literalexpression ' ' 'd' ' ' literalexpression
	|	QUANTUM
	;

literalexpression
	:	intergaliteral
	|	literalparenth
	|	literalexpression ' ' '+' ' ' literalexpression
	|	literalexpression ' ' '-' ' ' literalexpression
	|	literalexpression ' ' '*' ' ' literalexpression
	|	literalexpression ' ' '/' ' ' literalexpression
	|	literalexpression ' ' '*' '*' ' ' literalexpression
	|	literalexpression ' ' '*' '*' '*' ' ' literalexpression
	|	'!' literalexpression
	|	literalexpression '?' literalexpression ':' literalexpression
	;
	/* more later
	 * these are the reducibles
	 */

literalexpressionf
	:	quantityliteral
	|	literalparenth
	|	literalfparenth
	|	literalexpressionf ' ' '+' ' ' literalexpressionf
	|	literalexpressionf ' ' '-' ' ' literalexpressionf
	|	literalexpressionf ' ' '*' ' ' literalexpressionf
	|	literalexpressionf ' ' '/' ' ' literalexpressionf
	|	literalexpressionf ' ' '*' '*' ' ' literalexpressionf
	|	literalexpressionf ' ' '*' '*' '*' ' ' literalexpressionf
	|	literalexpressionf '!'
	|	literalexpression '?' literalexpression ':' literalexpression
	;

expression
	:	anything
	|	literalexpression
	|	literalexpressionf
	|	expression ' ' '+' ' ' expression
	|	expression ' ' '-' ' ' expression
	|	expression ' ' '*' ' ' expression
	|	expression ' ' '/' ' ' expression
	|	expression ' ' '*' '*' ' ' expression
	|	expression ' ' '*' '*' '*' ' ' expression
	|	'!' expression
	|	expression '?' expression ':' expression
	;

commalist
	:	anything ',' anything
	|	commalist ',' anything
	;

spacelist
	:	anything ' ' anything
	|	spacelist ' ' anything
	;

structure
	:	cast LSTRUCT commalist '}'
	;

itmoves
	:	allocate
	|	release
	|	assignment
	;

verb
	:	random
	|	parenth
	|	function
	|	ifthen
	|	simpleloop
	|	forloop
	|	switchtable
	|	foreach
	;

literalparenth
	:	'(' optsp literalexpression optsp ')'
	;
literalparenthf
	:	'(' optsp literalexpressionf optsp ')'
	|	literalparenth
	;

parenth
	:	'(' optsp anything optsp ')'
	|	'(' optsp expression optsp ')'
	|	'(' optsp assignment optsp ')'
	|	'(' optsp allocate optsp ')'
	|	'(' optsp release optsp ')'
	|	literalparenth	{$$ = $1}
	;

function
	:	FNAME
	|	FNAME '{' anything '}'
	|	FNAME '{' commalist '}'
	|	'(' optsp FNAME '`' ' ' anything optsp ')'
	|	'(' optsp FNAME '`' ' ' spacelist optsp ')'
	|	'+' '+' variable
	|	'-' '-' variable
	|	variable '+' '+'
	|	variable '-' '-'
	|	anything 'D' anything
	|	anything 'd' anything
	;
	/* section complete! */

dostuff
	:	anything
	|	returnval
	|	BREAK
	|	dostuff ';' dostuff
	;

snobranch
	:	':' '(' NAME ')'
	|	':' 'S' NAME ')'
	|	':' 'F' NAME '('
	|	':' 'S' NAME ')' 'F' NAME ')'
	|	':' 'F' NAME ')' 'S' NAME ')'
	;

subroutine
	:	BEGIN dostuff END
	|	ASSERT BEGIN dostuff END
	|	LABEL BEGIN dostuff END
	|	LABEL ASSERT BEGIN dostuff END
	|	BEGIN dostuff END snobranch
	|	ASSERT BEGIN dostuff END ':' '(' NAME ')'
	|	LABEL BEGIN dostuff END snobranch
	|	LABEL ASSERT BEGIN dostuff END ':' '(' NAME ')'
	;

ifthen
	:	IF '(' expression ')' THEN dostuff else___
	|	UNLESS '(' expression ')' THEN dostuff else___
	|	IF '(' expression ')' THEN dostuff FI
	|	UNLESS '(' expression ')' THEN dostuff FI
	;

else___
	:	ELSE dostuff FI	{$$ = $2}
	|	ELSE ifthen	{$$ = $2}
	|	FI
	;

simpleloop
	:	WHILE '(' expression ')' DO dostuff FI	{$$ = runtime__queue_while($3,$6)}
	|	UNTIL '(' expression ')' DO dostuff FI	{$$ = runtime__queue_until($3,$6)}
	|	DO dostuff ONCE FI
	|	DO dostuff WHILE '(' expression ')' FI	{$$ = runtime__queue_dowhile($2,$5)}
	|	DO dostuff UNTIL '(' expression ')' FI	{$$ = runtime__queue_dountil($2,$5)}
	|	FOREVER DO dostuff FI	{$$ = runtime__queue_forever($3)}
	|	FOREACH anycast IN array DO dostuff FI
	;

returnval
	:	RETURN	anything
	|	RETURN
	;

fordeclare
	:	lvalues ';'
	|	lvalue ':' '=' quantityliteral ';'
	|	lvalue LARR structliteral ';'
	|	larray LARR arrayliteral ';'
	;

forloop
	:	FOR assignment ';' WHILE '(' expression ')' DO dostuff AFTER dostuff FI
	|	FOR assignment ';' UNTIL '(' expression ')' DO dostuff AFTER dostuff FI
	;

switchtable
	:	SWITCH variable	DO caselist FI	{$$ = runtime__queue_switch($2,$4)}
	;

caseentry
	:	CASE quantity THEN dostuff FI	{$$ = runtime__case($2,$4)}
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
