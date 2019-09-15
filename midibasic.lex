#Don't remember the exact regex syntax, using generic unix metalanguage for groups until I get here
NOTE [A-G][01-9][#%b]?
KEYSIG ([#]+|[b]+|[A-G][#%b]?)?

NUMBER [01-9]+
HEX (0x|$)[01-9a-fA-F]+
OCTAL @[01-7]+
NEWLINE [\n]
SPACE [ ]
TAB [\t]

"SPEED"
"KEY"
"DETUNE"
"NOTE"
"PEDDLE"
"ON"
"OFF"
"DAMP"
"PORT"
"SUS"
"SOFT"
"WAIT"
"SET_INSTRUMENT"
"END"
"LOOP"
"REPEAT"
"RAW"

/*
syntax:

SPEED <HEX/OCTAL/NUMBER> : number of pulses per second. there are 24 pulses in a quarter note.

KEY <KEYSIG> : change the key. default key is C major

DETUNE ON <HEX/OCTAL/NUMBER channel> <HEX/OCTAL/NUMBER amount> : warp the tone by an amount

DETUNE OFF <HEX/OCTAL/NUMBER channel> : reset detuning

NOTE (ON|OFF) <HEX/OCTAL/NUMBER channel> <NOTE value> <HEX/OCTAL/NUMBER velocity> : begin/end a note

NOTE OFF <HEX/OCTAL/NUMBER channel> <NOTE value> <HEX/OCTAL/NUMBER velocity> : end a note

PEDDLE (ON|OFF) <HEX/OCTAL/NUMBER channel>  (DAMP|PORT|SUS|SOFT) : change the voicing

WAIT <HEX/OCTAL/NUMBER> : wait for a given number of pulses. wait deleminaits bursts of packets, affording time control sanity.

SET_INSTRUMENT <HEX/OCTAL/NUMBER channel, not ten or eleven> <HEX/OCTAL/NUMBER voice> : set the instrument program of the channel

...
...
...
END : end the song; a program may not expect the song to end, which would result in there being no sound after the end is reached.

...
...
LOOP
...
...
...
REPEAT : loop a portion of the song indefinately.

RAW <HEX> : a raw packet
*/