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

# this program uses tight integration between C and Perl,
# using what I am terming "Black Magic" scalars
# (following the theme of the perl internal docs),
# as they are have the potential to aquire...ultimate power.
#
# the interaction these functions is Thus:
#
# C <+> Perl <+> C
#    \________/
#
# The XSUB is able to _leak_ newly created variables back to the
# grandparent C program by throwing them on the heap. in theory.
# It may instead anger the MMU, but there should be ways around this...
# (Thread safety? what's that?)
# I call this tunneling.
#
# These scalars will use special sigils:
#
# £foo is a complicated struct object ref
# ¢foo is a singly, circularly linked list
# €foo is a doubly, half-circularly linked list object
# §foo is a doubly, circularly linked list object
#
# any struct pointer fields are converted to hash objects.
# a Ptr field and a SYNC method will be added to these objects.
#
# Similarly, prev, next, or other pointer fields may be NULL
# (a Filter::Simple macro in IWannaFly'Null, which wrapps the C NULL),
# and ANY field may be undef or absent if it is to be untouched.
# circularly linked list iteration is terminated when
# $HEAD->Ptr == $CURR->next->Ptr
# all other linked list iteration is terminated when
# !$CURR->next
#
# more mundane sigils are also added:
#
# ¤bar  is a reference
# °bar  is a C pointer
# ♯bar  is a bitfield or boolean
# ‽$bar is the refaddr function
# 
# all these extra sigils except ‽ are processed to $ by
# Filter::Simple in IWannaFly::Macro. they mearly provide
# disambiguation of special scalars/fields while inspecting code.
# since THEY ARE ALL INTERCHANGEABLE WITH EACHOTHER AND $, their usage
# is akin to a footnote comment that referrs back here.
# when declaring a new ♯, you should use it with ": optimize(int);"
# from optimize::int, or the Filter::Simple macro for it in
# IWannaFly'Macro, which is simply ": int;"
# 
# scalars generated from primatives will require a complementery pointer
# to be provided in order to be synced, while this is built in to the
# object resulting from a struct.
#
# modules for providing type support will be provided.
# every type will provide an assciated class.
# they will provide malloc, calloc, new, and fetch(°)
# these must be called by full name.
#
# ::malloc and ::calloc are wrappers for the C functions.
# they create a tunnelable heap object and pass the pointer
#
# ::new creates a blank object
#
# ::fetch(°ptr) creates a hash or scaler from a given °ptr
#
# once an object is created, a ->SYNC method will be created for it,
# which writes to ->Ptr
#
# fields which contain circularly linked lists may call IndexFwd and
# IndexBack on the reference itself to change the object pointed to.
# calling this on a half-circularly linked list will break it.
# calling IndexFwd on a Singly linked list creates a memory leak,
# calling IndexBack on a Singly linked list is a Bad Idea.
#
# free(♯Ptr) is untyped, and provided blessed.

<!--This is a comment. comments are comments-->

sub MAX($$) {return ($_[0] ≥ $_[1] ? $_[0] : $_[1])}
push(@EXPORT,'MAX');

sub MIN($$) {return ($_[0] ≤ $_[1] ? $_[0] : $_[1])}
push(@EXPORT,'MIN');

sub SGN($) {$_ <=> 0}
push(@EXPORT,'SGN');

sub INTVL($$$) {return MIN( MAX( $_[0],$_[1] ) ,$_[2] )}
push(@EXPORT,'INTVL');

<!-- MOVE THIS
sub DLLIST_NOCIRC_PUSH(€€) {
	my (€HEAD,€PUSHY) = @_;
	€PUSHY->prev = €HEAD->prev;
	€PUSHY->prevptr = €HEAD->prevptr;
	€HEAD->prev->next = €PUSHY;
	€HEAD->prev->nextptr = €PUSHY->ptr;
	€PUSHY->next = undef;
	€PUSHY->nextptr = NULL;
	€HEAD->prev = €PUSHY;
	€HEAD->prevptr = €PUSHY->ptr;
	}

sub DLLIST_NOCIRC_FREE(€€) {
	my (€HEAD,€DEAD) = @_;
	if (‽€HEAD->prev == ‽€DEAD) {
		€HEAD->prev = €HEAD->prev->prev;
		€HEAD->prev->next = undef;
		€HEAD->prev->nextptr = NULL;
		}
	elsif (addrof(€HEAD) == addrof(§DEAD)) {
		unless ((!€HEAD->next) || (€HEAD->next == NULL)) {
			€HEAD = €HEAD->next;
			€HEAD->prev = €DEAD->prev;
			€HEAD->prevptr = €DEAD->prevptr;
			}
	else {
		€DEAD->next->prev = €DEAD->prev;
		€DEAD->next->prevptr = €DEAD->prevptr;
		€DEAD->prev->next = €DEAD->next;
		€DEAD->prev->nextptr = €DEAD->nextptr;
		€DEAD->prev->next = €DEAD->next;
		}
	free(€DEAD);
	}
-->
