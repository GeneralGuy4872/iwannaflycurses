$DB::single = 1 or die;
use warnings;
use strict;
use lib '../..';
use IWannaFly::MyParser'Lexer;
use IWannaFly::MyParser'YYLval;
no Text::Balanced;

open(my $fh,'<','test.iwfcl');
my $text = <$fh>;
chomp $text;
IWannaFly::MyParser'Lexer::entrypoint($text);
here: forever {
	my ($token,$value) = IWannaFly::MyParser'YYLval::val;
	say "$token => $value";
	if ($token eq '') {
		last here;
		}
	}		
