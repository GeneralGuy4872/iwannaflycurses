#!/bin/sh
while getopts ":I:o:" opt; do
  case $opt in
    I)
	perlpp_include="$OPTARG"
    ;;
    p)
	perlpp_outfile="$OPTARG"
    ;;
    \?)
	echo "Invalid option -$OPTARG" >2
	undef perpp_include
	undef perpp_outfile
	exit 1
    ;;
  esac
done
if [ -z "$perlpp_include" ]
	then
	if [ -z "$perlpp_outfile" ]
	then
		gpp -I $perlpp_include -o $perlpp-outfile --nostdinc --warninglevel 0 -n -U "" "" "(" "," ")" "(" ")" "♯" "" -M "♯" "\n" " " " " "\n" "" "" +c "/*" "*/" +c "//" "\n" +c "\\\n" "" +s "`" "`" "\\" +s "'" "'" "\\" +s "s(" ")" "\\"
	else
		gpp -I $perlpp-include --nostdinc --warninglevel 0 -U -n "" "" "(" "," ")" "(" ")" "♯" "" -M "♯" "\n" " " " " "\n" "" "" +c "/*" "*/" +c "//" "\n" +c "\\\n" "" +s "`" "`" "\\" +s "'" "'" "\\" +s "s(" ")" "\\"
	fi
else
	if [ -z "$perlpp_outfile" ]
	then
		gpp -o $perlpp-outfile --nostdinc --warninglevel 0 -n -U "" "" "(" "," ")" "(" ")" "♯" "" -M "♯" "\n" " " " " "\n" "" "" +c "/*" "*/" +c "//" "\n" +c "\\\n" "" +s "`" "`" "\\" +s "'" "'" "\\" +s "s(" ")" "\\"
	else
		gpp --nostdinc --warninglevel 0 -U -n "" "" "(" "," ")" "(" ")" "♯" "" -M "♯" "\n" " " " " "\n" "" "" +c "/*" "*/" +c "//" "\n" +c "\\\n" "" +s "`" "`" "\\" +s "'" "'" "\\" +s "s(" ")" "\\"
	fi
fi
undef perlpp_include
undef perlpp_outfile
exit 0
