#error NOT READY FOR INITIAL COMPILATION
/* at the moment, this file is a scratchpad for outlining functions.
 * as development progresses, these outlines will be replaced with
 * tested and working equivilants.
 * to preserve the file history, this file will eventually become main.c
 * dummy.h will provide externs and macros for linkage.
 *
 * the bulk of it's contents, however, will be moved.
 *
 * comments may be deleted, may be moved into documentation, or may stay with what they describe
 *
 * work process:
 * outline pseudocode top-down, using blackboxes as neccisary
 * write real code bottom-up
 *
 * optimized for memory footprint. speed is not a concern at the moment.
 * C++ was found unsuitable for the majority of the program, however
 * Perl is seeming more and more of an extravagance; a C/C++ hybrid 
 * may be called upon to replace it.
 *
 * the idioms and formatting I am using throughout the project are based on the way my mind works
 * rather than a specific programming paradigm; I am borrowing from several.
 *
 * the program also uses various memory management paradigms,
 * including linked lists, stacks, queues, and page swapping.
 *
 * example: loading a room's file is swapping it into memory.
 * once it is loaded, the pointer is placed on the top of
 * the stack of loaded rooms, and the stack's depth counter
 * is increased. when the counter reaches the limit, the
 * stalest room is dropped. when warping, the room stack
 * is checked before an attempt is made to load another
 * room; when a room is recalled, it is moved to the top
 * of the stack, therefore (less stale) rooms are able to be
 * fetched faster than (more stale) rooms.
 *
 * additional indirection layers are used in an attempt to
 * prevent larger data structures from being duplicated
 *
 * most function calls provide an (obfuscation|abstraction) layer,
 * and before attempting to understand a function you should trace
 * down all the functions it calls. many functions use dynamic memory
 * operations, such as malloc and free; these side effects are what
 * causes the program state to change as the game unfolds. The
 * datastructures that are being manipulated are the same ones that
 * are serialized and saved in the savefiles; listed in the GLOBALS
 * section
 *
 * in the documentation and comments,
 * an "unbounded" array refers to
 * a [0] array that resembles a
 * nul-terminated string literal.
 * they are used for fixed data where
 * linked lists would be bloaty, but the
 * size of the array is not consistent.
 *
 * both explicit and implicit int declarations are used.
 * functions declared <implicit int> return either zero (ok) or
 * nonzero (error) rather than a proper intergal value.
 * this is akin to certain C library functions, and inverse
 * to a perl sub or a function returning bool
 * for the same pourpouse.
 * functions that return pointers return NULL on error;
 * functions returning "unbounded" arrays that cannot simply return NULL
 * return an equivilant to the empty string on error.
 *
 * as has already been demonstrated, my comment notation uses
 * programming speak in some situations. the meaning should be
 * readily apparent.
 */

/******************************
 * IWANNAFLY (working title)  *
 * Top-down 3D Rogue-like     *
 * Game engine with C API     *
 * using NCurses, with        *
 * extensions in Perl         *
 ******************************/

/* Hey, you. yeah, you. who do you think I'm talking to; the mouse?
 *
 * you found the seeecret extended documentation, aka the commentated
 * source code! the sorce code's witty comments are intended to supplement
 * other documentation, as well as give a deeper understanding of the
 * program because, ya'know, source code.
 *
 * The engine provides the C libraries and Perl modules/scripts needed to write a game.
 *
 * a game using the engine should provide the following:
 * - A newgame initializer perl script
 * - Any shared resources needed by events
 *
 * enviromental requirements:
 * - UTF-8 terminal of at least 24*80 characters
 *	"Fixed" font is recommended (specifically because
 *		it is a raster font; monospaced raster fonts are more uniform in width than the majority of vector so-called "monospaced" fonts;
 *		it is unicode, having a wide range of characters; and
 *		it is extreamly common, being the default font for the linux console, xterm, and urxvt)
 * - ANSI SGR escape codes and 16 colors outside of NCurses
 *	The engine will recognise the term enviroment and can sent xterm-style OSC strings if they are supported as well
 * - NCurses with support for A_BOLD, A_ITALIC, A_UNDERLINE, A_DIM, A_BLINK, A_REVERSE, A_INVIS, 8 colors, and 64 color pairs
 * - Full Keyboard
 *	(most keyboard layouts with all ASCII characters *should*
 *	work, but only QWERTY (US-ANSI) was used in design because
 *	I don't have access to any others, so at best controls may
 *	be strange on them.
 *	want to eventually guaruntee support for other keymappings;
 *	not just for other QWERTY layouts, but also for QWERTZ, AZERTY,
 *	and Dvorak, by request and/or the ability to remap keys
 *	by dotfiles.)
 *
 * XTerm is the recommended X Terminal Emulator (the primary one used in testing),
 * but the raw TTY Console set up in UTF8 locale will work just as well,
 * maybe even better if memory is an issue. At first glance, A Vt241 or Vt3*0
 * seem to meet all the requirements, but note: they predate the invention of unicode.
 * 
 * Controls:
 * - number keys move in xy
 * - + or - followed by a number move in xyz
 * - < > strafe
 * - backspace retreats (winged creatures also take flight)
 * - spacebar attacks
 * - tab picks up items
 * - enter interacts
 * - arrow keys, page up, page down, render a flat orthographic projection looking in that direction (free action)
 *	When in multiview mode:
 *	only visable tiles are rendered, other tiles are skipped instead of being rendered blinky.
 *	- number keys are indexed to camera, i.e. if facing west, 8 moves west and 2 moves east.
 *	- : look at a tile.
 * - home renders a top-down perspective at a -45 degree angle from the z axis,
 *	culling the first layer which obstructs the player from view and above (free action)
 * - end renders only the plane including the player. takes a slice perpindicular to the camera. (free action)
 * - 5 idles
 * - F1 toggles see invisible. (free action)
 * - F2 shows sense alignment. (free action)
 * - F3 shows the direction entities are facing. (free action)
 * - F4 shows normal view (free action)
 * - F5 toggles dingbats (free action)
 * - . <movement control> face a direction
 * - . ( "<" | ">" ) rotate that direction
 * - . . turn around
 * - \ initiates command entry. free action itself, but most commands are not.
 * more tbd
 *
 * new saved worlds may be generated by a perl script, which would call the system's tar near the end of execution.
 *
 * depending on RAM or Disk usage of the final program, it may be necissary
 * to run early versions in the system console to prevent resource starvation,
 * or to use a dedicated memory stick for the save files for the same reason.
 * if such requirements arise, they will be considered a severe flaw and work
 * will focus on fixing them as soon as possible.
 *
 * commands are implemented by a Perl::Safe read,exec loop
 *
 * This program is divided into 3 layers:
 *
 * the API layer is the part that provides functions to help with events.
 *	this is the only part you should need to know to compile your own
 *	games that can get fairly complex. these alse include the internal
 *	utilitys for character encoding conversion, input buffering, room
 *	generation and pathfinding algorithems, dice, warping, dying, error,
 *	and the internal implementation of cat.
 *
 * while the API functions have a simple enough calling convention,
 * there is no garuntee that the code underneath is not hundreds of lines long.
 * the sequence to bring the engine up is:
 *
 * termcheck()
 * enginesplash(name of game,game version,story revision)
 * <your startup stuff here>
 * FIXCURSES
 * <more of your startup stuff here>
 * promptload()
 * engineloop()
 *
 * autogeneration of newgame initializers is pending; mainly because no newgame initializer exists to model one off yet.
 *
 * the middle layer, or the guts, is where the engine actually happens, and
 *	it isn't pretty. if you want to change how the game works,
 *	it's going to get messy. this is where the functions for
 *	the RPG system itself, loading and saving, turns, shadows,
 *	3D rendering, and room changing are placed. these should not
 *	usually called directly by events, only by other builtin
 *	functions; some are only called by main.
 *
 * the backend consists of shims between generalized internal representations of
 *	a thing, and the actual way that a library or driver expects it to be
 *	formatted. the following are/will be considered part of this layer:
 *	- anything underneath a call to a parser
 *	- what goes on inside of the midi threads
 *	- the code underneath the savefile handling calls
 *
 * The API should always be backwards-compatable with all versions, from beta to doomsday.
 * The Guts may have breaking changes between MAJOR versions, but not otherwise.
 * The Backend depends on things beyond my control, and should be considered non-dependable.
 *	special cases should be noted, that the savefile format and language version have
 *	their own versioning system. this still may be broken if the flex-yacc or
 *	compression libraries of the build enviroment are changed from expectations,
 *	but is a good start.
 *
 * the goal of all things regarding RNG will not be cryptographic security;
 * contrarawise, an option to manually seed will be added so that
 * an exact game may be repeated. when perl is called, C's rand will
 * be used as the argument to perl's srand via XS.
 *
 * At present, communication between Perl and C is expected to use
 * controlled heap leaks, via xs. This has a potential to create real
 * memory leaks and is less than ideal, but is a quick kludge solution
 * to bypass C scope and thread safety in order to emulate a memory
 * structure more ideal for the scope of the game, namely the flat layouts
 * of ancient video game consoles. the Perl-side API has all the same
 * tools given to it as are required by the C-side API, including malloc
 * and free, to facilitate this. A side effect of this memory organization
 * choice is that YOU MUST COLLECT (most of) YOUR OWN GARBAGE with free().
 * in Perl, free may or may not be eventually implemented as a method as
 * well as a first-class sub.
 *
 * a nonstructured language will be provided for defining midi streams
 * in a human readable format.
 *
 * At some point in the far future, once the engine has reached Beta,
 * a complementery Tileset version of the engine will be created using
 * the X Toolkit, XPixMap, and the Athena Widgets, while retaining the
 * mostly the same API.
 *
 * A version targeting the upcoming Atari VCS may be contemplated
 *
 * GPLv2 or later unless noted.
 * Perl code dual-liscensed with the Artistic Liscense unless noted.
 * Do Please Distribute, All Wrongs Reversed.
 */

/**standard libraries**/
#ifndef _XOPEN_SOURCE_EXTENDED
#define _XOPEN_SOURCE_EXTENDED
#endif
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <math.h>
#include <limits.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <uchar.h>
#include <dlfcn.h>

/**system libraries**/
#include <unistd.h>
#include <signal.h>
#include <locale.h>
//#include <regex.h>
//#include <glob.h>
//#include <sys/types.h>
//#include <sys/ioctl.h>
//#include <fcntl.h>
//#include <sys/stat.h>
//#include <errno.h>

/**compression libraries**/
#include <libtar.h>
#include <zlib.h>
#include <libbz2.h>

/**perl libraries**/
#define PERL_NO_GET_CONTEXT
#include <EXTERN.h>
#include <perl.h>

/**ncurses libraries**/
#include <ncursesw/ncurses.h>
//#include <menu.h>
/**curses libforms**/
//#include <forms.h>

// need to find a MIDI library.

#ifndef __GNUC__
#warning WARNING - for best results, please use a compiler that supports GNU C.
#define __attribute__(X) /**/
#endif

/**local libraries**/
#include "macro.h"
#include "constants.h"

mvaddch16(int x,int y,char16_t raw,attr_t attrs) {
const wchar_t wch = raw;
attrset(attrs);
mvaddnwstr(x,y,&wch,1);
}

addch16(char16_t raw,attr_t attrs) {
const wchar_t wch = raw;
attrset(attrs);
addnwstr(&wch,1);
}

/* some output modes that will be used:
 *
 * using narrow characters with printw or addch
 * using wide characters with these functions
 * setting attributes with attrset, attron, attroff, and chgat
 *	uses A_DIM, A_BOLD, A_ITALIC, A_UNDERLINE, A_REVERSE, A_BLINK, A_INVIS,
 *	and 64 color pairs made from 8 colors
 * using the above custom functions to put wide characters on
 * the screen using addstr, addnstr, addwstr, addnwstr to print strings
 * pausing curses and dumping an entire file with printf
 */

/*ENVIROMENTALS*/
char16_t TILDEWIDE
char* TERM

/* ɛ⃓ will be used for "and", the conjunction, in comments where logical && would give a meaning that
 * could be validly, but incompatibly, interpreted as compleatly different from what is intended.
 * if confusion arises from or, similar mesures will be implemented for it, too.
 */

/* the 3D version of Iwannafly started off as a general RT-RPG library that
 * then became narrowed to a specific game. this version was originally
 * supposed to be the same game reworked for ncurses,
 * but is now becoming closer to the general library concept,
 * similar to a RPG ruleset that allows creation of
 * your own setting and plot (you know the one).
 * a default one will be provided, however.
 */

//anonomous pointers, could be anything. they're anonomous.
struct drum {
	char data[DRUMSIZE]
	short top
	}

void* drumalloc (ptr,amount)
struct drum ptr
size_t amount
{
if ((ptr->top + amount) ≤ (DRUMSIZE)) {
	void* output = ptr->data[ptr->top]
	ptr->top += amount
	return output
	}
else {return NULL}
}

drumpop (ptr,amount)
struct drum ptr
size_t amount
{
ptr->top = MAX(ptr->top - amount,0)
}

setlocale(LC_ALL, "");

initialize() {
	initscr();
	cbreak();
	noecho();
	start_color();
	keypad(stdscr, true);
	}

for (uchar bg = 0; bg < BGCOLORS; bg++) {
	for (uchar fg = 0; fg < FGCOLORS; fg++) {
		init_pair((BACKGROUND * bg) + fg, fg, bg);
		}
	}

char16_t setwidetilde() {
forever {
	move(12,4); printw("is this tilde between the lines? (y,n)")
	
	mvaddch(14,14,"-")
	mvaddch(14,15,"-")
	mvaddch(14,16,"~")
	mvaddch(14,17,"-")
	mvaddch(14,18,"-")
	
	char got = getch()
	
	switch (got) : {
		case 'y' : return '~';
		case 'n' : return = 0x223C;
		default : printf("\a"); fflush(stdout); break;
		}
	}
}

/*blackbox*/loading()
	/* clears screen
	 * prints "  LOADING..." on line 13
	 * prints a hint on line 22.
	 *   hints are stored in a struct
	 * rotates the hints wheel by 1 node
	 */

uint util__roll (num,side,low)
uchar num;	//number of dice to roll
uchar side;	//sides on each die
bool low;	//low number on each die
{
uint accum;
uint tmp;
for (uchar n = 0;n<num;n++) {
	tmp = (rand() % side) + low;
	accum += tmp;
	}
return accum;
}
//XdN is (X,N,0), XDN is (X,N,1)

short util__bonus (num)
uchar num;
{
short accum;
char tmp;
for (uchar n = 0;n<num;n++) {
	tmp = (rand() % 3) - 1;
	accum += tmp;
	}
return accum;
}

#define util__flip (rand() % 2)

/*implicit*/file_cat (path)
const char *path;
{
FILE *openfile = fopen(path,"r");
int lines;
if (openfile == NULL) {
	ERRORGRAPHIC(OK,1,sizeof(char*),"Could not open file: %s",path);
	return ERR;
	}
char tmpbuffer[BUFFER_MAX];
BREAKCURSES
for (bool n = true;n;) {
	if (fgets(tmpbuffer,BUFFER_MAX,openfile) == NULL) {
		n = false;
		} else {
		printf(tmpbuffer);fflush(stdout);
		lines++;
		}
	}
FIXCURSES
fclose(openfile);
return lines;
}

// depricated
/*x should also output __FILE__ ɛ⃓ __LINE__, which will likely be the program's version of
 *x undecipherable hex codes to anyone not extreamly fammiliar with the source. less severe
 *x errors will prompt for [Q]uit, [A]bort, or [Z] continue. more severe ones will prompt
 *x [Q]uit, [A]bort, [Z] restart. When other keyboard layout options are supported, QAZ will
 *x be replaced with the left column of letters (under 1). replacements for QAZ might be:
 *x QAY, AQW, "A:, FUJ. if Q or A are present in this group, they will be [Q]uit ɛ⃓ [A]bort,
 *x swapping places with the other option. otherwise, the quit-abort-option3 order will be kept.
 */

/**GLOBALS**/
playertyp PLAYER
roomstackholder ROOMSTACK
#define ROOM ROOMSTACK.swapin
#define ROOM_NOT_NULL(X,Y) ((ROOM != NULL) ? X : Y)
#define WORLD	ROOM_NOT_NULL( ROOM->latlon , (latlontyp){0,0,0,0,0,0} )
#define CEILING	ROOM_NOT_NULL( ROOM->ceiling , MAX_Z )
#define OLDCEILING (CEILING + 1)
planestackholder PLANESTACK
uint64_t TURN
nibbles TIMER
char ALARM = -1
turntyp DATE
uchar ROOMTURN
uchar ELECOLLECT[8]	//elemental collectibles
uchar QUESTCOLLECT[3]	//light/dark/entropy collectibles
uint64_t KILLS
char* SAVEPATH
followtyp *FOLLOW_ptr	//followers/minions
followtyp *PURS_ptr	//pursuers, i.e. paid assasins, ninjas, the reaper...
eventtyp *EVNT_ptr	//FOO_ptr refers to the doubly linked list's head. the tail is FOO_ptr->prev. FOO_ptr->prev->next is always NULL.
placetyp *PLACE_ptr
stringlistyp *HINT_ptr
eventdatastack_ele *EVSTACK_ptr
qglobobj * GLOBOBJ_ptr
qglobev * GLOBEV_ptr
chaptertyp CHAPTER
bitfield globools
#define NEW globools.a
#define FIRST globools.b
#define DAY globools.c
#define NIGHT globools.d
#define MORN globools.w
#define NOON globools.x
#define EVE globools.y
#define MIDNIT globools.z
cameratyp CAMERA
/*end GLOBALS*/

bool ticktock() {
TURN++;
TIMER.lo++;
if ((TIMER.lo == TIMER.hi) && (ALARM ≥ 0)) {ALARM++}
if (ROOMTURN < 200) {ROOMTURN++;}
DATE.sec += 6;
if (DATE.sec ≥ 60) {
	DATE.sec = 0;
	DATE.min++;
	if (DATE.min ≥ 60) {
		DATE.min = 0;
		DATE.hour++;
		if (DATE.hour ≥ 24) {
			DATE.hour = 0;
			DATE.weekday++
			if (DATE.weekday ≥ 7) {DATE.weekday = 0;}
			DATE.day++;
			if (DATE.day ≥ 30) {
				DATE.day = 0;
				DATE.month++;
				if (DATE.month ≥ 12) {
					DATE.month = 0;
					DATE.year++;
					if (!(DATE.year)) {return true}
					else {return false}
				}
			}
		}
	}

MIDNIT = ((DATE.hour == 0) && !(DATE.min))
MORN = ((DATE.hour == 6) && !(DATE.min))
NOON = ((DATE.hour == 12) && !(DATE.min))
EVE = ((DATE.hour == 18) && !(DATE.min))
DAY = ((6 ≤ DATE.hour) && (DATE.hour < 18))
NIGHT = ((DATE.hour < 6) || (18 ≤ DATE.hour))
}

//projection, →x ↓y ↑z

char* itemstabs[256] //stuff that doesn't go anywhere else; i.e. arrows, keys, quest items
char* spellstabs[256] //spells
char* weapstabs[256] //weapons
char* armstabs[256] //armor
char* shldstabs[256] //shield, cannon, greeves
char* baubstabs[256] //rings, amulets, bracelets, tiaras
miscitembasetyp* itemtable[256]
basespelltyp* spelltable[256]
baseweaptyp* weaptable[256]
basearmortyp* armtable[256]
baseshldtyp* shldtable[256]
baubtyp* baubtable[256]

char* legendstabs[24] = {
#include "legend.csv"
};
legendtyp* legendtable[24];

char* psystabs[8] = {"detect alignment","charm","psychic lock","sleep","mind blast","passify","unhinge","terrorize"}

/*blackbox*/psionic(id)
uchar id
//switch case for each psionic ability

char (*classnametable[8])[4] = {
	{
#include "class_rogue.csv"
	},{
#include "class_fighter.csv"
	},{
#include "class_magic_user.csv"
	},{
#include "class_cleric.csv"
}}

struct baseclasstyp classtable[4][8][4];

char (*monstabs[256])[16] = {
#include "monster0.csv"
	},{
#include "monster1.csv"
	},{
#include "monster2.csv"
}}

basentyp (*montable[256])[16] = {
/* contains all polymorphable monsters, of type BASENTYPE.
 * all C0 controls should be valid starting races, or left empty,
 * any polymorphable race can BECOME your base race...
 * 
 * if you become polylocked to a non-player race, your class will be removed.
 * becoming polylocked to one of the C0 entrys has no negative effects.
 * commands can change your base race without negative side effects
 */

/* MONSTERS BY LETTER
 * & : horned devil, balrog, jubilix,
 * @ : human, elf, half elf, drow, seaelf, siren,
 * A : angel, astral, ætherial, celestial, archon, half celestial,
 * a : newt, salamander, frog, 
 * B : bear, polar bear, owlbear,
 * b : mockingbird, parkeet, parrot, macaw, cockatoo, songbird, sparrow, starling, jay, magpie, jackdaw,
 * C : satyr, centaur,
 * c : chickatrice, cockatrice, pyrolisk,
 * D : /(△red|↯copper|◬white|*cyan|▽blue|♠green|⍫brown|$gold|☽black|☼silver|∅grey) dragon/,
 * d : hellhound, wolf, dire wolf, dog, fox, cyote,
 * E : <elementals>, stalker,
 * e : floating eye,
 * F : panther, lion, tiger, manticore, cat, lynx, bobcat,
 * f : turkey, rooster, chicken, peacock, duck, goose, swan, gull, dodo,
 * G : ghost, banshee, revenent, barrow wight,
 * g : gremlin, gargoyle, winged gargoyle,
 * H : giant, cyclops,
 * h : dwarf, gnome, hobbit,
 * I : /giant (ant|roach|scarab|wasp|scorpion|spider)/
 * i : ant, roach, scarab, wasp, scorpion, spider, firefly,
 * J : djinn,
 * j : gelatinous cube, green slime, brown pudding, black pudding, ocher jelly, spotted jelly, blue jelly,
 * K : kracken, giant squid, octopus,
 * k : kobold,
 * L : skeleton, lich,
 * l : leprachaun,
 * M : elephant, mammoth, rhino,
 * m : <mummies>
 * N : naga, half dragon,
 * n : merfolk, naiad, dryad, sea siren,
 * O : orc, half orc, uruk-hai, ogre,
 * o : ostrich, emu, moa,
 * P : dolphin, narwhal, orca, beluga,
 * p : penguin, puffin, auk, albatross,
 * Q : fiend, drider, erinys, kerr, harpy, tiefling,
 * q : quasit, imp, homunculus,
 * R : eagle, falcon, owl, kite, vulture, phoenix, raven, rook, crow,
 * r : mouse, rat, dire rat, raccoon, badger, opossum, platypus, groundhog, 
 * S : shark, stingray, swordfish, barracuda, eel,
 * s : copperhead, cobra, rattlesnake, python, boa, viper, coral snake, king snake, anaconda,
 * T : lurker above, trapper, wallmaster, rust monster,
 * t : troll,
 * U : umber hulk,
 * u : unicorn, pegasus, griphon, hippogriph,
 * V : vampire, mind flayer, medusa, tengu,
 * v : bat,
 * W : wyrm, great wyrm, hydra,
 * w : purple worm, nightcrawler,
 * X : velociraptor, tyrannasaurus,
 * x : monitor, alligator, crocodile,
 * Y : yeti, bigfoot,
 * y : ape, monkey, gorilla, chimp, leamur,
 * Z : <zombies>
 * {}: /(flesh|straw|clay|stone|glass|paper|leather) golem/, /(gold|copper|finite-state) automaton/, chest monster,
 * ? : mystery person
 * «»: bass, trout, salmon, tuna, carp, pike, halibut, herring, cod
 * × : lizard, geko, skink, 
 * ÷ : lobster, crab, shrimp,
 * £ : justice. (strictly-lawful neutral)
 * ¥ : [spoiler]
 * ¶ : da fuzz. (lawful neutral)
 * Ω : [spoiler]
 * ⑄ : retribution. (chaotic neutral)
 * ∀ : ox, cow, pig, buffalo, goat, sheep,
 * ∄ : fear itself. (neutral somewhat-evil)
 * ⊞ : lichen, moss, green mold, slime mold, black mold
 * ∈ : <half elementals>
 * ∞ : grue.
 * ☠ : death. (true neutral)
 * ♞ : quarterhorse, draft horse, miniature horse, zebra, nightmare,
 * ⏍ : hungry chest, chest monster,
 *//*
 * ≷?≶ ≶?≷ <?> >?< ≤?≥ ≥?≤ ≪?≫ ≫?≪ wings
 * some wings disappear when not flying; others are permenantly visable
 *
 * z : asleep
 * not rendered in the pgup or pgdn views
 *
 * these are rendered before (under) entities, but after tiles on each slice.
 */

char* conlangtab[32] = {"common language","middle elvish","old elvish","dwarvish", "gnomish","gothic","orkish","draconic", "fey","celestic","demonic","blackspeech", "skyspeak","waterspeak","earthspeak","firespeak",
	"thieves cant",/*?*/,/*?*/,/*?*/, /*?*/,/*?*/,/*?*/,/*?*/, /*?*/,/*?*/,/*?*/,/*?*/, "electric","icespeak","treespeak","metallic"}

/*blackbox*/update_player
/* resets .fromequip , then iterates through the entire equipment list to regenerate it.
 * must be called every time equipment is changed to ensure that it is up to date
 * effects in .permenent can only be removed by finding something that affects the opposite change
 * changes to your starting alignment or role are generally rare and disasterous, as they represent
 * the corruption of the character in some way. changes to your race may also be inconvenient,
 * but not necissarily bad. (I.E. late game events may change a player into a powerful
 * non-starting race as part of the story, such as a drider, full elemental, or dragon.)
 *
 * this may be done automatically when you sleep.
 */

/*blackbox*/inventsort
/* compresses stackable items into stacks, sorts items by objid and itemid.
 * more computationally expensive than update_player.
 */

/*blackbox*/force_global
/* forces some queued globals to be loaded. takes a very long time, but can
 * sometimes be necissary if the global buffer is starving the system.
 */

char* wandmaterials[16] = {"oak","ash","yew","honeylocust","silver","bronze","iron","orichalcum","marble","bone","dragon fang","unicorn horn","glass","lead crystal","adamantine","stardust"} //stoning -> marble

char* baubmaterials[8] = {"yew","bronze","silver","gold","soapstone","ivory","obsidian","stardust"} //stoning -> soapstone

set_collision_map (roomtyp * this,char x,char y,char z,bool q) {
	if (z < this->ceiling) {
		if (q) {
			switch (z) : {
				case 0 : return this->collisionmap.solid[y + 1][x + 1] |= 0x8000;
				case 1 : return this->collisionmap.solid[y + 1][x + 1] |= 0x4000;
				case 2 : return this->collisionmap.solid[y + 1][x + 1] |= 0x2000;
				case 3 : return this->collisionmap.solid[y + 1][x + 1] |= 0x1000;
				case 4 : return this->collisionmap.solid[y + 1][x + 1] |= 0x0800;
				case 5 : return this->collisionmap.solid[y + 1][x + 1] |= 0x0400;
				case 6 : return this->collisionmap.solid[y + 1][x + 1] |= 0x0200;
				case 7 : return this->collisionmap.solid[y + 1][x + 1] |= 0x0100;
				case 8 : return this->collisionmap.solid[y + 1][x + 1] |= 0x0080;
				case 9 : return this->collisionmap.solid[y + 1][x + 1] |= 0x0040;
				case 0xA : return this->collisionmap.solid[y + 1][x + 1] |= 0x0020;
				case 0xB : return this->collisionmap.solid[y + 1][x + 1] |= 0x0010;
				case 0xC : return this->collisionmap.solid[y + 1][x + 1] |= 0x0008;
				case 0xD : return this->collisionmap.solid[y + 1][x + 1] |= 0x0004;
				case 0xE : return this->collisionmap.solid[y + 1][x + 1] |= 0x0002;
				case 0xF : return this->collisionmap.solid[y + 1][x + 1] |= 0x0001;
				default : return ERR;
				}
			}
		else {
			switch (zcoord) : {
				case 0 : return this->collisionmap.solid[y + 1][x + 1] &= ~0x8000;
				case 1 : return this->collisionmap.solid[y + 1][x + 1] &= ~0x4000;
				case 2 : return this->collisionmap.solid[y + 1][x + 1] &= ~0x2000;
				case 3 : return this->collisionmap.solid[y + 1][x + 1] &= ~0x1000;
				case 4 : return this->collisionmap.solid[y + 1][x + 1] &= ~0x0800;
				case 5 : return this->collisionmap.solid[y + 1][x + 1] &= ~0x0400;
				case 6 : return this->collisionmap.solid[y + 1][x + 1] &= ~0x0200;
				case 7 : return this->collisionmap.solid[y + 1][x + 1] &= ~0x0100;
				case 8 : return this->collisionmap.solid[y + 1][x + 1] &= ~0x0080;
				case 9 : return this->collisionmap.solid[y + 1][x + 1] &= ~0x0040;
				case 0xA : return this->collisionmap.solid[y + 1][x + 1] &= ~0x0020;
				case 0xB : return this->collisionmap.solid[y + 1][x + 1] &= ~0x0010;
				case 0xC : return this->collisionmap.solid[y + 1][x + 1] &= ~0x0008;
				case 0xD : return this->collisionmap.solid[y + 1][x + 1] &= ~0x0004;
				case 0xE : return this->collisionmap.solid[y + 1][x + 1] &= ~0x0002;
				case 0xF : return this->collisionmap.solid[y + 1][x + 1] &= ~0x0001;
				default : return ERR;
				}
			}
		}
	else if (z == this->ceiling) {
		if (q) {
			div_t tmp = div(x,8);
			switch (tmp.quot) : {
				case 0 : return this->collisionmap.holes[y][tmp.rem] |= 0x80;
				case 1 : return this->collisionmap.holes[y][tmp.rem] |= 0x40;
				case 2 : return this->collisionmap.holes[y][tmp.rem] |= 0x20;
				case 3 : return this->collisionmap.holes[y][tmp.rem] |= 0x10;
				case 4 : return this->collisionmap.holes[y][tmp.rem] |= 0x08;
				case 5 : return this->collisionmap.holes[y][tmp.rem] |= 0x04;
				case 6 : return this->collisionmap.holes[y][tmp.rem] |= 0x02;
				case 7 : return this->collisionmap.holes[y][tmp.rem] |= 0x01;
				default : return ERR;
				}
			}
		else {
			switch (zcoord) : {
				case 0 : return this->collisionmap.holes[y][tmp.rem] &= ~0x80;
				case 1 : return this->collisionmap.holes[y][tmp.rem] &= ~0x40;
				case 2 : return this->collisionmap.holes[y][tmp.rem] &= ~0x20;
				case 3 : return this->collisionmap.holes[y][tmp.rem] &= ~0x10;
				case 4 : return this->collisionmap.holes[y][tmp.rem] &= ~0x08;
				case 5 : return this->collisionmap.holes[y][tmp.rem] &= ~0x04;
				case 6 : return this->collisionmap.holes[y][tmp.rem] &= ~0x02;
				case 7 : return this->collisionmap.holes[y][tmp.rem] &= ~0x01;
				default : return ERR;
				}
			}
		}
	return ERR;}

/*pseudocode*/getsym
	{
	if (sym < 0)
		{
		cursesprint(.hightiles[sym^-128]) //xor intentional
		}
	else
		{
		cursesprint(.lowtiles[sym])
		}
	}

char* gemcolors[8] = {
#include "gemstones.csv"
} //stoning has no effect
/* cut varys by color:
 * diamond = {uncut,cushion-cut,princess-cut,perfect-cut}
 * beryls,emerald={uncut,oval-cut,emerald-cut,teardrop} redundancy of emerald-cut emerald is redundant
 * amythest={geode,prismatic,cushion-cut,teardrop}
 * jet,turquoise={piece of,byzantine,polyhedral,carved relif in}
 */

/*blackbox*/radius
/* uses floats to define a circle,
 * terminating when there is not enough
 * value left to move another whole block.
 * one function won't cover all use cases.
 * one of these class of functions will be
 * __attribute__((hot))
 */

each layer is drawn translated +1y for each layer above the player and -1y for each layer below.
a shadow is drawn under the player
layers are drawn from ground to sky; if the player or their shadow would be covered by a tile,
drawing is stopped and the player is drawn if they have not been already
fluid tiles are transparent.

symbols that are white or black based on being filled or unfilled might be
switchable at startup in the same way as tilde vs tilde operator

depening on difficulty of implementing such, characters might be stored in a lookup table
that stores indexes between an anything and a unicode codepoint. this would require a byte
encoding scheme for peeking anythings between runtimes, which is problematic considering
the existing 2 ways require either names (being computationally expensive),
or pointers (which are volatile state)

an UNDERLINE is a shadow

note: unicode symbols are (mostly) used be their appearence, not by their meaning
) is a sword or dagger. ⍏ are polearms. ! is a staff. ⇞ is a club or mace. ℓ is a whip. ␋ is a flail. ( is a bow. ⇤ is an arrow. ⇲ is a writing instrument.
⟦ is armor. [ is clothing. ] is a shield. ⟧ are cannons or greeves. ☜☝☞☟ is a gauntlet. % is meat. ± is food (don't shoot it). $ is gold. ¢ is copper.
⌘ is a misc item. ↧ is a digging tool. ⌥ is a key or lockpick. ♫ is a lyre. ƒ is a violin. ♪ is a lute.
¿ are potions (fragile). ∫ is a scroll. ⊒ is a book. ∩ is a tablet. ° is a ring. º is a bracelet. ª is an amulet. ¬ is a crown.
¡ is a wand. ♮ ⇫ ⇪ is a ladder. ⋎ is a fountain or gyser. ⍾ is a bell. ⎋ is a clockface. ♠ ♣ ‡ are trees. ⋏ is fire. ♜ is a pedestal.
≋ is deep liquid's surface. ∬ is a waterfall. ≈ is a shallow liquid's surface, or a deep liquid below surface. ~ (centered) is a puddle. ≣ is a staircase. 
⌁ is electricity. * is ice. ⎈ spider web. ⌬ beehive. ↥ are spikes. ⎙ ⍝ ⎍ ∎ ⎅ are tombstones or signs. ␥ is glass.
• is a boulder. . is a rock. ⑆ is a rockslide. ◇ is a gemstone. ◊ is a giant magic crystal. ? is somone wearing a cowled cloak.
∪ is a sink. ⏍ is a chest. ↯ is the thunderbolt. ∅ is a spacetime anomaly (do not touch). ⍍ ⍔ are level stairs.
⇡ ⇣ ← ↑ → ↓ ↖ ↗ ↘ ↙ are flying projectiles, or facing direction. ⇐ ⇑ ⇒ ⇓ ⇖ ⇗ ⇘ ⇙ are ballistae. ✪ is a rune. ː ˑ are traps.
# █ ▓ ▒ ░ ▞ ▚ ⣿ (etc) are thick walls or floor. ☁ ≎ are clouds. ☈ is a thundercloud (keep your head out of them). ⁂ is fog.
^ ␣ are holes. , is a plant. ; is a grain or sunflower (impassable). ⌸ is a door. ⍯ is a locked door. ⎕ is an open door.
box drawings are low walls or columns. ¦ ⑉ are iron bars. / \ " are sunbeams. = is a gate. ≠ is a locked gate. : is an open gate
⍽ is mud. ≃ ≊ is stagnent water (unbreathable). ☯ is a reflecting pool. ⍬ is a mirror. ♄ is an antimagic field.

a prompt at launch uses user responce to choose between using ~ or ∼ for centered tilde.
handling of solid vs outlined symbols will use the solid symbol for a forground different from the background,
and outlined to represent same color on color.

box drawings:
 ╒╤╕     ╔╦╗
 ╞╪╡flat ╠╬╣upright
 ╘╧╛     ╚╩╝

A_DIM is used to provide 16 colors
A_ITALIC symbols are petrified (statues).
A_BLINK is a tile that is out of view
A_BOLD symbols are highlighted
A_INVIS is not able to be seen
A_REVERSE video is a magic spell's area of effect
A_UNDERLINE is the shadow of an entity

text that is cat-ed from an nfo file, or otherwise printed using stdio, will not be restricted to ncurses formatting,
and will use the full range of ANSI SGR escape codes

rune symbols
◬ air, ⍫ earth, △ fire, ▽ water
⋇ ice, ☇ electricity, ↥ metal, ♻ nature
❖ ☣ status effects, ∅ entropy
☼ light, ☽ dark, § polymorph, ↹ planer
♥ healing

magic AOE symbols
≋ air, • earth, ⋏ fire, ∿ water
* ice, ⌁ electricity, ↥ metal, ♠ nature
❖ ☣ status effects, ‽ entropy
☀ light, ☽ dark, § polymorph

directional symbols:
←, ↑, →, ↓, ↖, ↗, ↘, ↙, direction in XY;
! far side; ↧, ↥, direction in Z;
↹ different plane;
◬, ⍫, △, ▽, ⋇, ↯, ♤, ♻, ☼, ☽, ∅, inner planes;
LG, NG, CG, LN, CN, LE, NE, CE, TN, UN, ☠, outer planes;


/*blackbox*/playervelocitycheck() velocitycheck(*entity)
	/* if you have a nonzero velocity vector, when you try to move
	 * you travel in a direction determined by the mean vector of
	 * your move and your velocity. each turn, your velocity reduces
	 * by 1+.5n on land, 1+.75n underwater, and is cancled compleatly
	 * in a direction if you hit something.
	 */

/*blackbox*/movecheck(xmove,ymove,zmove)
	/* if you are flying {
	 *	checks your flying skill and restricts your movement accordingly
	 *		if you have no flying skill, grav is added to your -Z velocity
	 *	checks to make sure that you are not flying through a solid block
	 *	checks to make sure you are not landing in water if you can't swim
	 *		asks if you are sure
	 *	}
	 * if you are walking {	
	 *	checks to make sure you are not walking off a cliff without wings
	 *		asks if you are sure
	 *	checks to make sure you are not walking into deep water if you can't swim
	 *		asks if you are sure
	 *	automatically climbs 1-high blocks that are not fences
	 *	}
	 * updates your direction 	
	 * if you leave the room by any means, creates a mapscrolltyp of the apropriate value and calls mapscroll
	 * subtracts the appropriate value from your remaining move
	 * }
	 */

/*blackbox*/newtonlaw(xmove,ymove,zmove)
	- checks if you're flying magically, on ice, or in a liquid
	- if you are, adds {-xmove,-ymove,-zmove} to your velocity
	  (half this value in liquids)


roomscroll(direction,stairs)
uchar direction
bool stairs
{
switch (direction) : {
	case 0 : break;
	case ROOM_UP : saveroom(NULL);WORLD = touchroom(ROOM->neighborhood->up);

roomwarp(latlontyp)

coordjump(coordx,coordy,coordz)

/*blackbox implicit*/dump(datatypenum,void*)
// used by the debugger to dump data.

/*pseudocode implicit*/castshadow(xpos,ypos,zpos)
uchar xpos
uchar ypos
uchar zpos
{
if (zpos == 0) {
	return zpos
	}
else if (mapderef(xpos,ypos,zpos-1).solid) {
	underline(xpos,ypos,zpos)
	return zpos
	}
else {
	zpos--
	for (;zpos!=0;zpos--) {
		if (mapderef(xpos,ypos,zpos-1).solid) {
			underline(xpos,ypos,zpos)
			return zpos
			}
		else if (mapderef(xpos,ypos,zpos-1).liquid) {
			underline(xpos,ypos,zpos)
			}
		}
	underline(xpos,ypos,zpos) //escape zpos==0
	return zpos
	}

bool maskfetch(zcoord,ycoord,xcoord,mask)
uchar zcoord
uchar ycoord
uchar xcoord
shadowmask mask
{
switch (zcoord) : {
	case 0 : return (bool) (mask[ycoord][xcoord] & 0x8000);
	case 1 : return (bool) (mask[ycoord][xcoord] & 0x4000);
	case 2 : return (bool) (mask[ycoord][xcoord] & 0x2000);
	case 3 : return (bool) (mask[ycoord][xcoord] & 0x1000);
	case 4 : return (bool) (mask[ycoord][xcoord] & 0x0800);
	case 5 : return (bool) (mask[ycoord][xcoord] & 0x0400);
	case 6 : return (bool) (mask[ycoord][xcoord] & 0x0200);
	case 7 : return (bool) (mask[ycoord][xcoord] & 0x0100);
	case 8 : return (bool) (mask[ycoord][xcoord] & 0x0080);
	case 9 : return (bool) (mask[ycoord][xcoord] & 0x0040);
	case 0xA : return (bool) (mask[ycoord][xcoord] & 0x0020);
	case 0xB : return (bool) (mask[ycoord][xcoord] & 0x0010);
	case 0xC : return (bool) (mask[ycoord][xcoord] & 0x0008);
	case 0xD : return (bool) (mask[ycoord][xcoord] & 0x0004);
	case 0xE : return (bool) (mask[ycoord][xcoord] & 0x0002);
	case 0xF : return (bool) (mask[ycoord][xcoord] & 0x0001);
	default : return false;
	}
}

/*implicit*/maskset(zcoord,ycoord,xcoord,mask,value)
uchar zcoord;
uchar ycoord;
uchar xcoord;
shadowmask * maskptr;
bool value;
{
shadowmask mask = *maskptr;
if (value) {
	switch (zcoord) : {
		case 0 : return mask[ycoord][xcoord] |= 0x8000;
		case 1 : return mask[ycoord][xcoord] |= 0x4000;
		case 2 : return mask[ycoord][xcoord] |= 0x2000;
		case 3 : return mask[ycoord][xcoord] |= 0x1000;
		case 4 : return mask[ycoord][xcoord] |= 0x0800;
		case 5 : return mask[ycoord][xcoord] |= 0x0400;
		case 6 : return mask[ycoord][xcoord] |= 0x0200;
		case 7 : return mask[ycoord][xcoord] |= 0x0100;
		case 8 : return mask[ycoord][xcoord] |= 0x0080;
		case 9 : return mask[ycoord][xcoord] |= 0x0040;
		case 0xA : return mask[ycoord][xcoord] |= 0x0020;
		case 0xB : return mask[ycoord][xcoord] |= 0x0010;
		case 0xC : return mask[ycoord][xcoord] |= 0x0008;
		case 0xD : return mask[ycoord][xcoord] |= 0x0004;
		case 0xE : return mask[ycoord][xcoord] |= 0x0002;
		case 0xF : return mask[ycoord][xcoord] |= 0x0001;
		default : return ERR;
		}
	}
else {
	switch (zcoord) : {
		case 0 : return mask[ycoord][xcoord] &= ~0x8000;
		case 1 : return mask[ycoord][xcoord] &= ~0x4000;
		case 2 : return mask[ycoord][xcoord] &= ~0x2000;
		case 3 : return mask[ycoord][xcoord] &= ~0x1000;
		case 4 : return mask[ycoord][xcoord] &= ~0x0800;
		case 5 : return mask[ycoord][xcoord] &= ~0x0400;
		case 6 : return mask[ycoord][xcoord] &= ~0x0200;
		case 7 : return mask[ycoord][xcoord] &= ~0x0100;
		case 8 : return mask[ycoord][xcoord] &= ~0x0080;
		case 9 : return mask[ycoord][xcoord] &= ~0x0040;
		case 0xA : return mask[ycoord][xcoord] &= ~0x0020;
		case 0xB : return mask[ycoord][xcoord] &= ~0x0010;
		case 0xC : return mask[ycoord][xcoord] &= ~0x0008;
		case 0xD : return mask[ycoord][xcoord] &= ~0x0004;
		case 0xE : return mask[ycoord][xcoord] &= ~0x0002;
		case 0xF : return mask[ycoord][xcoord] &= ~0x0001;
		default : return ERR;
		}
	}
return ERR;
}

bool langetx(race,id) __attribute__((const))
basentyp race
uchar id
{
div_t tmp = div(id,8)
if (tmp.quot > 3) {
	ERRORGRAPHIC(SIGFPE,3,\
		0,"math: out of bounds",\
		sizeof(int),"impossible result %i > 3",tmp.quot,\
		sizeof(uchar),"(perhaps %i > 31)",id);
	return false}
switch (tmp.rem) : {
	case 0 : return (bool) (race.vocal[tmp.quot] & 0x80);
	case 1 : return (bool) (race.vocal[tmp.quot] & 0x40);
	case 2 : return (bool) (race.vocal[tmp.quot] & 0x20);
	case 3 : return (bool) (race.vocal[tmp.quot] & 0x10);
	case 4 : return (bool) (race.vocal[tmp.quot] & 0x08);
	case 5 : return (bool) (race.vocal[tmp.quot] & 0x04);
	case 6 : return (bool) (race.vocal[tmp.quot] & 0x02);
	case 7 : return (bool) (race.vocal[tmp.quot] & 0x01);
	default : ERRORGRAPHIC(SIGFPE,2,\
		0,"math: invalid remainder",\
		sizeof(int),"remainder %i from modulo 8",temp.rem);
	}
}

engineloop () __attribute__((noreturn)) {
forever {
	if (NEW) {
		checkglobal(NEW_FLAG,true)
		NEW = false
		}
	checkevents()	//check event triggers
	player_act()	//player's turn
	follow_iter()	//iterate through follower entities
	ent_iter()	//iterate through local entities
	encounter(1D6,1d100)	//generate up to 1D6 of monster number 1d100, iff encounter != NULL
	}
}

/*pseudocode*/ <follow|ent>_iter () {
<ent|follow>typ* ptr = <head>
while (ptr != NULL) {
	<follow|ent>_act(&ptr) //&ptr's turn
	ptr = ptr->next
	}
}

/*pseudocode*/encounter(count,tableid)
uchar count
uchar tableid
{
encontyp *ptr = ROOM.encon_head
for (;tableid != 0;tableid--) {
	ptr = ptr->next
	}
uchar try;
for (;count != 0;count--) {
	try = mainh_roll(10,20,1)
	if (try > ptr->tobeat) {
		summonfunc(ptr->spawn)
		}
	}
}

/*blackbox*/render() {
/* flush THESHADOWKNOWS and SHINEALIGHT
 * translate the view so that the player is on line 13
 * cast shadows and record the player's shadow
 * illuminate the player according to their view range
 * illuminate all lights in the room.
 * get the player's view information. only draw tiles that can be seen.
 * draw each layer of the room one at a time, making sure the player and their shadow are not covered, and doing out-of-view substitution.
 * draw the player
 * draw other entitys that can be seen
 * add shadows
 */

termcheck() {
TERM = getenv("TERM");
if (strstr(TERM,"xterm") != NULL) {
	IS_XTERM = true
	}

/*pseudocode*/enginesplash(GAME_NAME,GAME_VERSION,STORY_REV)
const char* GAME_NAME GAME_VERSION STORY_REV
{
	if (IS_XTERM = true) {
	printf("\033]1;IWannaFlyCurses\033\\");
	printf("\033]2;IWannaFlyCurses - %s\033\\",GAMENAME);
	}
printf(RESET);
printf(" \033[1;95m~~ IWANNAFLY ROGUELIKE ENGINE ~~\033[m\n\033[97m          engine version: %s\n          rules revision: %s\n            API revision: %s\n        savefile version: %s\nextension parser version: %s\n    runcommander version: %s\n       midibasic version: %s\n       midi backend type: %s\n\n \033[96m - %s -\033[m\n\033[97m  game version: %s\nstory revision: %s\n\n\033[37mCompiled on %s\n\033m\a",ENGINE_VERSION,RULES_VERSION,API_VERSION,SAVE_VERSION,EXT_PARSE_VERSION,RUNCOM_VERSION,MIDIBAS_VERSION,MIDI_TYPE,GAME_NAME,GAME_VERSION,STORY_REV,__DATE__);
fflush(stdout);
sleep(4);
printf(RESET);
printf("\033[1;32m\tEngine Copyright (C) 2019- \"GeneralGuy4872\"\n\n\tThis program is free software; you can redistribute it and/or\n\tmodify it under the terms of the GNU General Public License\n\tas published by the Free Software Foundation; either version 2\n\tof the License, or (at your option) any later version.\n\n\tThis program is distributed in the hope that it will be useful,\n\tbut WITHOUT ANY WARRANTY; without even the implied warranty of\n\tMERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n\tGNU General Public License for more details.\n\n\tYou should have received a copy of the GNU General Public License\n\talong with this program.  If not, see \n\t\033[m\033[4;94mhttps://www.gnu.org/licenses/\033[m\033[1;32m.\a");
fflush(stdout);
sleep(4);
printf(RESET);
printf("\033[92mLibraries linked:\nNCurses by Zeyd M Ben-Halim,\n           Eric S. Raymond,\n           Thomas E Dickey\n           and the Free Software Foundation\nLibTar by Mark D. Roth\nZlib by Jean-loup Gaully and Mark Adler\nLibBZip2 by Julian Steward\n");
fflush(stdout);
sleep(4);
printf(RESET);
printf("\033[92mAlgorithems Implemented:\nDijkstra's Algorithem\nPrim's Algorithem\nKruskal's Algorithem and Kruskal's Reverse Algorithem\nBorůvka's Algorithm\nRolling Dice\nSierpiński Attractor\nPerlin Noise\a");
fflush(stdout);
sleep(4);
}

init__main() {
termcheck();
TILDEWIDE = setwidetilde();
}

main() {
init__main();
enginesplash("Default Game","Prealpha","Rough Draft");
printf(RESET);printf(BLINKY);
fflush(stdout);
sleep(4);
printf(RESET);
file_cat_nocurses(STATIC_PATH"scene.nfo");	//...okay, it's the story of every JRPG ever, but the story of the 3D game didn't have a wide enough scope. I'll write more later, when I'm in that mindset.
printf("\a");
fflush(stdout);
sleep(4);
printf(RESET);printf(BLINKY);
fflush(stdout);
sleep(4);
printf(RESET);
puts("\033[3mSo it begins...\033[23m\a");
fflush(stdout);
sleep(4);
FIXCURSES
do_intro_movie();
promptload();
engineloop();
}

notatruending() {	/* used when an early win condition is met.
			 * the game is not normally saved,
			 * and the character remains in the file so that
			 * the true ending can be reached.
			 *
			 * recieving this message is usually a bad thing,
			 * as it means you were working in the wrong
			 * direction; however, there are more wicks
			 * twords the true endings than the red herrings
			 */
	BREAKCURSES
	printf("\033[1;3;33mTHIS IS NOT A TRUE ENDING...\n");
	puts(RESET);
	quit(0);
	}
