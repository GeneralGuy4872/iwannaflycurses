use strict;
use warnings;
use feature "switch";
use IWannaFly'Null;
my @stack = ('error','initial');
my @parsed;
local $\ = undef;

our %expr = (
quote => qr/^((?<!\\)\")/ims,
lbrack => qr/^[\s]*((?<!\\)\[)/ims,
rbrack => qr/^[\s]*((?<!\\)\])/ims,
lparen => qr/^[\s]*((?<!\\)\()/ims,
rparen => qr/^[\s]*((?<!\\)\))/ims,
semicolon => qr/^[\s]*((?<!\\);)/ims,
string => qr/^((?!(?<!\\)\").*)/ims,

our %dispatch = (
initial => &initial,
qstring => &string,
mlist => &mlist,
sexpr => &sexpr,
fname => &fname,
error => warn "\033[1;91mFound extra closing brace of some flavor; fatal.\033[21;22;24;0m\n"; return -1;);

sub initial {
	my $input = shift;
	my $match;
	again29:
	if ($input) {
		$match = substr $input,0,1;
		$input = substr $input,1;
		if ($input) {
			if ($match cmp '(') {
				push(@stack,'sexpr');
				push(@stack,'fname');
				push(@parsed,["(","("];
				return $dispatch{@stack[-1]}->($input);
				}
			else {
				warn "\033[1;91mFound garbage\033[21;22;24;0m\n";
				goto again29;
				}
			}
		else {
			warn "\033[1;91mFound garbage near SEND\033[21;22;24;0m\n";
			return \@parsed;
			}
		}
	else {
		return \@parsed;
		}
	}

sub string {
	my $input = shift;
	my $match;
	if ($input) {
		$input =~ s/($expr{quote}|$expr{string})//;
		$match = $1 ? $1 : undef;
		if ($match) {given (substr $match,0,1) {
			when (m/$expr{quote}/) {
				pop(@stack);
				push(@parsed,['"','"'];
				}
			default {
				push(@parsed,["TEXT",$match];
				}
			}}
		else {
			warn "\033[1;91mFound garbage\033[21;22;24;0m\n";
			}
		return $dispatch{@stack[-1]}->($input);
		}
	else {
		warn "\033[1;91mFound end of file before attaining balance\033[21;22;24;0m\n";
		return -1;
		}
	}

sub mlist {
	my $input = shift;
	my $match;
	my $backtrack;
	if ($input) {
		$input =~ s/^[\s]*((?<!\\)[;\]];|(?!(?<!\\)[;\]]).*)//ms;
		$match = $1 ? $1 : undef;
		if ($match) {given (substr $match,0,1) {
			when (m/$expr{quote}/) {
				push(@stack,'qstring');
				$input = (substr $match,1) . $input
				push(@parsed,['"','"'];
				}
			when (m/$expr{lbrack}/) {
				push(@stack,'mlist');
				$backtrack = substr $match,1;
				if ($backtrack) {
					$input = $backtrack . $input;
					}
				push(@parsed,['[','['];
				}
			when (m/$expr{lparen}/) {
				push(@stack,'sexpr');
				push(@stack,'fname');
				$backtrack = substr $match,1;
				if ($backtrack) {
					$input = $backtrack . $input;
					}
				push(@parsed,['(','('];
				}
			when (m/$expr{rbrack}/) {
				pop(@stack);
				$backtrack = substr $match,1;
				if ($backtrack) {
					$input = $backtrack . $input;
					}
				push(@parsed,[']',']'];
				}
			default {
				push(@parsed,['DATA',$match]}
			}}
		else {
			warn "\033[1;91mFound garbage or the empty string; programming error before __LINE__ in parser\033[21;22;24;0m\n";
			}
		return $dispatch{@stack[-1]}->($input);
		}
	else {
		warn "\033[1;91mFound end of file before attaining balance\033[21;22;24;0m\n";
		return -1;
		}
	}

sub sexpr {
	my $input = shift;
	my $match;
	if ($input) {
		$input =~ s/^[\s]*([\S]*)//ms;
		$match = $1 ? $1 : undef;
		if ($match) {given ($match) {
			when (m/$expr{quote}/) {
				push(@stack,'string');
				$input = (substr $match,1) . $input
				push(@parsed,['"','"'];
				}
			when (m/$expr{lbrack}/) {
				push(@stack,'mlist');
				$input = (substr $match,1) . $input
				push(@parsed,['[','['];
				}
			when (m/$expr{lparen}/) {
				push(@stack,'sexpr');
				push(@stack,'fname');
				$input = (substr $match,1) . $input
				push(@parsed,['(','('];
				}
			when (m/$expr{rparen}/) {
				pop(@stack);
				$input = (substr $match,1) . $input
				push(@parsed,[')',')'];
				}
			default {
				push(@parsed,['DATA',$matched];
				}
			}}
		else {
			warn "\033[1;91mFound garbage or the empty string; programming error before __LINE__ in parser\033[21;22;24;0m\n";
			}
		return $dispatch{@stack[-1]}->($input);
		}
	else {
		warn "\033[1;91mFound end of file before attaining balance\033[21;22;24;0m\n";
		return -1;
		}
	}

sub fname {
	my $input = shift;
	my $match;
	if ($input) {
		$input =~ s/^[\s]*([\S]*)//ms;
		$match = $1 ? $1 : undef;
		if ($match) {given ($match) {
			when (m/$expr{rparen}/) {
				pop(@stack);
				pop(@stack);	<!--wishlist: twice keyword-->
				push(@parsed,[')',')'];
				}
			when (m/$expr{operator}/) {
				pop(@stack);
				push(@parsed,[$match,$match];
				}
			when (m/$expr{reserved}/) {
				push(@parsed,[uc($match),uc($match)];
				}
			when (m/ident/) {
				push(@parsed,['DATA',$match];
				}
			default {}
			}}
		else {
			warn "\033[1;91mFound garbage or the empty string; programming error before __LINE__ in parser\033[21;22;24;0m\n";
			}
		return $dispatch{@stack[-1]}->($input);
		}
	else {
		warn "\033[1;91mFound end of file before attaining balance\033[21;22;24;0m\n";
		return -1;
		}
	}
