package IWannaFly'Macro;

use warnings;
use strict;
use boolean;
use Scalar::Utils;
use Filter::Simple;

FILTER_ONLY
	code => sub { s/<!--(?:(?!-->).*)-->//g };
FILTER_ONLY
	code => sub { s/≤/<=/g };
FILTER_ONLY
	code => sub { s/≥/>=/g };
FILTER_ONLY
	code => sub { s/NaN/"NaN"/ig };
FILTER_ONLY
	code => sub { s/(-?)INF(INITY)?/"$1Inf"/ig };
FILTER_ONLY
	code => sub { s/T(RUE|rue)/true/g };
FILTER_ONLY
	code => sub { s/F(ALSE|alse)/false/g };
FILTER_ONLY
	code => sub { s/NIL/''/g };
FILTER_ONLY
	code => sub { s/¤/\$/g };
FILTER_ONLY
	code => sub { s/°/\$/g };
FILTER_ONLY
	code => sub { s/¢/\$/g };
FILTER_ONLY
	code => sub { s/£/\$/g };
FILTER_ONLY
	code => sub { s/€/\$/g };
FILTER_ONLY
	code => sub { s/§/\$/g };
FILTER_ONLY
	code => sub { s/♯/\$/g };
FILTER_ONLY
	code => sub { s/‽(\()?/refaddr$1 /g };
FILTER_ONLY
	code => sub { s/OK(AY)?/0/g };
FILTER_ONLY
	code => sub { s/OKAY/0/ig };
FILTER_ONLY
	code => sub { s/ERR/-1/ig };
FILTER_ONLY
	code => sub { s/«((?!»).*)»[\t]+:\(([\w]+)\)$/$1;\n\tgoto $2;\n/g };
FILTER_ONLY
	code => sub { s/«((?!»).*)»[\t]+:S\(([\w]+)\)F\(([\w]+)\)\n$/if ( $1 ) {\n\tgoto $2;\n} else {\n\tgoto $3;\n}/g };
FILTER_ONLY
	code => sub { s/: int;/: optimize(int);/g };
