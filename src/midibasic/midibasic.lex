NOTE	[A-G][0-9]
CHORD	([Mm]|"maj"|"min"|"sus"|"dim"|"aug"|"!7")

NUMBER	[0-9]+
HEX	("0x"|"$")[0-9a-fA-F]+
OCTAL	@[0-7]+

INDENT	^[\t\x1C- ]+
SPACE	[\t\x1C- ]
NEWLINE	[\n\r\f\v]+

LOUD	("LOUD"|"FORTE")
SUSTAIN	("SUSTAIN"|"DAMPER")
WAIT	("WAIT"|"REST")
DOUBLESHARP	("*"|"x"|"##")

%{
#include <stdio.h>
#include <string.h>
#include "y.tab.h"
short accum;
%}

%s KEYCOND CORDCOND
%%
{INDENT};
{SPACE};
{NEWLINE}	return '\n';
<KEYCOND>{NEWLINE}	yyval.number = accum;accum = 0;BEGIN(0);return(KEYBREAK);

{NOTE}	yyval.twovals.quot = yytext[0];yyval.twovals.rem = atoi(yytext);return(NOTE);
<KEYCOND>{NOTE}	yyval.twovals.quot = yytext[0];yyval.twovals.rem = atoi(yytext);accum = 0;BEGIN(0);return(NOTE);

{NUMBER}	yyval.number = atoi(yytext);return(NUMBER);
{HEX}	yyval.number = strtoul(&(yytext[1]),NULL,16);return(NUMBER);
{OCTAL}	yyval.number = strtoul(yytext,NULL,8);return(NUMBER);

"SPEED"	return(SPEEDTOK);
"KEY"	BEGIN(KEYCOND);return(KEYTOK);
"DETUNE"	return(DETUNETOK);
"NOTE"	return(NOTETOK);
"CUT"	return(CUTTOK);
"INSTRUMENT"	return(INSTTOK);
"BANK"	return(BANKTOK);
"VOLUME"	return(VOLTOK);
"MUTE"	return(MUTETOK);
{LOUD}	return(LOUDTOK);
"ON"	return(ONTOK);
"OFF"	return(OFFTOK);
{SUSTAIN}	return(SUSTOK);
"PORTAMENTO"	return(PORTTOK);
"SOSTENUTO"	return(SOSTTOK);
"SOFT"	return(SOFTTOK);
{WAIT}	return(WAITTOK);
"END"	return(ENDTOK);
"[:"	return(LOOPSTART);
":]"	return(LOOPEND);
"RAW"	return(RAWTOK);

<KEYCOND>"#"	accum++;
<KEYCOND>"b"	accum--;
"#"	yyval.number = 1;return(SIGN);
{DOUBLESHARP}	yyval.number = 2;return(SIGN);
"%"	yyval.number = 0;return(SIGN);
"b"	yyval.number = -1;return(SIGN);
"bb"	yyval.number = -2;return(SIGN);

"++"	return(INCR);
"--"	retunr(DECR);
"("	return '(';
")"	return ')';
","	return ',';
"\""	BEGIN(CORDCOND);
<CORDCOND>{CHORD}	yyval.string = strcpy(yytext);return(CHORDTOK);
<CORDCOND>"\""	BEGIN(0);
%%
