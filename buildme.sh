#!/bin/sh
gcc -fPIC -shared -o libiwannafly_ncurses.so main.c -Wl,-E -Wl,-r -lncursesw
gcc -o libiwannafly_ncurses.debug main.c -g -lncursesw
gcc -fPIC -pie -shared -o iwannafly_ncurses_default.xso default.c -g -Wl,-E -Wl,-r -L. -liwannafly_ncurses.so -lncursesw
gcc -o iwannafly_ncurses_default.debug default.c -g -L. -liwannafly_ncurses.so -lncursesw
gcc -o iwannafly_ncurses_default_newgame.debug util_newgame.d -g -L. -l:iwannafly_ncurses_default.xso -lncursesw
gcc -o iwannafly_ncurses_default_editor.debug util_editor.c -g -L. -l:iwannafly_ncurses_default.xso -lncursesw
#preliminary guesswork at commands to build, nowhere near ready to run them to check