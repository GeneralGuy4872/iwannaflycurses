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

# £foo is a singly linked list
# §bar is a doubly linked list
# ¤qux is a C pointer
# ¶zot is a regex

