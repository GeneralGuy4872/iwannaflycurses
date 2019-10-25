/*TYPES*/
//ensure size names work on all systems
#define uint unsigned int
#define sint signed int
#define uchar uint8_t
#define schar int8_t
#define ushort uint16_t
#define sshort int16_t
#define umint uint32_t
#define smint int32_t
#define ulong unsigned long
#define slong signed long
#define ullong uint64_t
#define sllong int64_t

// prettify the tokens my eyes don't parse
#define ≥ >=
#define ≤ <=
#define forever for (;;)

#ifndef EOF
#error now you're just TRYING to break stuff...
#endif

#ifndef NULL
#warning ... ...wh ... ... how??
#define NULL ((void*)0)
#endif

#define TRUE true
#define FALSE false

/*ENVIROMENTALS*/
#define BUFFER_MAX 512
#define FLOPPYSIZE 1474560
#define DRUMSIZE 16384
#define BGCOLORS 8
#define FGCOLORS 8

/*VERSION*/
#define ENGINE_VERSION "Prealpha"
#define RULES_VERSION "Prealpha"
#define API_VERSION "Prealpha"
#ifndef SAVE_VERSION
#define SAVE_VERSION "MISSING"
#endif
#ifndef EXT_PARS_VERSION
#define EXT_PARSE_VERSION "MISSING"
#endif
#ifndef RUNCOM_VERSION
#define RUNCOM_VERSION "MISSING"
#endif
#ifndef MIDIBAS_VERSION
#define MIDIBAS_VERSION "MISSING"
#endif
#ifndef MIDI_TYPE
#define MIDI_TYPE "MISSING"
#endif

/*FUNCTION MACROS*/
#define BACKGROUND 010
#define MAX(A,B) (A ≥ B ? A : B)
#define MIN(A,B) (A ≤ B ? A : B)
#define SGN(N) (N < 0 ? 1 : (N > 0 ? -1 : (N == 0 ? 0 : NAN)))
#define CLAMP(A,N,B) MIN(MAX(A,N),B)
#define COORDSUB(Z,Y,X) ((MAX_Y * Z) + (MAX_X * Y) + X)

// kludge so that stdio and ncurses play nice together
#define RESET "\033c\033[2J\033[0H"
#define BREAKCURSES clear();refresh();endwin();printf(RESET);fflush(stdout);
#define FIXCURSES printf(RESET);fflush(stdout);initialize();while (fgetc(stdin) != '\n');refresh;
#define BLINKY "\033[5m_\033[25m"

#define MACRO__DLLIST_NOCIRC_PUSH(HEAD,NEW) {\
	NEW->prev = HEAD->prev;\
	HEAD->prev->next = NEW;\
	NEW->next = NULL;\
	HEAD->prev = NEW;\
	}

#define MACRO__DLLIST_NOCIRC_FREE(HEAD,DEADBEEF) {\
	if (HEAD->prev == DEADBEEF) {\
		HEAD->prev = HEAD->prev->prev;\
		HEAD->prev->next = NULL;\
		}\
	else if (HEAD == DEADBEEF) {\
		HEAD = HEAD->next;\
		HEAD->prev = DEADBEEF->prev;\
		}\
	else {\
		DEADBEEF->next->prev = DEADBEEF->prev;\
		DEADBEEF->prev->next = DEADBEEF->next;\
		}\
	free(DEADBEEF);\
	}\		

#define MACRO__DLLIST_INSERT(PREV,NEW) {\
	NEW->prev = PREV;\
	NEW->next = PREV->next;\
	PREV->next->prev = NEW;\
	PREV->next = NEW;\
	}

#define MACRO__DLLIST_CIRCLE_FREE(HEAD,DEADBEEF) {\
	if (HEAD->prev == DEADBEEF) {\
		HEAD->prev = HEAD->prev->prev;\
		HEAD->prev->next = HEAD;\
		}\
	else if (HEAD == DEADBEEF) {\
		HEAD = HEAD->next;\
		HEAD->prev = DEADBEEF->prev;\
		HEAD->prev->next = HEAD;\
		}\
	else {\
		DEADBEEF->next->prev = DEADBEEF->prev;\
		DEADBEEF->prev->next = DEADBEEF->next;\
		}\
	free(DEADBEEF);\
	}\
