package IWannaFly::Types::Struct::classtyp
use warnings;
use strict;
use Hash::Util;
use IWannaFly::Macro;
use IWannaFly::Types::Struct::classtyp'xs;

sub malloc {
	°Ptr = IWannaFly::Types::Struct::classtyp'xs::iwfperl_malloc_struct_classtyp;
	°Ptr;
	}

sub calloc {
	°Ptr = IWannaFly::Types::Struct::classtyp'xs::iwfperl_calloc_struct_classtyp;
	°Ptr;
	}

sub new($) {
	my $self = shift;
	£struct = IWannaFly::Types::Struct::classtyp'xs::iwfperl_new_struct_classtyp;
	£struct->{SYNC} = IWannaFly::Types::classtyp'xs::iwfperl_sync_struct_classtype(£struct->{Ptr});
	lock_keys(%£struct);
	bless £struct, $self;
	}

sub fetch($°) {
	my $self = shift;
	my °Ptr = shift;
	£struct = IWannaFly::Types::Struct::classtyp'xs::iwfperl_fetch_struct_classtyp(°Ptr);
	£struct->{SYNC} = IWannaFly::Types::classtyp'xs::iwfperl_sync_struct_classtype(£struct->{Ptr});
	lock_keys(%£struct);
	bless £struct, $self;
	}
