NOTE [A-G][0-9][#%b]?
KEYSIG ([#]{1,9}|[b]{1,9}|[A-G][#%b]?)?

NUMBER [0-9]+
HEX ("0x"|"$")[0-9a-fA-F]+
OCTAL @[0-7]+

INDENT ^[ \t]+
SPACE [ \t]

SPEEDTOK "SPEED"
KEYTOK "KEY"
DETUNETOK "DETUNE"
NOTETOK "NOTE"
CUTTOK "CUT"
INSTTOK "INSTRUMENT"
VOLTOK "VOLUME"
MUTETOK "MUTE"
FORTETOK "FORTE"
ONTOK "ON"
OFFTOK "OFF"
SUSTOK "SUSTAIN"
WAITTOK "WAIT"
ENDTOK "END"
LOOPTOK "LOOP"
REPEATTOK "REPEAT"
RAWTOK "RAW"

%{
#include <stdio.h>
#include <string.h>
#include "y.tab.h"
%}
%%
{INDENT};
{SPACE};
"\n"	return '\n';

{NOTE}	yyval.string = strdup(yytext);return(NOTE);
{KEY}	yyval.string = strdup(yytext);return(KEY);

{NUMBER}	yyval.number = atoi(yytext);return(NUMBER);
{HEX}	yyval.number = strtoul(yytext,NULL,16);return(HEX);
{OCTAL}	yyval.number = strtoul(yytext,NULL,8);return(OCTAL);

SPEEDTOK "SPEED"	return(SPEEDTOK);
KEYTOK "KEY"	return(KEYTOK);
DETUNETOK "DETUNE"	return(DETUNETOK);
NOTETOK "NOTE"	return(NOTETOK);
CUTTOK "CUT"	return(CUTTOK);
INSTTOK "INSTRUMENT"	return(INSTTOK);
VOLTOK "VOLUME"	return(VOLTOK);
MUTETOK "MUTE"	return(MUTETOK);
FORTETOK "FORTE"	return(FORTETOK);
ONTOK "ON"	return(ONTOK);
OFFTOK "OFF"	return(OFFTOK);
SUSTOK "SUSTAIN"	return(SUSTOK);
WAITTOK "WAIT"	return(WAITTOK);
ENDTOK "END"	return(ENDTOK);
LOOPTOK "LOOP"	return(LOOPTOK);
REPEATTOK "REPEAT"	return(REPEATTOK);
RAWTOK "RAW"	return(RAWTOK);
%%