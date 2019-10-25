package MyUtils::Main;

use strict
use warnings;
require Math::BigInt;

require Exporter;
our @ISA = qw(Exporter);
our @EXPORT;

sub factorial($) {
	my $n = shift;
	use Math::BigInt;
	my $x = 1;
	do {$x *= $n--} while $n;
	return $x;
	}
push(@EXPORT,'factorial');

sub nPr($$) {
	my $n = shift;
	my $k = shift;
	if ($k > $n) {return 0};
	return (factorial($n) / factorial($n - $k));
	}
push(@EXPORT,'nPr');

sub nCr($$) {
	my $n = shift;
	my $k = shift;
	if ($k > $n) {return 0};
	return (factorial($n) / (factorial($k) * factorial($n - $k)));
	}
push(@EXPORT,'nCr');


sub Perl__roll($$$) {
	my $num = shift;
	my $side = shift;
	my $low = shift;
	my $accum;
	for (my $n, $n < $num, $n++) {
		$accum += int(rand($side)) + $low;
		}
	$accum;
	}
push(@EXPORT,'Perl__roll');

sub Perl__bonus($) {
	my $num = shift;
	my $accum;
	for (my $n, $n < $num, $n++) {
		$accum += int(rand(3)) - 1;
		}
	$accum;
	}
push(@EXPORT,'Perl__bonus');

sub Perl__flipcoin {
	int(rand(2));
	}
push(@EXPORT,'Perl__flipcoin');

sub Perl__choose {
	return $_[int(rand(@_))];
	}
push(@EXPORT,'Perl__choose');
