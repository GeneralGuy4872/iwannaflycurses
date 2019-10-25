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
	
# Linked lists are provided using objects with methods:
# ->Head is the first element; or an alias of ->Here for ¢ and §
# ->Tail is the last element, an alias of ->Here->{prev} for §, or a cached node whose ->{next} is equal to ->Here for ¢
# ->Offset($) element $-offset from ->Head
# ->Here is the currently indexed element.
# ->FromHere($) element $-offset from ->Here
# ->Index the offset index from ->Head of ->Here. always 0 for § and ¢.
# ->Size the number of elements in the list.

# ->Adv advances ->Here by 1
# ->Rew rewinds ->Here by 1
# ->Seek($) changes ->Here by $
# ->Reset resets ->Here to ->Head.
# ->Set($) set ->Here to ->Head + $.

# ->Push adds a new element after ->Tail with the same keys as ->Head.
# ->PushHere adds a new element after ->Here with the same keys as ->Head and moves to it.
# ->PushTo($) adds a new element at ->Offset($) with the same keys as ->Head.
# ->PushToHere($) adds a new element at ->FromHere($) with the same keys as ->Head.
# ->Shove adds a new element before ->Head with the same keys as ->Head.

# ->Pop removes ->Tail, or the node immidiately before ->Here for § and ¢
# ->PopHere removes ->Here
# ->PopAt($) removes ->Offset($)
# ->PopFrom($) removes ->FromHere($)
# ->Axe removes ->Head

# ->Punt sends ->Here to ->Tail (Do not pass go do not collect 200 scalars.) Alias of ->Adv for §
# ->PuntAt($) sends ->Offset($) to ->Tail
# ->PuntFrom($) sends ->Fromhere($) to ->Tail, or to before ->Here for § and ¢
# ->Put($) sends ->Here to ->Offset($)
# ->Throw($) sends ->Here to ->FromHere($)
# ->Move($) seeks by $ while still holding ->Here

# ->Pull($) pull ->Offset($) to before ->Here
# ->PullFrom($) pull ->FromHere($) to before ->Here

# ->Flip($) swaps ->FromHere($) and ->Here
# ->Flop($) swaps ->Offset($) and ->Here
# ->Swap swaps ->Tail and ->Here.
# ->Switch swaps ->Head and ->Here.
# any combination of (Flip|Flop|Swap|Switch)(Flip|Flop|Swap|Switch) except (Swap|Switch)(Swap|Switch) swap the non-here elements, with the args in that order.

# ->FlushAll syncs all elements to their pointers

# classes for linked list objects are:
# IWannaFly'LinkedList::Single
# IWannaFly'LinkedList::SingleCircle
# IWannaFly'LinkedList::Double
# IWannaFly'LinkedList::DoubleHalf
# IWannaFly'LinkedList::DoubleCircle

# each linked list class supports:
# ::capture(%) makes a container around a recursive hash, with members
# 	named ->{next} containing the recursion, as are created by the
# 	data file parsers. ->{prev} members may be overwritten, and if
# 	the formatting does not match, this could cause a resource
# 	starvation loop, i.e., capturing a circularly linked list with
# 	the non-circular class.

# the following are avalible for structs or linked list elements:
# ->{Ptr} is the C pointer to the struct.
# ->Flush syncs a struct object to its pointer.

# each struct class supports:
# ::new makes an empty locked hash object with the fields of the struct,
# 	the additional field ->{Ptr}, and the method ->SYNC.
# ::fetch(°) creates a new container from the data at °. pointer fields
# 	are replaced with perl references to an object created in the same
#	manner; null pointers are translated to undef, and undef is
#	translated to null.
# ::malloc and ::calloc return a pointer address to a struct of that type
# ::capture(\%) makes a container around a hash
