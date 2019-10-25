package MyParser::Lexer;
use strict;
use warnings;

######################################################################
#NOTICE
#
#gotos are used instead of subroutines since no distinction is made
#between blocks and scopes; this oversight makes the use of goto
#in this manner a necessity for non-linear programming, since
#variables would otherwise be shell-gamed in ungood ways.
#
#the gotos can be thought of as functions/subroutines which take
#the current state as an argument and return sideffects,
#
#using a flowchart with the entrypoint at the top, the drain at
#the bottom, all the tier 1 dispatchers on one side, all the
#tier 2 sorters on the opposite, and the whitespace/unary filter as
#a large vertical bar between the two columns, with all permutations
#of possible flow transfer shown, would provide the best understanding
#of the program's structure.
#
#yes, you can have structure with gotos, and excluding or "safing"
#them introduces an artificial ceiling to a program's complexity and
#efficiancy, one that I hit hard before making this design choice.
######################################################################

sub prompt {
	printf "\033[1;4;95m>\033[96m>\033[97m>\033[21;22;24;0m";
	my $tmp = <STDIN>;
	chomp $tmp;
	return $tmp;
	}

our $WHITESPACE = qr/[\0\a\s\034-\037]/ms;

our $UNSIGNED = qr/(?:0[xb])?(?:[0]*[1-9][0-9]*)/i;
our $FLOAT = qr/?[0-9]*[\.][0-9]+/
our $RNG = qr/(?:$UNSIGNED(?:ran)?[d]$UNSIGNED)/i
our $BONUS = qr/(?:+|±)$UNSIGNED/
our $NUMBER = qr/(?:$INTERGER|$FLOAT|$RNG|$BONUS)/

our $QTEXT = qr/^((?:(?!(?<!\\)').*)|(?:(?<!\\)'))/ms;
our $QQTEXT = qr/^((?:(?!(?<!\\)(?:"|$SIGAL|\\)).*)|(?:(?<!\\)")|$NAME)/ms;

our $SIGAL = qr/(?:(?:[\$\%\@\&]?[\$\*])|[\$][\#]))/;
our $IDENT = qr/[\w]+(?:(?:'|::)(?R))?/;
our $NAME = qr/(?:$SIGAL{(?R)}|$SIGAL(?:$IDENT)(?:(?:\-\>|(?:\-\>)?(?:\{(?:(?R))\}|\[(?:(?R)|[\-]?[0-9]+|[\#])\]))*))|$SIGAL(?:[^\w\s]|[\^]A-Z]|[\+\-])(?:\[(?:[\-]?[0-9]+|[\#])\]?))/;
our $READ = qr/[\<](?:[\w]+|$NAME)[\>]/;

our $SYMBOL = qr/^(?:(?:[\<](?:[\<]|[\=][\>]?)?|[\=][\~\=]?|[\+\-\%\~\!\|\&\>][\=]?|[\/](?:[\/\=])?|[\>][\>]|[\|][\|]|[\&][\&]|×|÷|≤|≥)|N[PC]R|[N]?AND|[X]?[N]?OR|NOT|[LG][TE]|NE|EQ(?:UAL)?|IFF|CMP|COINFLIP|FLIP[A]?COIN|MOV[E]?)/ims;
our $PREFIX = qr/^(?:(?:[!~]|[\+][\+]|[\-][\->]?)(?>!$WHITESPACE))/
our $POSTFIX = qr/^(?:(?!(?<!\\)(?:[!]|[\+][\+]|[\-][\-]?))/

our $BRANCH = qr/^(?:(?<!\\)(?:[\(\)\{\}\[\]'"`]))/;
our $ESCAPE = qr/^(?:[a-zA-Z]|cC|0|0[0-7][0-7]|x[0-9A-Fa-f][0-9A-Fa-f]|u[0-9A-Fa-f][0-9A-Fa-f][0-9A-Fa-f][0-9A-Fa-f]|U[0-9A-Fa-f][0-9A-Fa-f][0-9A-Fa-f][0-9A-Fa-f][0-9A-Fa-f][0-9A-Fa-f][0-9A-Fa-f][0-9A-Fa-f])/;

#%%

your @yylval;

sub entrypoint {
	my $input = shift // prompt()
	my $col = 1;
	my @stack = (initial);
	my $match;
	if ($input eq '') {
		error 'got nothin\'';
		return 0;
		}
######################################################################
# ABANDON ALL HOPE YE WHO ENTER HERE,
# FOR THE WAES OF STRUCTURED PROGRAMMING DOTH BE FORSOOKE!
######################################################################
initial:
unless ($input eq '') {
	$match = substr $input,0,1;
	$match // die "Daaaiiisy, Daaaaaiiiiisy, give me your answer, do. IIII'm haalf craaaaaaazy..."
	$col++
	$input = substr $input,1;
	if ($match =~ m/$WHITESPACE/) {
		goto ($stack->[-1]);
		}
	unless ($input eq '') {
		if ($match eq '(') {goto lparen;}
		else {die "syntax error outdoors at character $col (±dodgy counters)";}
		}
	else {die "syntax error outdoors near EOF";}
	}
else {goto drain;}
######################################################################
#ENTRYPOINT
die qq{fell out of bounds and eaten by a goto raptor;
(tier: -1, section: } . $stack->[-1] . ')';
#UNARY / WHITESPACE
######################################################################
nomnom:
unless ($input eq '') {
	$input =~ s/^($WHITESPACE*(?:$PREFIX)?|$POSTFIX$WHITESPACE+)//;
	$match = $1 // die "syntax error in s-expression at character $col (±dodgy counters); garbage";
	$col += length $match;
	unless ($input eq '') {
		unless ($match eq '') {
			given (substr $match,0,1) {
				when ($match eq '+') {push @yylval,['POST','++'];}
				when ($match eq '-') {push @yylval,['POST','--'];}
				when ($match eq '!') {push @yylval,['FACT'];}
				default {given (substr $match,-1,1) {
					when ($match eq '+') {push @yylval,['PRE','++'];}
					when ($match eq '-') {
						if ((substr $match,-2,1) eq '-') {
							push @yylval,['PRE','--'];
							}
						else {
							push @yylval,['NEGATIVE'];
							}
					when ($match eq '!') {push @yylval,['NOT'];}
					when ($match eq '~') {push @yylval,['BITNOT'];}
					when ($match eq '>') {push @yylval,['PTR'];}
					default {}
					}
				}
			goto ($stack->[-1]);
			}
		}
	}
######################################################################
#UNARY / WHITESPACE
die qq{fell out of bounds and eaten by a goto raptor;
(tier: 0, section: } . $stack->[-1] . ')';
#TIER 1
######################################################################
s_expr:
unless ($input eq '') {
	$input =~ s/($NUMBER|$NAME|//;
	$match = $1 // die "syntax error in s-expression at character $col (±dodgy counters); garbage";
	$col += length $match;
	unless ($input eq '') {
		unless ($match eq '') {
			if ($match =~ m/$NUMBER/) {goto parsenumber;}
			given (substr $match,0,1) {
				when ($_ =~ m/$SIGAL/) {push @yylval,['VAR',$match];}
				when ($_ =~ m/N/) {goto disambig_n;}
				when ($_ =~ m/t/i) {goto disambig_t;}
				when ($_ =~ m/f/i) {goto disambig_f;}
				when ($_ eq '(') {goto lparen;}
				when ($_ eq ')') {
					pop @stack;
					push @yylval,[')'];
					goto ($stack->[-1]);
					}
				when ($_ eq '{')

					}
				when ($_ eq '}') {
					die "syntax error in s-expression at character $col (±dodgy counters); '}' is not a valid closing character";
					}
				when ($_ eq '[') {

					}
				when ($_ eq ']') {
					die "syntax error in s-expression at character $col (±dodgy counters); ']' is not a valid closing character";
					}
				when ($_ eq "'") {
					unless ((substr $input,0,1) eq "'") {
						push @stack,'qstring'
						push @yylval,["'"];
						goto ($stack->[-1]);
						}
					else {
						$input = substr $input,1;
						$col++;
						push @yylval,['DATA',''];
						}
					}
				when ($_ eq '"') {
					unless ((substr $input,0,1) eq '"') {
						push @stack,'qqstring'
						push @yylval,['"'];
						goto ($stack->[-1]);
						}
					else {
						$input = substr $input,1;
						$col++;
						push @yylval,['DATA',''];
						}
					}
				when ($_ eq ',') {
					unless ((substr $input,0,1) =~ m/[,;]/) {
						push @yylval,[','];
						goto ($stack->[-1]);
						}
					else {
						push @yylval,[','];
						push @yylval,['DATA',0];
						}
					}
				when ($_ eq ';') {
					unless ((substr $input,0,1) =~ m/[,;]/) {
						push @yylval,[';'];
						goto ($stack->[-1]);
						}
					else {
						push @yylval,[';'];
						push @yylval,['DATA',0];
						}
					}
				default {
					push @yylval,['DATA',$match];
					}
				}
			goto ($stack->[-1])
			}
		else {
			die "syntax error in s-expression at character $col (±dodgy counters)"
			}
		}
	else {
		die "syntax error in s-expression near EOF";
		}
	}
else {
	die "syntax error in s-expression at EOF";
	}
######################################################################
die qq{fell out of bounds and eaten by a goto raptor;
(tier: 1, section: } . $stack->[-1] . ')';
######################################################################
m_list:
unless ($input eq '') {
	$input =~ s/$M_LIST//;
	$match = $1 // die "syntax error in m-list at character $col (±dodgy counters); found garbage";
	$col += length $match;
	unless ($input eq '') {
		unless ($match eq '') {
			if ($match =~ m/$NUMBER/) {
				goto parsenumber;
				}
			given (substr $match,0,1) {
				when ($_ =~ m/$SIGAL/) {push @yylval,['VAR',$match];}
				when ($_ eq 'N') {goto disambig_n;}
				when ($_ =~ m/t/i) {goto disambig_t;}
				when ($_ =~ m/f/i) {
					if (uc($match) eq "FALSE") {
					push @yylval,['VAR',uc($match)];
					}
					else {
					push @yylval,['DATA',$match];
					}
				when ($_ eq '(') {
					unless ((substr $input,0,1) eq ')') {
						push @stack,'s_expr'
						push @yylval,['('];
						}
					else {
						$input = substr $input,1;
						$col++;
						}
					}
				when ($_ eq ')') {
					die "syntax error in m-list at character $col (±dodgy counters); ')' is not a valid closing character";
					}
				when ($_ eq '{')
					unless ((substr $input,0,1) eq '}') {
						push @stack,'struct_key'
						push @yylval,['['];
						}
					else {
						$input = substr $input,1;
						$col++;
						push @yylval,['DATA',NULL];
						}
					}
				when ($_ eq '}') {
					die "syntax error in m-list at character $col (±dodgy counters); '}' is not a valid closing character";
					}
				when ($_ eq '[') {
					unless ((substr $input,0,1) eq ']') {
						push @stack,'m_list'
						push @yylval,['['];
						}
					else {
						$input = substr $input,1;
						$col++;
						push @yylval,['DATA',''];
						}
					}
				when ($_ eq ']') {
					pop @stack;
					push @yylval,[']'];
					goto ($stack->[-1])
					}
				when ($_ eq "'") {
					unless ((substr $input,0,1) eq "'") {
						push @stack,'qstring'
						push @yylval,["'"];
						}
					else {
						$input = substr $input,1;
						$col++;
						push @yylval,['DATA',''];
						}
					}
				when ($_ eq '"') {
					unless ((substr $input,0,1) eq '"') {
						push @stack,'qqstring'
						push @yylval,['"'];
						}
					else {
						$input = substr $input,1;
						$col++;
						push @yylval,['DATA',''];
						}
					}
				when ($_ eq ',') {
					unless ((substr $input,0,1) =~ m/[,;]/) {
						push @yylval,[','];
						}
					else {
						push @yylval,[','];
						push @yylval,['DATA',NULL];
						}
					}
				when ($_ eq ';') {
					unless ((substr $input,0,1) =~ m/[,;]/) {
						push @yylval,[';'];
						}
					else {
						push @yylval,[';'];
						push @yylval,['DATA',NULL];
						}
					}
				default {
					push @yylval,['DATA',$match];
					}
				}
			goto ($stack->[-1])
			}
		else {
			die "syntax error in m-list at character $col (±dodgy counters)"
			}
		}
	else {
		die "syntax error in m-list near EOF";
		}
	}
else {
	die "syntax error in m-list at EOF";
	}
######################################################################
die qq{fell out of bounds and eaten by a goto raptor;
(tier: 1, section: } . $stack->[-1] . ')';
######################################################################
struct_val:
unless ($input eq '') {
	$input =~ s/$VALUE//;
	$match = $1 // die "syntax error in struct value at character $col (±dodgy counters); found garbage";
	$col += length $match;
	unless ($input eq '') {
		unless ($match eq '') {
			if ($match =~ m/$NUMBER/) {
				goto parsenumber;
				}
			given (substr $match,0,1) {
				when ($_ =~ m/$SIGAL/) {
					pop @stack;
					push @stack,'struct_sep';
					push @yylval,['VAR',$match];
					}
				when ($_ eq 'N') {
					if ($match eq "NULL") {
					push @yylval,['VAR',$match];
					}
					elsif ($match eq "NIL") {
					push @yylval,['VAR',$match];
					}
					else {
					push @yylval,['DATA',$match];
					}
				when ($_ =~ m/t/i) {
					if (($match eq 'T') || (uc($match) eq "TRUE")) {
					push @yylval,['VAR',uc($match)];
					}
					else {
					push @yylval,['DATA',$match];
					}
				when ($_ =~ m/f/i) {
					if (uc($match) eq "FALSE") {
					push @yylval,['VAR',uc($match)];
					}
					else {
					push @yylval,['DATA',$match];
					}
				when ($_ eq '(') {
					unless ((substr $input,0,1) eq ')') {
						pop @stack;
						push @stack,'struct_sep';
						push @stack,'s_expr';
						push @yylval,['('];
						}
					else {
						pop @stack;
						push @stack,'struct_sep';
						$input = substr $input,1;
						$col++;
						push @yylval,['DATA',OK];
						}
					}
				when ($_ eq ')') {
					die "syntax error in struct value at character $col (±dodgy counters); ')' is not a valid closing character";
					}
				when ($_ eq '{')
					unless ((substr $input,0,1) eq '}') {
						pop @stack;
						push @stack,'struct_sep';
						push @stack,'struct_key'
						push @yylval,['['];
						}
					else {
						pop @stack;
						push @stack,'struct_sep';
						$input = substr $input,1;
						$col++;
						push @yylval,['DATA',NULL];
						}
					}
				when ($_ eq '}') {
					pop @stack;
					push @yylval,['}'];
					}
				when ($_ eq '[') {
					unless ((substr $input,0,1) eq ']') {
						pop @stack;
						push @stack,'struct_sep';
						push @stack,'m_list'
						push @yylval,['['];
						}
					else {
						pop @stack;
						push @stack,'struct_sep';
						$input = substr $input,1;
						$col++;
						push @yylval,['DATA',NIL];
						}
					}
				when ($_ eq ']') {
					die "syntax error in struct value at character $col (±dodgy counters); ']' is not a valid closing character"
					}
				when ($_ eq "'") {
					unless ((substr $input,0,1) eq "'") {
						pop @stack;
						push @stack,'struct_sep';
						push @stack,'qstring'
						push @yylval,['"'];
						}
					else {
						pop @stack;
						push @stack,'struct_sep';
						$input = substr $input,1;
						$col++;
						push @yylval,['DATA',NIL];
						}
					}
				when ($_ eq '"') {
					unless ((substr $input,0,1) eq '"') {
						pop @stack;
						push @stack,'struct_sep';
						push @stack,'qqstring'
						push @yylval,['"'];
						}
					else {
						pop @stack;
						push @stack,'struct_sep';
						$input = substr $input,1;
						$col++;
						push @yylval,['DATA',NIL];
						}
					}
				when ($_ eq ',') {
					unless ((substr $input,0,1) =~ m/[,;]/) {
						pop @stack;
						push @stack,'struct_key';
						push @yylval,[','];
						}
					else {
						$col++
						die "syntax error in struct key at character $col (±dodgy counters), key can't be nil"
						}
					}
			goto ($stack->[-1])
			}
		else {
			die "syntax error in struct value at character $col (±dodgy counters)"
			}
		}
	else {
		die "syntax error in struct value near EOF";
		}
	}
else {
	die "syntax error in struct value at EOF";
	}
######################################################################
die qq{fell out of bounds and eaten by a goto raptor;
(tier: 1, section: } . $stack->[-1] . ')';
######################################################################
struct_key:
unless ($input eq NIL) {
	$input =~ s/$KEY//;
	$match = $1 // die "syntax error in struct key at character $col (±dodgy counters); Not a valid key sequence";
	$col += length $match;
	unless ($input eq NIL) {
		given (substr $match,0,1) {
			when ($_ =~ m/$SIGAL/) {
				pop @stack;
				push @stack,'struct_val';
				push @yylval,['VAR',$match];
				push @yylval,['=>'];
				}
			when ($_ eq 'N') {
				if ($match eq "NULL") {
				die "syntax error in struct key at character $col (±dodgy counters), key can't be the NULL pointer";
				}
				elsif ($match eq "NIL") {
				die "syntax error in struct key at character $col (±dodgy counters), key can't literally be NIL";
				}
				else {
				pop @stack;
				push @stack,'struct_val';
				push @yylval,['DATA',$match];
				push @yylval,['=>'];
				}
			when ($_ =~ m/t/i) {
				if (($match eq 'T') || (uc($match) eq "TRUE")) {
				die "syntax error in struct key at character $col (±dodgy counters), key can't be true, it can't handle the truth!";
				}
				else {
				pop @stack;
				push @stack,'struct_val';
				push @yylval,['DATA',$match];
				push @yylval,['=>'];
				}
			when ($_ =~ m/f/i) {
				if (uc($match) eq "FALSE") {
				die "syntax error in struct key at character $col (±dodgy counters), key can't be false, it must be valid";
				}
				else {
				pop @stack;
				push @stack,'struct_val';
				push @yylval,['DATA',$match];
				push @yylval,['=>'];
				}
			when ($_ eq '(') {
				unless ((substr $input,0,1) eq ')') {
					pop @stack;
					push @stack,'struct_delim';
					push @stack,'s_expr';
					push @yylval,['('];
					}
				else {
					die "syntax error in struct key at character $col (±dodgy counters), key can't be the skip operation";
					}
				}
			default {
				pop @stack;
				push @stack,'struct_val';
				push @yylval,['DATA',$match];
				}
			}
		goto ($stack->[-1]);
		}
	else {
		die "syntax error in struct key near EOF";
		}
	}
else {
	die "syntax error in struct key at EOF";
	}
######################################################################
die qq{fell out of bounds and eaten by a goto raptor;
(tier: 1, section: } . $stack->[-1] . ')';
######################################################################
hash_delim:
pop @stack;
push @stack,'struct_val';
push @yylval,['=>'];
goto ($stack->[-1]);
######################################################################
die qq{fell out of bounds and eaten by a goto raptor;
(tier: 1½, section: } . $stack->[-1] . ')';
######################################################################
seperator:
pop @stack;
push @stack,'struct_val';
push @yylval,['=>'];
goto ($stack->[-1]);
######################################################################
#TIER 1
die qq{fell out of bounds and eaten by a goto raptor;
(tier: 1½, section: } . $stack->[-1] . ')';
#TIER 2
######################################################################
qqstring:
unless ($input eq NIL) {
	$input =~ s/$QQTEXT//;
	$match = $1 // die "lexer is illiterate";
	$col += length $match;
	unless ($input eq NIL) {
		given (substr $match,0,1) {
			when ($_ =~ m/$SIGAL/) {
				push @yylval,['VAR',$match];
				}
			when ($_ eq '"') {
				pop @stack;
				push @yylval,['"'];
			default {
				push @yylval,['DATA',$match];
				}
			}
		goto ($stack->[-1]);
		}
	else {
		die "syntax error in string near EOF";
		}
	}
else {
	die "syntax error in string at EOF";
	}
######################################################################
die qq{fell out of bounds and eaten by a goto raptor;
(tier: 2, section: } . $stack->[-1] . ')';
######################################################################
qstring:
unless ($input eq NIL) {
	$input =~ s/$QTEXT//;
	$match = $1 // die "lexer is illiterate";
	$col += length $match;
	unless ($input eq NIL) {
		given (substr $match,0,1) {
			when ($_ eq "'") {
				pop @stack;
				push @yylval,["'"];
			default {
				push @yylval,['TEXT',$match];
				}
			}
		goto ($stack->[-1]);
		}
	else {
		die "syntax error in exact string near EOF";
		}
	}
else {
	die "syntax error in exact string at EOF";
	}
######################################################################
die qq{fell out of bounds and eaten by a goto raptor;
(tier: 2, section: } . $stack->[-1] . ')';
######################################################################
parsenumber:
if ($match =~ m/([Rr][Aa][Nn][Dd])/) {
	$match = oct($match);
	}
if ($match =~ m/([Dd])/) {
	$match = oct($match);
	}
elif ($match,0,1 eq '0') {
	$match = oct($match);
	}
else {
	$match = $match + 0;
	}
push @yylval,['NUM',$match];
$interger = NULL;
goto ($stack->[-1]);
######################################################################
die qq{fell out of bounds and eaten by a goto raptor;
(tier: 2, section: } . $stack->[-1] . ')';
######################################################################
disambig_n:
if ($match eq "NULL") {
push @yylval,['VAR',$match];
	}
elsif ($match eq "NIL") {
push @yylval,['VAR',$match];
	}
else {
push @yylval,['DATA',$match];
	}
######################################################################
die qq{fell out of bounds and eaten by a goto raptor;
(tier: 2, section: } . $stack->[-1] . ')';
######################################################################
disambig_t:
if (($match eq 'T') || (uc($match) eq "TRUE")) {
	push @yylval,['VAR',uc($match)];
	}
else {
	push @yylval,['DATA',$match];
	}
######################################################################
die qq{fell out of bounds and eaten by a goto raptor;
(tier: 2, section: } . $stack->[-1] . ')';
######################################################################
disambig_f:
if (uc($match) eq "FALSE") {
	push @yylval,['VAR',uc($match)];
	}
else {
	push @yylval,['DATA',$match];
	}
######################################################################
die qq{fell out of bounds and eaten by a goto raptor;
(tier: 2, section: } . $stack->[-1] . ')';
######################################################################
lparen_tok:
if (substr $input,0,9 eq '(void*)0)' {
	$input = substr $input,9;
	push @yylval,['VAR','((void*)0)'];
	}
else {
	unless (substr $input,0,1) eq ')') {
		$input = substr $input,1;
		$col++;
		}
	else {
		push @stack,'s_expr';
		push @yylval,['('];
		}
	}
goto nomnom;
######################################################################
die qq{fell out of bounds and eaten by a goto raptor;
(tier: 2, section: } . $stack->[-1] . ')';
######################################################################
lcurly_tok:
unless ((substr $input,0,1) eq '}') {
	push @stack,'hash_key'
	push @yylval,['{'];
	}
else {
	$input = substr $input,1;
	$col++;
	push @yylval,['DATA',NULL];
	}
goto nomnom;
######################################################################
die qq{fell out of bounds and eaten by a goto raptor;
(tier: 2, section: } . $stack->[-1] . ')';
######################################################################
lbrack_tok:
unless ((substr $input,0,1) eq ']') {
	push @stack,'array'
	push @yylval,['['];
	}
else {
	$input = substr $input,1;
	$col++;
	push @yylval,['DATA',''];
	}
goto nomnom;
######################################################################
#TIER 2
die qq{fell out of bounds and eaten by a goto raptor;
(tier: 2, section: } . $stack->[-1] . ')';
#DRAIN
######################################################################
drain:
return @yylval;
}

