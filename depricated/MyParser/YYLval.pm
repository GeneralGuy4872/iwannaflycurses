package IWannaFly::MyParser'YYLval;
use strict;
use warnings;

our @yylval;

getval {
	my \@pair = shift @yylval;
	return (($pair[1] // ''),($pair[2] // undef))
	}
