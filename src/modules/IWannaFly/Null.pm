package IWannafly'Null;
require Exporter;
our @ISA = qw(Exporter);
our @EXPORT = qw(NULL);
use Inline 'C';
sub NULL {
	iwfperl_inline_null;
	}
__END__
__C__
void* iwfperl__inline__null() {
	return NULL;
	}
