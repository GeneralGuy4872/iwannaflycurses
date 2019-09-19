BOOLEAN ("T"|[Tt]("RUE"|"rue")|[Nn]("IL"|"il")|[Ff]("ALSE"|"alse"))
	/*not lowercase t, that might be needed*/
NAME [A-Za-z_][A-Za-z0-9_]*
NUMBER -?[0-9]+
HEX ("$"|"0x")[0-9a-fA-F]+
OCTAL @[0-7]+
ENDQUOTE [^\\]"
ENDPRIME [^\\]'
TEXT [.]+
CHAR [\0-\x7F]
UTF8 ([\0xB0-\0xCF][\0x80-\0xAF]|[\0x70-\0x7F][\0x80-\0xAF][\0x80-\0xAF]|[\0xF0-\0xF7][\0x80-\0xAF][\0x80-\0xAF][\0x80-\0xAF])

STRUCTPTR ("->"|"→")
BITLEFT ("<<"|"«")
LE ("<="|"≤"|[Ll][Ee])
LT ("<"|[Ll][Tt])
BITRIGHT (">>"|"»")
GE (">="|"≥"|[Gg][Ee])
GT (">"|[Gg][Tt])
LOGAND ("&&"|[Aa]("ND"|"nd"))
LOGOR ("||"|[Oo][Rr])
LOGNAND ("!&&"|[Nn][Aa]("ND"|"nd"))
LOGNOR ("!||"|[Nn][Oo][Rr])
LOGIFF ([Ii]("FF"|"ff")|"⇔"|"<=>")
LOGXOR ([Ee]?[Xx][Oo][Rr])
EQ [Ee][Qq]
EQUALS ([=][=]?|[Ee]("QUAL"|"qual"))
BITNOR ("~|"|"¥")
NE ("!="|"≠"|[Nn][Ee])
ASSIGN (":="|"←")
ABORT ^([Aa]("BORT"|"bort"))$
WHITESPACE [\t-\r\034- ]+

%option noyywrap
%top{
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "y.tab.h"
%}
%s SEXPR CLIKE MATH
%x STRING COMMENT CHARVAL LVALUE
%%
"\""	yy_push_state(STRING);
<STRING>{ENDQUOTE}	yy_pop_state();
<STRING>{TEXT}	yyval.string = strdup(yytext);return(TEXT);

"\'"	yy_push_state(CHARVAL);
<CHARVAL>{CHARVAL}	yy_pop_state();
<CHARVAL>{CHAR}	yyval.number = *yytext;return(HEX);
<CHARVAL>{UTF8}	yyval.string = strdup(yytext);return(UTF8);

"/*"	yy_push_state(COMMENT);
<LVALUE>"/*"	yy_push_state(COMMENT);
<COMMENT>"*/"	yy_pop_state();
<COMMENT>{TEXT};

<SEXPR>{WHITESPACE}	return ' ';
<MATH>{WHITESPACE}	return ' ';

"`"	yy_push_state(LVALUE);
<LVALUE>{NAME}	yyval.string = strdup(yytext);return(NAME);
<LVALUE>"*"	return '*';
<LVALUE>{ASSIGN}	yy_pop_state(); return(ASSIGN);

"("	yy_push_state(SEXPR); return '(';
<SEXPR>")"	yy_pop_state(); return ')';
	/*s-expressions and lists*/
"{"	yy_push_state(MATH); return '{';
<MATH>"}"	yy_pop_state(); return '}';
	/*infix*/
"["	yy_push_state(CLIKE); return '[';
<LVALUE>"["	yy_push_state(CLIKE); return '[';
<CLIKE>"]"	yy_pop_state(); return ']';
	/*c-like functions, structs, and arrays*/

{NAME}	yyval.string = strdup(yytext);return(NAME);
{NUMBER}	yyval.number = atoi(yytext);return(NUMBER);
{HEX}	yyval.number = strtoul(yytext,NULL,16);return(HEX);
{OCTAL}	yyval.number = strtoul(yytext,NULL,8);return(OCTAL);
{BOOLEAN}	yyval.number = !(strcmp(toupper(yytext),"T") && strcmp(toupper(yytext),"TRUE"));
{DEC}	return(DEC);
{INC}	return(INC);
"+"	return '+';
{STRUCTPTR}	return(STRUCTPTR);
"-"	return '-';
"*"	return '*';
"/"	return '/';
"%"	return '%';
{BITLEFT}	return(BITLEFT);
{LOGIFF}	return(LOGIFF);
{LE}	return(LE);
{LT}	return '<';
{BITRIGHT}	return(BITRIGHT);
{GE}	return(GE);
{GT}	return '>';
{EQUALS}	return '=';
{NE}	return(NE);
{LOGXOR}	return(LOGXOR);
{LOGNAND}	return(LOGNAND);
{LOGNOR}	return(LOGNOR);
"!"	return '!';
{BITNOR}	return(BITNOR);
"~"	return '~';
{LOGAND}	return(LOGAND);
"&"	return '&';
{LOGOR}	return(LOGOR);
"|"	return '|';
"^"	return '^';
{EQ}	return(EQ);
<MATH>"?"	return '?';
<MATH>":"	return ':';
"."	return '.';
";"	return ';';
<CLIKE>","	return ',';
"\\"	return '\\';
{ABORT}	fprintf(stderr,"Your wish is my command..."); quit(1);
%%
