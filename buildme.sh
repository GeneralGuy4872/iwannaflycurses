#?/bin/sh
gcc -fPIC -shared -o libiwannafly_ncurses.so main.c -Wl,-E -Wl,-r -lncursesw
gcc -fPIC -shared -o libiwannafly_ncurses_runcommander.so runcommander.c -Wl,-E -Wl,-r -L. -liwannafly_ncurses.so -lncursesw
gcc -fPIC -shared -o libiwannafly_ncurses_extensions.so extensions.c -Wl,-E -Wl,-r -L. -liwannafly_ncurses.so -lncursesw

#gcc -fPIC -shared -o event_foo.so foo.c -g -Wl,-E -Wl,-r -L. -liwannafly_ncurses.so -lncursesw
#gcc -fPIC -shared -o event_bar.so bar.c -g -Wl,-E -Wl,-r -L. -liwannafly_ncurses.so -lncursesw
#gcc -fPIC -shared -o event_baz.so baz.c -g -Wl,-E -Wl,-r -L. -liwannafly_ncurses.so -lncursesw

#gcc -fPIC -shared -o quux.dat quux.h -O0 -g -Wl,-E -Wl,-r -L. -liwannafly_ncurses.so
#gcc -fPIC -shared -o garply.dat garply.h -O0 -g -Wl,-E -Wl,-r -L. -liwannafly_ncurses.so
#gcc -fPIC -shared -o xyzzy.dat xyzzy.h -O0 -g -Wl,-E -Wl,-r -L. -liwannafly_ncurses.so

gcc -fPIC -pie -shared -o iwannafly_ncurses_default.xso default_game.c -g -Wl,-E -Wl,-r -L. -liwannafly_ncurses.so -liwannafly_ncurses_extensions.so -lncursesw
gcc -o iwannafly_ncurses_default.out default_game.c -g -L. -liwannafly_ncurses.so -liwannafly_ncurses_extensions.so -lncursesw

gcc -fPIC -pie -shared -o iwannafly_ncurses_default_newgame.xso newgame.c -g -Wl,-E -Wl,-r -L. -liwannafly_ncurses.so -liwannafly_ncurses_runcommander.so -lncursesw
gcc -o iwannafly_ncurses_default_newgame.debug newgame.c -g -L. -liwannafly_ncurses.so -liwannafly_ncurses_runcommander.so -lncursesw

gcc -o iwannafly_ncurses_default_editor.debug editor.c -g -L.  -liwannafly_ncurses.so -liwannafly_ncurses_extensions.so -l:iwannafly_ncurses_default.xso -liwannafly_ncurses_runcommander.so -l:iwannafly_ncurses_default_newgame.xso -lncursesw

#NEEDS REAL MAKEFILE NOW; runcommander and extensions need to be flex-ed and yacc-ed
#preliminary guesswork at commands to build, nowhere near ready to run them to check