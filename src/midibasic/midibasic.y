%token SPEEDTOK KEYTOK DETUNETOK NOTETOK CUTTOK INSTTOK BANKTOK VOLTOK MUTETOK LOUDTOK ONTOK OFFTOK SUSTOK PORTTOK SOSTTOK SOFTTOK WAITTOK ENDTOK LOOPSTART LOOPEND INCR DECR
%token <twovals> NOTE 
%token <string> CHORDTOK
%token <number> NOTE NUMBER SIGN KEYBREAK

%top{
struct chord {
	struct cord next
	char data
	}	

%union{
	div_t twovals
	int number
	char* string
}

%%
instruction
	:	SPEEDTOK NUMBER '\n'
	|	SPEEDTOK INCR NUMBER '\n'
	|	SPEEDTOK DECR NUMBER '\n'
	|	VOLTOK NUMBER NUMBER '\n'
	|	VOLTOK INCR NUMBER NUMBER '\n'
	|	VOLTOK DECR NUMBER NUMBER '\n'
	|	MUTETOK	NUMBER '\n'
	|	LOUDTOK	NUMBER '\n'
	|	KEYTOK NUMBER KEYBREAK
	|	KEYTOK NUMBER notevalue '\n'
	|	INSTTOK	NUMBER NUMBER '\n'
	|	BANKTOK	NUMBER NUMBER '\n'
	|	SUSTOK NUMBER '\n'
	|	PORTTOK NUMBER '\n'
	|	SOSTTOK NUMBER '\n'
	|	SOFTTOK NUMBER '\n'
	|	DETUNETOK ONTOK NUMBER NUMBER '\n'
	|	DETUNETOK INCR NUMBER NUMBER '\n'
	|	DETUNETOK DECR NUMBER NUMBER '\n'
	|	DETUNETOK OFFTOK NUMBER '\n'
	|	NOTETOK ONTOK NUMBER value NUMBER '\n'
	|	NOTETOK OFFTOK NUMBER value NUMBER '\n'
	|	NOTETOK	ONTOK NUMBER chord NUMBER '\n'
	|	NOTETOK	OFFTOK NUMBER chord NUMBER '\n'
	|	CUTTOK NUMBER '\n'
	|	WAITTOK	NUMBER '\n'
	;

value
	:	NOTE
	|	NOTE SIGN
	|	notevalue
	|	notevalue
	;

chordlist
	:	notevalue ',' notevalue
	|	chord ',' notevalue
	|	notevalue CHORDTOK
	;

chord
	:	'(' chordlist ')'
	;

movement
	:	instruction
	|	movement instruction
	;

loop
	:	LOOPSTART movement LOOPEND
	;

song
	:	movement ENDTOK
	|	movement loop
	;
