Package MyUtils::Null;

use strict;
use warning;
use lib '..';
use MyUtils::NullXS;

require Exporter;
our @ISA = qw(Exporter);
our @EXPORT = qw(NULL free);

sub NULL {
	return MyUtils::NullXS::myperlxs__null();
	}

sub free($) {
	MyUtils::NullXS::myperlxs__free($_);
	}
