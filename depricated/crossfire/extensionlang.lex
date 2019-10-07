BOOLEAN ("[Tt]("RUE"|"rue")|[Ff]("ALSE"|"alse"))
NAME	[A-Za-z_\xC2-\xF4][A-Za-z0-9_\x80-\xBF\xC2-\xF4]*
LABEL	[A-Za-z_\xC2-\xF4][A-Za-z0-9_\x80-\xBF\xC2-\xF4]*:
NUMBER	-?[0-9]+
UNSIGNED	\+[0-9]+
DIGITS	[0-9]+
TAILINDEX	-[1-9][0-9]*
FLOAT	-?([0-9]+)?\.[0-9]+
NANTOK	[Nn][Aa][Nn]
INFTOK	[Ii]("NF"|"nf"|"NFINITY"|"nfinity")
UNFTOK	-[Ii]("NF"|"nf"|"NFINITY"|"nfinity")
HEX	("0x")[0-9a-fA-F]+
OCTAL	@[0-7]+
ENDQUOTE	[^\\]"
ENDPQ	[^\\]\)
ENDPRIME	[^\\]'
TEXT	[.]+
CHAR	[\0-\x7F]
UTF8	("\xC0\x80"|[\xC2-\xDF][\x80-\xBF]|[\xE0-\xEF][\x80-\xBF][\x80-\xBF]|[\xF0-\xF4][\x80-\xBF][\x80-\xBF][\x80-\xBF]|
ERRVAL	([Oo][Kk]("AY"|"ay")?|[Ee]("RR"|"rr")) 
NEW	[Nn]("EW"|"ew")
FREE	[Ff]("REE"|"ree")

LARR	("<-"|"←")
RARR	("->"|"→")
BITLEFT	("<<"|"«")
LE	("<="|"≤"|[Ll][Ee])
LT	("<"|[Ll][Tt])
BITRIGHT	(">>"|"»")
GE	(">="|"≥"|[Gg][Ee])
GT	(">"|[Gg][Tt])
DIFF	([Dd]("IFF"|"iff")|"⇔"|"<=>")
LOGAND	("&&"|[Aa]("ND"|"nd"))
LOGOR	("||"|[Oo][Rr])
LOGNAND	("!&&"|[Nn][Aa]("ND"|"nd"))
LOGNOR	("!||"|[Nn][Oo][Rr])
LOGIFF	([Ii]("FF"|"ff")|"↔"|"<->")
LOGXOR	([Ee]?[Xx][Oo][Rr])
CMP	[Cc]("MP"|"mp")
EQ	([Ee][Qq]|"==="|"≡")
EQUALS	("=="|[Ee]("QUAL"|"qual"))
APPROX	("=~"|[Aa]("PPROX"|"pprox")|"≈")
BITNOR	("~|"|"¥")
NE	("!="|"≠"|[Nn][Ee])
NPR	[Nn][Pp][RrKk]
NCR	[Nn][Cc][RrKk]
WHITESPACE	[\a\t-\r\034- ]+
NEWLINE	[\n-\r\x1c-\x1f]+
NULLTOK	[Nn]("ULL"|"ull")
NILTOK [Nn]("IL"|"il")

QUANTUM	([Qq]("ANTUM"|"antum")|[Cc]("AT"|"at")([Aa]("LIVE"|"live")|[Dd]("EAD"|"ead")))
CURRENT	[Cc]("URRENT"|"urrent")
SWITCH	[Ss]("WITCH"|"witch")
CASE	[Cc]("ASE"|"ase")
IF	[Ii][Ff]
IN	[Ii][Nn]
UNLESS	[Uu][Nn]("LESS"|"less")
ELSE	[Ee]("LSE"|"lse")
WHILE	[Ww]("HILE"|"hile")
UNTIL	[Uu]("NTIL"|"ntil")
FOR	[Ff]("OR"|"or")
THEN	[Tt]("HEN"|"hen")
FOREVER	[Ff]("OR"|"or")[Ee]("VER"|"ver")
FOREACH	[Ff]("OR"|"or")[Ee]("ACH"|"ach")
DO	[Dd][Oo]
ONCE	[Oo]("NCE"|"nce")
AFTER	[Aa]("FTER"|"fter")
BREAK	[Bb]("REAK"|"reak")
GOTO	[Gg][Oo][Tt][Oo]
RETURN	[Rr]("ETURN"|"eturn")
BEGIN	[Bb]("EGIN"|"egin")
END	[Ee]("ND"|"nd")
FI	[Ff][Ii]
ASSERT	[Aa]("SSERT"|"ssert")
DIE	([Dd]("IE"|"ie")|[Aa]("BORT"|"bort")|[Gg][Oo][Mm][Ff])
EXIT	([Ee]("XIT"|"xit")|[Qq]("UIT"|"uit"))

%option noyywrap
%top{
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "y.tab.h"
%}
%s EXPR INSIDE
%x STRING COMMENT CHARVAL TYPE SNOBOL LVALUE INITYPE SUBSCR DESTROY
%%
<EXPR,INSIDE>"\""	yy_push_state(STRING);
<STRING>{ENDQUOTE}	yy_pop_state();
<STRING>{TEXT}	yyval.string = strdup(yytext);return(CTEXT);

<EXPR,INSIDE>"\`"	yy_push_state(FUN);
<FUN>{NAME}	yyval.string = strdup(yytext);return(FNAME);yy_pop_state();

<EXPR,INSIDE>"\'"	yy_push_state(CHARVAL);
<CHARVAL>{ENDPRIME}	yy_pop_state();
<CHARVAL>{CHAR}	yyval.number = *yytext;return(NUMBER);
<CHARVAL>{UTF8}	yyval.string = strdup(yytext);return(UTF8);

<EXPR,INSIDE>"["	yy_push_state(SUBSCR);return '[';
<SUBSCR>{DIGITS}	yyval.deadbeef = strtoul(yytext,NULL,10);return(RAW);
<SUBSCR>{HEX}	yyval.deadbeef = strtoul(yytext,NULL,16);return(RAW);
<SUBSCR>{OCTAL}	yyval.deadbeef = strtoul(yytext,NULL,8);return(RAW);
<SUBSCR>{TAILINDEX}	yyval.number = atoi(yytext);return(TAIL);
<SUBSCR>{NAME}	yyval.string = strdup(yytext);return(NAME);
<SUBSCR>"@"	return '@';
<SUBSCR>"("	yy_push_state(EXPR);return '(';
<SUBSCR>"]"	yy_pop_state();return ']';

<TYPE>")>"	yy_pop_state();
<TYPE>"){"	yy_pop_state();return(LSTRUCT);
<TYPE>{NAME}	yyval.string = strdup(yytext);return(TYPENAME);
<TYPE>"*"	return(PTR);
<TYPE>"["	return '[';

<INITYPE>")>"	yy_pop_state();
<INITYPE>{NAME}	yyval.string = strdup(yytext);return(TYPENAME);
<INITYPE>"*"	return(PTR);

<LVALUE>"<("	yy_push_state(INITYPE);
<LVALUE>{NAME}	yyval.string = strdup(yytext);return(NAME);
<LVALUE>"["	return '[';
<LVALUE>";"	yy_pop_state();return ';'

<DESTROY>{WHITESPACE}	return ' ';
<DESTROY>{NAME}	yyval.string = strdup(yytext);return(NAME);
<DESTROY>"$"	return '$';
<DESTROY>";"	yy_pop_state();return ';';

<EXPR,INSIDE>"("	yy_push_state(EXPR);return '(';
<EXPR>{WHITESPACE}	return ' ';
<EXPR>")"	yy_pop_state();return ')';
<0>"("	return '(';
<0>")"	return ')';

<EXPR,INSIDE>"/*"	yy_push_state(COMMENT);
<TYPE>"/*"	yy_push_state(COMMENT);
<COMMENT>"*/"	yy_pop_state();
<COMMENT>{TEXT};

<0,INSIDE>{LABEL}	yyval.string = strdup(yytext);return(LABEL);
<EXPR,INSIDE>{NAME}	yyval.string = strdup(yytext);return(NAME);
<0>{NAME}	yyval.string = strdup(yytext);return(NAME);
<EXPR,INSIDE>{NUMBER}	yyval.number = atoi(yytext);return(NUMBER)
<EXPR,INSIDE>{UNSIGNED}	yyval.deadbeef = strtoul(yytext,NULL,10);return(RAW);
<EXPR,INSIDE>{FLOAT}	yyval.dval = atof(yytext);return(FLOAT);
<EXPR,INSIDE>{NANTOK}	yyval.dval = atof(yytext);return(NANTOK);
<EXPR,INSIDE>{HEX}	yyval.deadbeef = strtoul(yytext,NULL,16);return(RAW);
<EXPR,INSIDE>{OCTAL}	yyval.deadbeef = strtoul(yytext,NULL,8);return(RAW);
<EXPR,INSIDE>{BOOLEAN}	yyval.boolean = !(strcmp(toupper(yytext),"TRUE"));return(BOOLEAN);
<EXPR,INSIDE>{ERRVAL}	yyval.number = -(!(strcmp(toupper(yytext),"ERR"))));return(ERRVAL);
<EXPR,INSIDE>{NULLTOK}	yyval.ptr = NULL;return(NULLTOK);
<EXPR,INSIDE>{NILTOK}	yyval.string = "";return(NILTOK);
<EXPR,INSIDE>{NANTOK}	yyval.dval = NAN;return(NANTOK);
<EXPR,INSIDE>{INFTOK}	yyval.dval = HUGE_VAL;return(INFTOK);
<EXPR,INSIDE>{UNFTOK}	yyval.dval = -HUGE_VAL;return(INFTOK);
<EXPR,INSIDE>"{"	return '{';
<EXPR,INSIDE>"}"	return '}';
<EXPR,INSIDE>"$"	return '$';
<EXPR,INSIDE>"+"	return '+';
<EXPR,INSIDE>{RARR}	return(RARR);
<EXPR,INSIDE>"-"	return '-';
<EXPR,INSIDE>"*"	return '*';
<EXPR,INSIDE>"/"	return '/';
<EXPR,INSIDE>"DICE"	return 'D';
<EXPR,INSIDE>"dice"	return 'd';
<EXPR,INSIDE>"%"	return '%';
<EXPR,INSIDE>{BITLEFT}	return(BITLEFT);
<EXPR,INSIDE>{CMP}	return(CMP)
<EXPR,INSIDE>{DIFF}	return(DIFF);
<EXPR,INSIDE>{LOGIFF}	return(LOGIFF);
<EXPR,INSIDE>{LE}	return(LE);
<LVALUE>{LARR}	yy_pop_state();return(LARR);
<EXPR,INSIDE>"<("	yy_push_state(TYPE);
<EXPR,INSIDE>{LT}	return '<';
<EXPR,INSIDE>{BITRIGHT}	return(BITRIGHT);
<EXPR,INSIDE>{GE}	return(GE);
<EXPR,INSIDE>{GT}	return '>';
<EXPR,INSIDE>{EQ}	return(EQ);
<EXPR,INSIDE>{EQUALS}	return(EQUALS);
<EXPR,INSIDE>{APPROX}	return(APPROX);
<EXPR,INSIDE>"="	return '=';
<EXPR,INSIDE>{NE}	return(NE);
<EXPR,INSIDE>{NPR}	return(NPR);
<EXPR,INSIDE>{NCR}	return(NCR);
<EXPR,INSIDE>{LOGXOR}	return(LOGXOR);
<EXPR,INSIDE>{LOGNAND}	return(LOGNAND);
<EXPR,INSIDE>{LOGNOR}	return(LOGNOR);
<EXPR,INSIDE>"!!"	return(LOGVAL);
<EXPR,INSIDE>"!"	return '!';
<EXPR,INSIDE>{BITNOR}	return(BITNOR);
<EXPR,INSIDE>"~"	return '~';
<EXPR,INSIDE>"¬"	return '~';
<EXPR,INSIDE>{LOGAND}	return(LOGAND);
<EXPR,INSIDE>"&"	return '&';
<EXPR,INSIDE>{LOGOR}	return(LOGOR);
<EXPR,INSIDE>"|"	return '|';
<EXPR,INSIDE>"^"	return '^';
<EXPR,INSIDE>"?"	return '?';
":"	return ':';
<0>"S("	return 'S';
<0>"F("	return 'F';
<EXPR,INSIDE>"."	return '.';
<EXPR,INSIDE>";"	return ';';
<EXPR,INSIDE>","	return ',';
<EXPR,INSIDE>"`"	yy_push_state(EXPR);return'`';
<EXPR,INSIDE>"\\"	return '\\';
<EXPR,INSIDE>{ALLOC}	yy_push_state(LVALUE);return(ALLOC);
<EXPR,INSIDE>{FREE}	yy_push_state(DESTROY);return(FREE);
<EXPR,INSIDE>{QUANTUM}	return(QUANTUM);
<EXPR,INSIDE>{SWITCH}	return(SWITCH);
<EXPR,INSIDE>{CASE}	return(CASE);
<EXPR,INSIDE>{IF}	return(IF);
<EXPR,INSIDE>{IN}	return(IN);
<EXPR,INSIDE>{UNLESS}	return(UNLESS);
<EXPR,INSIDE>{THEN}	return(THEN);
<EXPR,INSIDE>{ELSE}	return(ELSE);
<EXPR,INSIDE>{WHILE}	return(WHILE);
<EXPR,INSIDE>{UNTIL}	return(UNTIL);
<EXPR,INSIDE>{FOR}	return(FOR);
<EXPR,INSIDE>{FOREVER}	return(FOREVER);
<EXPR,INSIDE>{DO}	return(DO);
<EXPR,INSIDE>{ONCE}	return(ONCE);
<EXPR,INSIDE>{AFTER}	return(AFTER);
<EXPR,INSIDE>{BREAK}	return(BREAK);
<EXPR,INSIDE>{RETURN}	return(RETURN);
<EXPR,INSIDE>{FI}	return(FI);
<0>{BEGIN}	BEGIN(INSIDE);return(BEGIN);
<INSIDE>{END}	BEGIN(0);return(END);
<INSIDE>{GOTO}	return(GOTO);
{ASSERT}	return(ASSERT);
{EXIT}	return(EXIT);
{DIE}	return(DIE);
%%
