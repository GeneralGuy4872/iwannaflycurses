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
*roguelike game with plugin interface written in C useing minimal propagating dependencies*

Dependencies:
(listed by file to be distro-independent)

Build Deps:
- <CODE>cp</CODE>
- <CODE>ls</CODE>
- <CODE>sh</CODE>
- <CODE>cc</CODE>
- <CODE>ld</CODE>
- <CODE>sed</CODE> maybe?
- <CODE>awk</CODE> maybe?
- <CODE>perl</CODE> maybe?
- <CODE>flex</CODE>
- <CODE>byacc</CODE>
- <CODE>make</CODE>

Build Recommends:
- <CODE>uname</CODE>
- <CODE>grep</CODE>
- <CODE>sed</CODE>

Depends (libraries by header):
- <CODE>\<stdlib.h\></CODE>
- <CODE>\<stdio.h\></CODE>
- <CODE>\<stdbool.h\></CODE>
- <CODE>\<stdint.h\></CODE>
- <CODE>\<math.h\></CODE>
- <CODE>\<limits.h\></CODE>
- <CODE>\<time.h\></CODE>
- <CODE>\<string.h\></CODE>
- <CODE>\<ctype.h\></CODE>
- <CODE>\<uchar.h\></CODE>

- <CODE>\<dlfcn.h\></CODE>
- <CODE>\<unistd.h\></CODE>
- <CODE>\<signal.h\></CODE>
- <CODE>\<locale.h\></CODE>
- <CODE>\<regex.h\></CODE>
- <CODE>\<glob.h\></CODE>
- <CODE>\<sys/types.h\></CODE>
- <CODE>\<sys/ioctl.h\></CODE>
- <CODE>\<fcntl.h\></CODE>
- <CODE>\<sys/stat.h\></CODE>

- <CODE>\<libtar.h\></CODE>
- <CODE>\<zlib.h\></CODE>
- <CODE>\<libbz2.h\></CODE>

- <CODE>\<ncursesw/ncurses.h\></CODE>
- <CODE>\<menu.h\></CODE>
- <CODE>\<forms.h\></CODE>

Recommends:
- <CODE>xterm</CODE>, unicode, color
- <CODE>/usr/share/fonts/X11/misc/6x13.\*</CODE>
	- aka <CODE>-Misc-Fixed-Medium-R-SemiCondensed--13-120-75-75-C-60-ISO10646-1</CODE>

Devkit Suggests:
- <CODE>m4</CODE>
- <CODE>gpp</CODE>
- <CODE>sed</CODE> || <CODE>awk</CODE> || <CODE>perl</CODE>
- <CODE>emacs</CODE> || <CODE>vim</CODE>

Doc Depends:
- <CODE>man</CODE>
- <CODE>info</CODE>

Doc Meta-depends:
- <CODE>mandb</CODE>
- <CODE>install-info</CODE>
- <CODE>cp</CODE>

Doc Recommends:
- <CODE>xdvi</CODE>

Obfuscated C
------------

To save my poor eyes, I'm using the following macros for C builtins:

- <CODE>≥</CODE> means <CODE>\>=</CODE>
- <CODE>≤</CODE> means <CODE>\<=</CODE>
- <CODE>→</CODE> means <CODE>-\></CODE>
- <CODE>forever</CODE> means <CODE>for (;;)</CODE>

I am given to understand that using macros for functions like this
is called "obfuscated C"

NEWS (and Olds)
---------------

During Alpha, the project will be optemized for Devuan Linux, however,
there are (theoretically) no distro-dependent elements, and the code should
run on ANY \*nix with properly fufilled dependancies by configuring paths.h

Manpages will be provided in Linux's ROFF-man and BSD's ROFF-mdoc;
the documentation installed will be determined by <CODE>uname</CODE>.
Extended documentation will be provided in plaintext, Texinfo, and HTML


Lore can be found at my Neocities site: https://generalguy4872.neocities.org/Games/
