package MyUtils::Macro;

use warnings;
use strict;
use Filter::Simple;
require Exporter;
our @ISA = qw(Exporter);
our @EXPORT = qw(NAN INFINITY OK ERR π noop MAX MIN SGN CLAMP);

use constant INFINITY => 'Inf';
use constant NAN => 'NaN';
use constant OK => 0;
use constant ERR => -1;
use constant π = 4 * atan2(1,1);

sub noop {}
sub MAX($$) {return (( $_[0] ≥ $_[1] ) ? $_[0] : $_[1])}
sub MIN($$) {return (( $_[0] ≤ $_[1] ) ? $_[0] : $_[1])}
sub SGN($) {return ($_ <=> 0)}
sub CLAMP($$$) {return MIN( MAX( $_[0],$_[1] ),$_[2] )}

FILTER_ONLY
	code_no_comments => sub { s/≤/<=/g },
	code_no_comments => sub { s/≥/>=/g },
	code_no_comments => sub { s/¤/\$/g },
	code_no_comments => sub { s/£/\$/g },
	code_no_comments => sub { s/§/\$/g },
	code_no_comments => sub { s/¶/\$/g },
	code_no_comments => sub { s/T(?:rue|RUE)/true/g },
	code_no_comments => sub { s/F(?:alse|ALSE)/false/g },
	code_no_comments => sub { s/forever/for (;;)/gm };
