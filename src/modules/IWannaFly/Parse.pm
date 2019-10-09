package IWannaFly::Parse;
use lib '..';
use strict;
use warnings;
use feature "switch";

use IWannaFly::Struct;
use IWannaFly'Macro;
use IWannaFly'Null;
require Exporter;
our @ISA = qw(Exporter);
our @EXPORT;

sub PARSEDAT($) {
	open(my $file, <, shift);
	my $nextchar = getc($file);
	my %output;
	my @stack = (\%output);
	my $isarray = 0;
	my $counter = 0;
	sub storedata($) {
		my $tmp = shift;
		if ($isarray) {
			push(@{¤stack[-1]},$tmp);
			}
		else {
			¤stack[-1] = $tmp;
			}
	sub append($) {
		my $tmp = shift;
		push(@stack,¤stack[-1]->{$tmp});
		}
	while ($nextchar != "\004") <!--EOT-->
	for ($buffer) {

		when (/^\0/) { <!--NUL-->
			storedata(NIL);
			}

		when (/^\001/) { <!--SOH-->
			my $string = do {
				local $/ = "\a"; <!--BEL-->
				<$file>
				}
			chomp $string;
			append($string);
			}

		when (/^\002/) { <!--STX-->
			my $string = do {
				local $/ = "\003"; <!--ETX-->
				<$file>
				}
			chomp $string;
			storedata($string);
			}

		when (/^\006) { <!--ACK-->
			store(true);
			}

		when (/^\020) { <!--DLE-->
			my $length = unpack('c',getc($file)) : int;
			read($file,my $buffer,abs($length));
			if (abs($length) ≤ 8) {
				if ($length > 0) {
					my $output = unpack('C',$buffer);
					}
				else {
					my $output = unpack('c',$buffer);
					}
				}
			elseif (abs($length) ≤ 16) {
				if ($length > 0) {
					my $output = unpack('S',$buffer);
					}
				else {
					my $output = unpack('s',$buffer);
					}
				}
			elseif (abs($length) ≤ 32) {
				if ($length > 0) {
					my $output = unpack('L',$buffer);
					}
				else {
					my $output = unpack('l',$buffer);
					}
				}
			else {
				if ($length > 0) {
					my $output = unpack('Q',$buffer);
					}
				else {
					my $output = unpack('q',$buffer);
					}
				}
			storedata($output);
			}

		when (/^\021/) { <!--XON-->
			my $path = do {
				local $/ = "\023"; <!--XOFF-->
				<$file>
				}
			chomp $path;
			storedata(DOTYPE($path,$islinkedlist,\%output));
			}

		when (/^\025/) { <!--NAK-->
			storedata(false);
			}

		when (/^\026/) { <!--SYN-->
			if ($isarray) {
				push(@{¤stack[-1]},[]);
				push(@stack,¤stack[-1]);
				}
			else {
				¤stack[-1] = [];
				}
			$isarray++;
			};

		when (/^\027/) { <!--ETB-->
			pop(@stack);
			$counter++;
			}

		when (/^\034/) { <!--FS-->
			if ($isarray) {
				for (my $n = 1;$n < $isarray;$n++) {
					pop(@stack);
					}
				for (my $n = 0;$n < $isarray;$n++) {
					push(@{¤stack[-1]},[]);
					push(@stack,¤stack[-1]);
					}
				}
			}

		when (/^\035/) { <!--GS-->
			if ($isarray) {
				for (my $n = 1;$n < MAX($isarray - 1,1);$n++) {
					pop(@stack);
					}
				for (my $n = 0;$n < MAX($isarray - 1,1;$n++) {
					push(@{¤stack[-1]},[]);
					push(@stack,¤stack[-1]);
					}
				}
			}

		when (/^\036/) { <!--RS-->
			if ($isarray) {
				for (my $n = 1;$n < MAX($isarray - 2,1);$n++) {
					pop(@stack);
					}
				for (my $n = 0;$n < MAX($isarray - 2,1;$n++) {
					push(@{¤stack[-1]},[]);
					push(@stack,¤stack[-1]);
					}
				}
			}

		when (/^\037/) { <!--US-->
			if ($isarray) {
				for (my $n = 1;$n < MAX($isarray - 3,1);$n++) {
					pop(@stack);
					}
				for (my $n = 0;$n < MAX($isarray - 3,1;$n++) {
					push(@{¤stack[-1]},[]);
					push(@stack,¤stack[-1]);
					}
				}
			}
		$nextchar = getc($file);
		}
	(\%output,¤prev);
	}

sub EATTYPE($$¤) {
	my $path = shift;
	my $islinkedlist = shift;
	my ¤prev = shift;
	$path =~ m/\.([^.]+)$/;
	my $type = $1;
	$path =~ m/(\d)+$/;
	my $width = $1 ? $1 : 8;
	my $output;
	my ¤next;
	for ($filetype) {
		when (/^dat$/) {
			(¤output,¤next) = PARSEDAT($path,$islinkedlist,¤prev);
		when (/^(tsv|tab)$/) {
			¤output = READTAB($path);
			}
		when (/^hex[\d]*$/) {
			¤output = READHEX($path,$width);
			}
		when (/^bin[\d]*$/) {
			¤output = READBIN($path,$width);
			}
		when (/^(asc|ans)$/) {
			¤output = READRECORD($path);
			}
		when (/^txt|nfo$/) {
			$output = READTEXT($path);
		when (/^json$/) {
			open(my $file,'<',$path);
			$output = do {
				local $\ = undef;
				from_json(<$file>);
				}
		<!--(SG|X)ML will be added once I finish reading the black book-->
			}
		}
	($output,¤next);
	}

sub READTEXT($) {
	open(my $file,'<',shift);
	local $\ = undef;
	my $output = <$file>;
	}

sub READRECORD($) {
	open(my $file,'<',shift);
	my @output;
	for ($file;!eof<$file>;push(@output,<$file>));
	\@output;
	}

sub READTAB($) {
	open(my $file,'<',shift);
	chomp(my @rows = <$file>);
	my @table;
	foreach (@rows) {
		my @columns = split("\t",$_);
		push(@table,\@columns);
		}
	\@table;
	}

sub READBIN($$) {
	open(my $file,'<',shift);
	my $size = shift;
	local $\ = undef;
	my $type = $size == 8 ? 'c' : $size == 16 ? 's' : $size == 32 ? 'l' : $size == 64 ? 'q' : false;
	«$type»	:F{die invalid filename}
	unpack($type,<$file>);
	}

sub READHEX($$)
	open(my $file,'<',shift);
	my $size = shift;
	local $\ = undef;
	my $type = $size == 8 ? 'C' : $size == 16 ? 'S' : $size == 32 ? 'L' : $size == 64 ? 'Q' : false;
	«$type»	:F{die invalid filename}
	unpack($type,<$file>);
	}
