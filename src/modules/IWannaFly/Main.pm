package IWannaFly::Main;

use strict;
use warnings;
use Acme::Comment type=>'HTML';

use lib '..';
use MyUtils::Null;
use MyUtils::Macro;
use MyUtils::Div;
use IWannaFly::Constants;
use IWannaFly::Paths;

require Exporter;
our @ISA = qw(Exporter);
our @EXPORT;

# this is a comment
<!--this is also a comment.
all comments are comments-->

# ‰foo is a hash ref or struct
# £foo is a singly linked list object
# ¢fie is a singly, circularly linked list object
# ♮bam is a doubly linked list
# €baz is a doubly, half-circularly linked list
# §qux is a doubly, circularly linked list
# ¤zot is a reference
# °abc is a C pointer
# ¶zyz is a regex

