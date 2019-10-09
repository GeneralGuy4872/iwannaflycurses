package IWannaFly::Main;
use lib '..';
use strict;
use warnings;

use IWannaFly::Struct;
use IWannaFly'Macro;
use IWannaFly'Null;
require Exporter;
our @ISA = qw(Exporter);
our @EXPORT;

<!--keep track of what's where in local modules
with :: for directories and ' for files-->

# £foo is a singly linked list object
# ¢fie is a singly, circularly linked list object
# ♮bam is a doubly linked list
# €baz is a doubly, half-circularly linked list
# §qux is a doubly, circularly linked list
# ¤zot is a reference
# ¶xyz is a regex

# Linked lists are provided using objects:
# ->Head is the first element; or an alias of ->Here for ¢ and §
# ->Tail is the last element, or an alias of ->Here->{prev} for §, or the ref whose ->{next} is equal to ->here for ¢
# ->Offset($) element $-offset from ->Head
# ->Here is the currently indexed element
# ->FromHere($) element $-offset from ->Here

# ->Adv advances ->Here by 1
# ->FFwd($) advances ->Here by $
# ->Back rewinds ->Here by 1
# ->Rew($) rewinds ->Here by $
# ->Reset resets ->Here to ->Head.
# ->Set($) set ->Here to ->Head + $.

# ->Push adds a new element after ->Tail
# ->PushHere adds a new element at ->Here
# ->PushAt($) adds a new element at ->Offset($)
# ->PushTo($) adds a new element at ->FromHere($)

# ->Pop removes ->Tail, or the node immidiately before ->Here for §
# ->PopHere removes ->Here
# ->PopAt($) removes ->Offset($)
# ->PopFrom($) removes ->FromHere($)

# ->Punt sends ->Here to ->Tail (Do not pass go do not collect 200 scalars.) Alias of ->Adv for §
# ->PuntAt($) sends ->Offset($) to ->Tail
# ->PuntFrom($) sends ->Fromhere($) to ->Tail, or to before ->Here for §

# The hashes in the objects are maintained as references.

# classes for the objects are:
# IWannaFly::LinkedList::Single
# IWannaFly::LinkedList::SingleCircle
# IWannaFly::LinkedList::Double
# IWannaFly::LinkedList::DoubleHalf
# IWannaFly::LinkedList::DoubleCircle

# each class supports:
# ::new makes an empty container with the methods above
# ::capture(\%) makes a container around a recursive hash, with members named
# ->{next} containing the recursion, as are created by the data file parsers.
# ->{prev} members may be overwritten, and if the formatting does not match,
# this could invoke the halting problem, i.e., capturing a circularly linked
# list with the non-circular class

<!--This is a comment. comments are comments-->

sub MAX($$) {return ($_[0] ≥ $_[1] ? $_[0] : $_[1])}
push(@EXPORT,'MAX');

sub MIN($$) {return ($_[0] ≤ $_[1] ? $_[0] : $_[1])}
push(@EXPORT,'MIN');

sub SGN($) {$_ <=> 0}
push(@EXPORT,'SGN');

sub INTVL($$$) {return MIN( MAX( $_[0],$_[1] ) ,$_[2] )}
push(@EXPORT,'INTVL');

