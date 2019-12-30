**prealpha stats:**
- ➤ *outline*
- ➤ *implementation*
- ⌛ syntax fixing
- ⌛ debugging
- ⌛ alpha release

**build stats:**
- last working build : NULL
	- 0 total

- last faulty build : NULL
- last failed build : NULL

Iwannafly
=========
*roguelike game library written in C and Perl with extension interface useing minimal external propagating dependencies*

## Dependencies:

(under construction)
<!--
Build Deps:
- Command <CODE>cp</CODE>
- Command <CODE>ls</CODE>
- Command <CODE>sh</CODE>
- Command <CODE>cc</CODE>
- Command <CODE>ld</CODE>
- Command <CODE>sed</CODE>
- Command <CODE>awk</CODE> (maybe?)
- Command <CODE>perl</CODE>
- Command <CODE>flex</CODE>
- Command <CODE>byacc</CODE>
- Command <CODE>make</CODE>
- Perl module <CODE>Module::Build</CODE>
- Perl module <CODE>ExtUtils::MakeMaker</CODE>
- Perl module <CODE>Parse::Yapp</CODE>

Build Recommends:
- Command <CODE>uname</CODE>
- Command <CODE>cpan</CODE>

Depends:
- UTF-8 Console Support
- C library <CODE>\<stdlib.h\></CODE>
- C library <CODE>\<stdio.h\></CODE>
- C library <CODE>\<stdbool.h\></CODE>
- C library <CODE>\<stdint.h\></CODE>
- C library <CODE>\<math.h\></CODE>
- C library <CODE>\<limits.h\></CODE>
- C library <CODE>\<time.h\></CODE>
- C library <CODE>\<string.h\></CODE>
- C library <CODE>\<ctype.h\></CODE>
- C library <CODE>\<uchar.h\></CODE>
- C library <CODE>\<dlfcn.h\></CODE>
- C library <CODE>\<unistd.h\></CODE>
- C library <CODE>\<signal.h\></CODE>
- C library <CODE>\<locale.h\></CODE>
- C library <CODE>\<regex.h\></CODE> (probably)
- C library <CODE>\<glob.h\></CODE> (probably)
- C library <CODE>\<sys/types.h\></CODE> (maybe?)
- C library <CODE>\<sys/ioctl.h\></CODE> (maybe?)
- C library <CODE>\<fcntl.h\></CODE> (probably)
- C library <CODE>\<sys/stat.h\></CODE> (probably)
- C library <CODE>\<errno.h\></CODE> (maybe?)
- C library <CODE>\<rpc/rpc.h\></CODE>
- C library <CODE>\<libtar.h\></CODE>
- C library <CODE>\<zlib.h\></CODE>
- C library <CODE>\<libbz2.h\></CODE>
- C library <CODE>\<ncursesw/ncurses.h\></CODE>
- C library <CODE>\<menu.h\></CODE> (maybe?)
- C library <CODE>\<forms.h\></CODE> (maybe?)
- C library <CODE>\<EXTERN.h\></CODE>
- C library <CODE>\<perl.h\></CODE>
- C library <CODE>"XSUB.h"</CODE>
- C library <CODE>"INLINE.h"</CODE>
- Perl feature <CODE>"switch"</CODE>
- Perl module <CODE>boolean</CODE>
- Perl module <CODE>Exporter</CODE>
- Perl module <CODE>Scalar::Util</CODE>
- Perl module <CODE>Hash::Util</CODE>
- Perl module <CODE>FastGlob</CODE> (maybe?)
- Perl module <CODE>goto::file</CODE>
- Perl module <CODE>Data::Dumper</CODE>
- Perl module <CODE>JSON</CODE>
- Perl module <CODE>Config::Tiny</CODE>
- Perl module <CODE>Filter::Simple</CODE>
- Perl module <CODE>Math::RPN</CODE>
- Perl module <CODE>Tie::File</CODE>
- Perl module (<CODE>XS</CODE>|<CODE>Dyna</CODE>)<CODE>Loader</CODE>
- Perl module <CODE>POSIX qw(ceil floor strfdate)</CODE>
- Perl module <CODE>Acme::Comment</CODE>

Recommends:
- Command <CODE>xterm</CODE> (UTF-8, Color)
- Font <CODE>-Misc-Fixed-Medium-R-SemiCondensed--13-120-75-75-C-60-ISO10646-1</CODE>

Doc Depends:
- Command <CODE>man</CODE>
- Command <CODE>info</CODE>
- Command <CODE>perldoc</CODE>

Doc Build Deps:
- Command <CODE>mandb</CODE>
- Command <CODE>makeinfo</CODE>
- Command <CODE>install-info</CODE>
- Command <CODE>make</CODE>
- Command <CODE>perl</CODE>
- Command <CODE>cp</CODE>
- Perl module <CODE>Module::Build</CODE>

Doc Recommends:
- Command <CODE>xdvi</CODE>
- Command <CODE>texi2dvi</CODE>
-->

NEWS (and Olds)
---------------

Mixed line endings are intentional.

As of 28/10/2019, major changes to some of the oldest portions of the
outline are underway. these changes need to be propogated through the
entire project, and will result in major inconsistancies until finished.
once they are, work will begin twords the renderer, then a shakedown test
program for the camera, movement, and srolling. once the shakedown test
program begins the debug-compile-debug phase, dev state will be advanced
to Prealpha proper.

During Alpha, the project will be optemized for Devuan Linux, however,
there are (theoretically) no distro-dependent elements, and the code should
run on ANY *nix with properly fufilled dependancies by configuring paths.h

Manpages will be provided in Linux's ROFF-man and BSD's ROFF-mdoc;
the documentation installed will be determined by uname.
Extended documentation will be provided in plaintext, POD, Texinfo, and HTML

Lore can be found at my Neocities site:
https://generalguy4872.neocities.org/Games/
