BOOLEAN ("T"|[Tt]("RUE"|"rue")|[Nn]("IL"|"il")|[Ff]("ALSE"|"alse"))
	/*not lowercase t, that might be needed*/
NAME [A-Za-z_][A-Za-z0-9_]*
NUMBER -?[0-9]+
HEX ("$"|"0x")[0-9a-fA-F]+
OCTAL @[0-7]+
ENDQUOTE [^\\]"
TEXT [.]+

STRUCTPTR ("->"|"→")
BITLEFT ("<<"|"«")
LE ("<="|"≤")
BITRIGHT (">>"|"»")
GE (">="|"≥")
IFFTOK [Ii]("FF"|"ff")
XORTOK [Xx]("OR"|"or")
NE "!="

	/*todo: escape sequences, numeric value '', but this should be enough to get this up and running*/

%{
#include <stdio.h>
#include <string.h>
#include "y.tab.h"
%}
%x STRING COMMENT
%%
"\""	BEGIN(STRING);
<STRING>{ENDQUOTE}	BEGIN(0);
<STRING>{TEXT}	yyval.string = strdup(yytext);return(TEXT);

"/*"	BEGIN(COMMENT);
<COMMENT>"*/"	BEGIN(0);
<COMMENT>{TEXT};

" "	return ' ';
"\t"	return '\t';
"\n"	return '\n';

"("	return '(';
")"	return ')';
	/*s-expressions and lists*/
"{"	return '{';
"}"	return '}';
	/*c-like expressions, structs, and arrays*/
"["	return '[';
"]"	return ']';
	/*array subscript*/

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
{LE}	return(LE);
"<"	return '<';
{BITRIGHT}	return(BITRIGHT);
{GE}	return(GE);
">"	return '>';
"="	return '=';
{IFFTOK}	return(IFFTOK);
{XORTOK}	return(XORTOK);
"!"	return '!';
"~"	return '~';
"&"	return '&';
"|"	return '|';
"^"	return '^';
"?"	return '?';
":"	return ':';
"."	return '.';
";"	return ';';
","	return ',';
%%