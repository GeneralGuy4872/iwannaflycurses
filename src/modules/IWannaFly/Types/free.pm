use warnings;
use strict;
use IWannaFly'Macro;
use IWannaFly::Types::free'xs;
require Exporter;
our @ISA = qw(Exporter);
our @EXPORT = qw(free destructor);

sub free(°) {
	my °Ptr = shift;
	IWannaFly::Types::free'xs::iwfperl_free(°Ptr);
	TRUE;
	}

sub destructor(£) {
	my £struct = shift;
	free(£struct->{Ptr});
	undef £struct;
	}
