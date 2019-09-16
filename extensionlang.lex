#Don't remember the exact regex syntax, using generic unix metalanguage for groups until I get here
NAME [A-Za-z_][A-Za-z0-9_]*
STRING	\"(\\.|[^\"])*\"
NUMBER [0-9]+
HEX $[0-9a-fA-F]+
OCTAL @[0-7]+
NEWLINE [\n]
SPACE [ ]
TAB [\t]