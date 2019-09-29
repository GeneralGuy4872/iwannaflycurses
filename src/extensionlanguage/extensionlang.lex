BOOLEAN ("T"|[Tt]("RUE"|"rue")|[Nn]("IL"|"il")|[Ff]("ALSE"|"alse"))
	/*not lowercase t, that might be needed*/
NAME	[A-Za-z_\xC2-\xF4][A-Za-z0-9_\x80-\xBF\xC2-\xF4]*
VAR	$([A-SU-Za-z]|[A-Za-z_\xC2-\xF4][A-Za-z0-9_\x80-\xBF\xC2-\xF4]+)
PTRVAR	[\*&]+([A-SU-Za-z]|[A-Za-z_\xC2-\xF4][A-Za-z0-9_\x80-\xBF\xC2-\xF4]+)
NUMBER	-?[0-9]+
FLOAT	-?([0-9]+)?\.[0-9]+
NANTOK	(-?[Ii]("NFINITY"|"nfinity")|[Nn][Aa][Nn])
HEX	("0x")[0-9a-fA-F]+
OCTAL	@[0-7]+
ENDQUOTE	[^\\]"
ENDPRIME	[^\\]'
TEXT	[.]+
CHAR	[\0-\x7F]
UTF8	("\xC0\x80"|[\xC2-\xDF][\x80-\xBF]|[\xE0-\xEF][\x80-\xBF][\x80-\xBF]|[\xF0-\xF4][\x80-\xBF][\x80-\xBF][\x80-\xBF]|
ERRVAL	([Oo][Kk]("AY"|"ay")?|[Ee]("RR"|"rr")) 

STRUCTPTR	("->"|"→")
BITLEFT	("<<"|"«")
LE	("<="|"≤"|[Ll][Ee])
LT	("<"|[Ll][Tt])
BITRIGHT	(">>"|"»")
GE	(">="|"≥"|[Gg][Ee])
GT	(">"|[Gg][Tt])
LOGAND	("&&"|[Aa]("ND"|"nd"))
LOGOR	("||"|[Oo][Rr])
LOGNAND	("!&&"|[Nn][Aa]("ND"|"nd"))
LOGNOR	("!||"|[Nn][Oo][Rr])
LOGIFF	([Ii]("FF"|"ff")|"⇔"|"<>")
LOGXOR	([Ee]?[Xx][Oo][Rr])
EQ	([Ee][Qq]|"≡")
EQUALS	([=][=]|[Ee]("QUAL"|"qual"))
APPROX	("=~"|[Aa]("PPROX"|"pprox")|"≈")
BITNOR	("~|"|"¥")
NE	("!="|"≠"|[Nn][Ee])
NPR	[Nn][Pp][RrKk]
NCR	[Nn][Cc][RrKk]
ASSIGN	(":="|"←")
WHITESPACE	[\a\t-\r\034- ]+
NULLTOK	[Nn]("ULL"|"ull")

FLIP	[Ff]("LIP"|"lip")
SWITCH	[Ss]("WITCH"|witch")
CASE	[Cc]("ASE"|"ase")
IF	[Ii][Ff]
ELSE	[Ee]("LSE"|"lse")
WHILE	[Ww]("HILE"|"hile")
UNTIL	[Uu]("NTIL"|"ntil")
FOR	[Ff]("OR"|"or")
THEN	[Tt]("HEN"|"hen")
FOREVER	[Ff]("OREVER"|"orever")
DO	[Dd][Oo]
AFTER	[Aa]("FTER"|"fter")
BREAK	[Bb]("REAK"|"reak")
RETURN	[Rr]("ETURN"|"eturn")
BEGIN	[Bb]("EGIN"|"egin")
END	[Ee]("ND"|"nd")
FI	[Ff][Ii]

%option noyywrap
%top{
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "y.tab.h"
%}
%s FUNC EXPR ARR
%x STRING COMMENT CHARVAL TYPE
%%
"\""	yy_push_state(STRING);
<STRING>{ENDQUOTE}	yy_pop_state();
<STRING>{TEXT}	yyval.string = strdup(yytext);return(TEXT);

"\'"	yy_push_state(CHARVAL);
<CHARVAL>{ENDPRIME}	yy_pop_state();
<CHARVAL>{CHAR}	yyval.number = *yytext;return(NUMBER);
<CHARVAL>{UTF8}	yyval.string = strdup(yytext);return(UTF8);

"`"	yy_push_state(TYPE);
<TYPE>"`"	yy_pop_state()
<TYPE>"{`"	yy_pop_state();return(LSTRUCT);
<TYPE>{NAME}	yyval.string = strdup(yytext);return(TYPENAME);
<TYPE>'*'	return(TYPEPTR);
<TYPE>'&'	return(DEREF);

"/*"	yy_push_state(COMMENT);
<TYPE>"/*"	yy_push_state(COMMENT);
<COMMENT>"*/"	yy_pop_state();
<COMMENT>{TEXT};

<EXPR>{WHITESPACE}	return ' ';

"("	yy_push_state(EXPR); return '(';
<EXPR>")"	yy_pop_state(); return ')';

"{"	yy_push_state(ARR); return '{';
<ARR>"}"	yy_pop_state(); return '}';

"["	yy_push_state(FUNC); return '[';
<FUNC>"]"	yy_pop_state(); return ']';

{NAME}	yyval.string = strdup(yytext);return(NAME);
{VAR}	yyval.string = strdup(&(yytext[1]));return(VAR);
{PTRVAR}	yyval.string = strdup(yytext);return(VAR);
{NUMBER}	yyval.number = atoi(yytext);return(NUMBER);
{FLOAT}	yyval.dval = atof(yytext);return(FLOAT);
{NANTOK}	yyval.dval = atof(yytext);return(NANTOK);
{HEX}	yyval.deadbeef = strtoul(yytext,NULL,16);return(RAW);
{OCTAL}	yyval.deadbeef = strtoul(yytext,NULL,8);return(RAW);
{BOOLEAN}	yyval.boolean = !(strcmp(yytext,"T") || strcmp(toupper(yytext),"TRUE"));return(BOOLEAN);
{ERRVAL}	yyval.number = -(!(strcmp(toupper(yytext),"ERR"))));return(ERRVAL);
{NULLTOK}	return(NULLTOK);
"+"	return '+';
{STRUCTPTR}	return(STRUCTPTR);
"-"	return '-';
"*"	return '*';
"/"	return '/';
"D%"	return 'D';
"d%"	return 'd';
"%"	return '%';
{BITLEFT}	return(BITLEFT);
{LOGIFF}	return(LOGIFF);
{LE}	return(LE);
{LT}	return '<';
{BITRIGHT}	return(BITRIGHT);
{GE}	return(GE);
{GT}	return '>';
{EQUALS}	return(EQUALS);
'='	return '=';
{NE}	return(NE);
{NPR}	return(NPR);
{NCR}	return(NCR);
{LOGXOR}	return(LOGXOR);
{LOGNAND}	return(LOGNAND);
{LOGNOR}	return(LOGNOR);
"!"	return '!';
{APPROX}	return(APPROX);
{BITNOR}	return(BITNOR);
"~"	return '~';
"¬"	return "~";
{LOGAND}	return(LOGAND);
"&"	return '&';
{LOGOR}	return(LOGOR);
"|"	return '|';
"^"	return '^';
{EQ}	return(EQ);
"?"	return '?';
":"	return ':';
"."	return '.';
";"	return ';';
","	return ',';
"\\"	return '\\';
{FLIP}	return(FLIP);
{SWITCH}	return(SWITCH);
{CASE}	return(CASE);
{IF}	return(IF);
{THEN}	return(THEN);
{ELSE}	return(ELSE);
{WHILE}	return(WHILE);
{UNTIL}	return(UNTIL);
{FOR}	return(FOR);
{FOREVER}	return(FOREVER);
{DO}	return(DO);
{AFTER}	return(AFTER);
{BREAK}	return(BREAK);
{RETURN}	return(RETURN);
{FI}	return(FI);
{BEGIN}	return(BEGIN);
{END}	return(END);
%%
