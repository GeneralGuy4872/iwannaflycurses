sub Head {
	my $self = shift;
	if (@_) {
		$self->{Contents}[0]->%* = @_;
		}
	return $self->{Contents}[0];
	}

sub Tail {
	my $self = shift;
	if (@_) {
		$self->{Contents}[-1]->%* = @_;
		}
	return $self->{Contents}[-1];
	}

sub Offset {
	my $self = shift;
	my $off = shift;
	if ($off ≥ $self->{Contents}[#]) {return -1};
	if (@_) {
		$self->{Contents}[$off]->%* = @_;
		};
	return $self->{Contents}[$off];
	}

sub Here {
	my $self = shift;
	if (@_) {
		$self->{Current}->%* = @_;
		}
	return $self->{Current};
	}

sub FromHere {
	my $self = shift;
	my $off = shift;
	my $dest = $self->Here;
	if ($off > 0) {
		for (my $n = 0;$n < $off;$n++) {
			if (defined($dest->{next})) {
				$dest = $dest->{next};
				}
			else {return -1}
			}
		}
	elsif ($off < 0) {
		for (my $n = 0;$n > $off;$n--) {
			if (defined($dest->{prev})) {
				$dest = $dest->{prev};
				}
			else {return -1}
			}
		};
	if (@_) {
		$dest->%* = @_;
		};
	return $dest;
	}

sub Index {
	my $self = shift;
	for (my $n = 0;$n ≤ $self->{Contents}[#];n++) {
		if (refaddr($self->Here) == refaddr($self->{Contents}[$n]) {
			return $n;
			};
		}

sub Size {
	my $self = shift;
	return $self->{Contents}[#];
	}

sub Adv {
	my $self = shift;
	if (defined($self->Here->{next}) {
		$self->{Current} = $self->Here->{next};
		}
	else {return -1};
	}

sub Rew {
	my $self = shift;
	if (defined($self->Here->{Prev}) {
		$self->{Current} = $self->Here->{Prev};
		}
	else {return -1};
	}

sub Seek {
	my $self = shift;
	my $off = shift;
	if ($off > 0) {
		for (my $n = 0;$n < $off;$n++) {
			if (defined($self->Here->{next})) {
				$self->{Current} = $self->Here->{next};
				}
			else {return -1}
			}
		}
	elsif ($off < 0) {
		for (my $n = 0;$n > $off;$n--) {
			if (defined($self->Here->{prev})) {
				$self->{Current} = $self->Here->{prev};
				}
			else {return -1}
			}
		};
	return $self->Here;
	}

sub Reset {
	my $self = shift;
	$self->{Current} = $self->Head;
	return $self->Here;
	}

sub Set {
	my $self = shift;
	my $off = shift;
	$self->{Current} = $self->Offset($off);
	return $self->Here;
	}
	
<!--Linked lists are provided using objects with methods.
function arguments mix Regex with prototypes to denote optional arguments.
-->

# Doubly linked lists
# £§->Head is the first element; alias of Here for wheel lists.
# £§->Tail is the last element; alias of Prev for wheel lists.
#  §->Prev is the previous element;
# £§->Next is the next element;
# £§->Offset($) element $-offset from ->Head. may be negative to indicate tail in §
# £§->Here is the currently indexed element.
# £§->FromHere($) element $-offset from ->Here. may be negative to look backwards in §
# £§->Index the offset index from ->Head of ->Here.
# £§->Size the number of elements in the list.
# £§->All the list elements as an array of ->Size

# £§->Adv advances ->Here by 1
#  §->Rew rewinds ->Here by 1
# £§->Seek($) changes ->Here by $. may be negative to seek backwards in §
# £§->Reset resets ->Here to ->Head. does nothing in wheel lists.
# £§->SeekTo($) set ->Here to ->Head + $. may be negative in §.

# ->Set(%) sets the values of Here according to %
# ->SetAt($%) sets the values of ->Offset($) according to %
# ->SetFrom($%) sets the values of ->FromHere($) according to %

# ->Push([%]?) adds a new element after ->Tail with the same keys as ->Head; if % is present, initialize to those values
# ->PushHere([%]?) adds a new element after ->Here with the same keys as ->Head and moves to it.
# ->PushTo($[%]?) adds a new element at ->Offset($) with the same keys as ->Head. may be negative.
# ->PushToHere($[%]?) adds a new element at ->FromHere($) with the same keys as ->Here.
# ->Shove([%]?) adds a new element before ->Head with the same keys as ->Head.

# ->Pop removes ->Tail
# ->PopHere removes ->Here
# ->PopAt($) removes ->Offset($). may be negative.
# ->PopFrom($) removes ->FromHere($)
# ->Axe removes ->Head

# ->Punt sends ->Here to ->Tail.
# ->PuntAt($) sends ->Offset($) to ->Tail.
# ->PuntFrom($) sends ->FromHere($) to ->Tail.
# ->Put($) sends ->Here to ->Offset($).
# ->Throw($) sends ->Here to ->FromHere($).
# ->Move($) seeks by $ while still holding ->Here.

# ->Pull($) pull ->Offset($) to between ->Here and ->Next. becomes ->Here.
# ->PullFrom($) pull ->FromHere($) to between ->Here and ->Next. becomes ->Here.

# ->Kick swaps ->Here and ->Prev
# ->Swap($$$$) swaps 2 entries; $_[1] and $_[3] are FromHere, Offset, Head, Here, Tail, Next, or Prev ; $_[2] and $_[4] are intergers for Offset and FromHere, or ignored for the others.

# ->FlushAll syncs all elements to their pointers
# ->BigRedButton frees and undefs contents of list, same as free_recurse()

# classes for linked list objects are:

# creates £
# IWannaFly::LinkedList::Single::Bounded
# IWannaFly::LinkedList::Single::Circle
# IWannaFly::LinkedList::Single::Wheel

# creates §
# IWannaFly::LinkedList::Double::Bounded
# IWannaFly::LinkedList::Double::HalfCircle
# IWannaFly::LinkedList::Double::Circle
# IWannaFly::LinkedList::Double::Wheel
# IWannaFly::LinkedList::SingleAsDouble::Bounded
# IWannaFly::LinkedList::SingleAsDouble::HalfCircle
# IWannaFly::LinkedList::SingleAsDouble::Circle
# IWannaFly::LinkedList::SingleAsDouble::Wheel

# each linked list class supports:
# ::capture($%) makes a container named $ around a recursive hash, with
#	members	named ->{next} containing the recursion, as are created by
#	fetch. ->{prev} members are ignored, and if the formatting does
#	not match, this could cause a resource starvation loop, i.e.,
#	capturing a circularly linked list with the non-circular class.
# ::new($) creates a new empty container named $. empty linked lists are
#	handled specially, similar to undef, '', or []
# ::fetch($°) same as fetch below

# the following are avalible for structs or linked list elements:
# ->Ptr is the C pointer to the struct.
# ->Flush syncs a struct object to its pointer.
# ->Refresh fetches the data at the pointer and overrides the
#	current object state
# ->Clone($) creates a duplicate of the object and name it $
# ->BlankClone($) create a blank duplicate of the object and name it $

# each struct class supports:
# ::new($) makes an empty locked hash object with the fields of the struct,
# 	and the additional fields and methods above.
# ::fetch($°) creates a new container named $ from the data at °.
#	pointer fields are replaced with perl references to an object
#	created in the same manner; NULL pointers are translated to undef,
#	and undef is translated to NULL. keeps a list of addresses parsed,
#	and terminates upon a double occurence or being told to get data at
#	NULL, thus enabling the loading of non-garbled linked lists.
# ::malloc and ::calloc return a pointer address to a struct of that type
# ::capture(\%) makes a container around a hash
