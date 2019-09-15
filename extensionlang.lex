#Don't remember the exact regex syntax, using generic unix metalanguage for groups until I get here
NAME [A-Za-z][A-Za-z01-9]*
STRING	\"(\\.|[^\"])*\"
NUMBER [01-9]+
HEX $[01-9a-fA-F]+
OCTAL @[01-7]+
NEWLINE [\n]
SPACE [ ]
TAB [\t]