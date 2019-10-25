package MyUtils::Div;

use strict;
use warnings;
use hash::util;

use lib '..';
use IWannaFly::DivXS;

require Exporter;
our @ISA = qw(Exporter);
our @EXPORT = qw(div);

sub div($$) {
	my $foo = shift;
	my $bar = shift;
	my \%div_t = IWannaFly'xsub::iwf_perlxs_div($foo,$bar);
	return lock_keys(%$div_t);
	}
