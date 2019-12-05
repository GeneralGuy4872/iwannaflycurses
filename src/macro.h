/*TYPES*/
//ensure size names work on all systems
#define uint unsigned int
#define uchar unsigned char
#define ushort unsigned short
#define ulong unsigned long
#define 8BITPTR uint8_t

#define ≥ >=
#define ≤ <=
#define forever for (;;)
#define END return 0;}
#define ↑ [0]

#define ARRY_X 0
#define ARRY_Y 1
#define ARRY_Z 2
#define ARRY_W 3

/* syntactic sugar for macros that are actually tailcalls
 * such macros contain a return or this macro
 */
#define tailcall(X) X

#ifndef EOF
#error now you're just TRYING to break stuff...
#endif

#ifndef NULL
#warning ... ...wh ... ... how??
#define NULL ((void*)0)
#endif

#define TRUE true
#define True true
#define FALSE false
#define False false

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
#define BALTERN_3(X,Y,Z) ((sgn(Z) * 9) + (sgn(Y) * 3) + sgn(X))
#define COORDSUB(Z,Y,X) ((MAX_Y * Z) + (MAX_X * Y) + X)
#define SWAP(X,Y) {if (X != Y) {intptr_t sWaPtEmPoRaRy = X;Y = X;X = sWaPtEmPoRaRy}}\

// kludge so that stdio and ncurses play nice together
#define RESET "\033c\033[2J\033[0H"
#define BREAKCURSES clear();refresh();endwin();printf(RESET);fflush(stdout);
#define FIXCURSES printf(RESET);fflush(stdout);initialize();while (fgetc(stdin) != '\n');refresh;
#define BLINKY "\033[5m_\033[25m"

#define MACRO__DLLIST_HALFCIRC_PUSH(HEAD,NEW) {\
	NEW->prev = HEAD->prev;\
	HEAD->prev->next = NEW;\
	NEW->next = NULL;\
	HEAD->prev = NEW;\
	}

#define MACRO__DLLIST_HALFCIRC_PUSH(NEW,TAIL) {\
	NEW->prev = TAIL;\
	TAIL->next = NEW;\
	NEW->next = NULL;\
	TAIL = NEW;\
	}

#define MACRO__DLLIST_HALFCIRC_FREE(HEAD,DEADBEEF) {\
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

#define MACRO__DLLIST_NOCIRC_FREE(HEAD,DEADBEEF,TAIL) {\
	if (TAIL == DEADBEEF) {\
		TAIL = TAIL->prev;\
		TAIL->next = NULL;\
		}\
	else if (HEAD == DEADBEEF) {\
		HEAD = HEAD->next;\
		HEAD->prev = NULL;\
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

#define MACRO__DLLIST_CIRCLE_FREE(DEADBEEF) {\
	DEADBEEF->next->prev = DEADBEEF->prev;\
	DEADBEEF->prev->next = DEADBEEF->next;\
	free(DEADBEEF);\
	}\

#define MACRO__DLLIST_NOCIRC_SWAP(HEAD,FOO,BAR,TAIL) {if ((HEAD != NULL) && (TAIL != NULL) && (FOO != NULL) && (BAR != NULL)) {\
	if (FOO == HEAD) {\
		if (BAR == TAIL) {\
			FOO->prev = BAR->prev;\
			BAR->next = FOO->next;\
			BAR->prev = NULL;\
			FOO->next = NULL;\
			SWAP(HEAD,TAIL);\
			}\
		else {\
			FOO->prev = BAR->prev;\
			SWAP(FOO->next,BAR->next);\
			BAR->prev = NULL;\
			HEAD = BAR;\
			}\
		}\
	else if (FOO == TAIL) {\
		if (BAR == HEAD) {\
			FOO->next = BAR->next;\
			BAR->prev = FOO->prev;\
			BAR->next = NULL;\
			FOO->prev = NULL;\
			SWAP(HEAD,TAIL);\
			}\
		else {\
			FOO->next = BAR->next;\
			SWAP(FOO->prev,BAR->prev);\
			BAR->next = NULL;\
			HEAD = BAR;\
			}\
		}\
	else {\
		if (BAR == HEAD) {\
			BAR->prev = FOO->prev;\
			SWAP(FOO->next,BAR->next);\
			BAR->prev = NULL;\
			HEAD = FOO;\
			}\
		else if (BAR == TAIL) {\
			BAR->next = FOO->next;\
			SWAP(FOO->prev,BAR->prev);\
			FOO->next = NULL;\
			TAIL = FOO;\
			}\
		else {\
			SWAP(FOO->prev;BAR->prev);\
			SWAP(FOO->next;BAR->next);\
			}\
		}\
	}\
else {\
	lambda = ERR;\
	}}\

#define MACRO__DLLIST_HALFCIRC_SWAP(HEAD,FOO,BAR) {if ((HEAD != NULL) && (FOO != NULL) && (BAR != NULL)) {\
	if (FOO == HEAD->prev) {\
		if (BAR == HEAD) {\
			BAR->prev = FOO->prev;\
			FOO->next = BAR->next;\
			FOO->prev = BAR;\
			BAR->next = NULL;\
			HEAD = FOO;\
			}\
		else {\
			FOO->next = BAR->next;\
			SWAP(FOO->prev,BAR->prev);\
			BAR->next = NULL;\
			HEAD->prev = BAR;\
			}\
		}\
	else if (BAR == HEAD->prev) {\
		if (FOO == HEAD) {\
			FOO->prev = BAR->prev;\
			BAR->next = FOO->next;\
			BAR->prev = FOO;\
			FOO->next = NULL;\
			HEAD = BAR;\
			}\
		else {\
			BAR->next = FOO->next;\
			SWAP(FOO->prev,BAR->prev);\
			FOO->next = NULL;\
			HEAD->prev = FOO;\
			}\
		}\
	else {\
		SWAP(FOO->prev;BAR->prev);\
		SWAP(FOO->next;BAR->next);\
		}\
	}\
else {\
	lambda = ERR;\
	}}\

#define MACRO__DLLIST_CIRCLE_SWAP(FOO,BAR) {if ((FOO != NULL) && (BAR != NULL)) {\
	SWAP(FOO->prev;BAR->prev);\
	SWAP(FOO->next;BAR->next);\
	}\
else {\
	lambda = ERR;\
	}\
