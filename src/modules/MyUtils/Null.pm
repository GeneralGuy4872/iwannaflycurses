Package MyUtils::Null;

use strict;
use warning;
use lib '..';
use MyUtils::NullXS;

require Exporter;
our @ISA = qw(Exporter);
our @EXPORT = qw(NULL free freeItr);

sub NULL {
	return MyUtils::NullXS::myperlxs__null();
	}

sub free($) {
	MyUtils::NullXS::myperlxs__free($_);
	}

sub freeItr {
	my $arg = shift;
	my $error = 0;
	foreach (keys %$arg) {
		if (reftype($arg->{$_}) eq 'HASH') {
			recursivefree($arg->{$_});
			}
		else {
			$error++;
			}
		}
	unless ($error) {
		if (exists($arg->{Ptr})) {
			free($arg->{Ptr});
			}
		}
	return $error;
	}
