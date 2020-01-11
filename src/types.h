/* todo:
 * tools implementation as a pair of arrays;
 * one array of normal item data
 * and a second that is a dispatch table.
 */

#ifndef IWANNAFLY_TYPES_H_REENTRANT
#define IWANNAFLY_TYPES_H_REENTRANT 1

/* note: if the compiler complains about mixing tightly packed and loosly packed fields,
 * the tightly packed ones will be split off into a seperate type with "_bits" affixed to
 * the name, which will be placed in a consistantly-named member "_bits" at the end of the struct.
 */

#define uint unsigned int
#define uchar unsigned char
#define ushort unsigned short
#define ulong unsigned long
#define 8BITPTR uint8_t

struct odds_n_ends {
uint64_t turn;
turntype date;
uchar roomturn;
cameratyp camera;
bool new : 1;
bool first : 1;
bool day : 1;
bool night : 1;
bool morn : 1;
bool noon : 1;
bool eve : 1;
bool midnit : 1;
}

struct stringlistyp {
(self) *prev
(self) *next
char* text
}
/* used to store a list of strings
 * may be from a data object, or
 * stored in a tsv
 */

struct singlestringlistyp {
(self) * next
char * text
}

struct filelinetyp {
(self) *prev
(self) *next
ushort lineno
char* text
}
// used by the line editor

struct singlestringlistyp {
(self) * next
ushort lineno
char * text
}

/*depracated
struct blitimgcolor {
	struct attr_t attr[6];
	uchar fgcolor[4];
	uchar bgcolor[4];
	char ** img[16];
	}
	?*			[0]	[1]	[2]	[3]	fgcolor
	 *			0x0000	[0]	[1]	[2]	attr
	 *	[0]	0x0000	[0]	[1]	[2]	[3]	img
	 *	[1]	[3]	[4]	[5]	[6]	[7]
	 *	[2]	[4]	[8]	[9]	[10]	[11]
	 *	[3]	[5]	[12]	[13]	[14]	[15]
	 *	bgcolor	attr
	 * the first row and column never have any attributes
	 * NULL img pointers are skipped, rather than acting as sentries
	 */

struct drawvector {
	ucoord3 a;
	ucoord3 b;
	char16_t ch;	// if set to \0, then assume that attr also holds an ascii symbol and switch accordingly.
	struct attrcolortyp attrcolor;
	ushort uslp;	/* how long to delay between each character; calls usleep.
			 * there is already a miniscule delay for the stepwise pathfinder calculation
			 */
	}

/* note: make function where some glyph is swept to some azimuth
 * ( char16_t unichar, struct attrcolortyp attrcolor, uchar az ¿, float dist?, ushort uslp)
 */

/* not implemented yet
struct glyphtyp {
unsigned typ;
int attrs;
void *glyph;
}
?* cast void to (OR flags) :
 *
 * 0x80 : char16_t instead of char
 * 0x70 : elements are nul terminated strings of whatevers
 * 0xn0 : for 1 ≤ n ≤ 6, elements are fixed sized arrays of n whatevers
 *
 * 0x00 : toplevel is not an array
 * 0x01 : [10] = {up,north,ne,left,se,south,sw,right,nw,down}
 * 0x02 :  [2] = {left,right}
 * 0x03 :  [2] = {north,south}
 * 0x04 :  [4] = {north,left,south,right}
 * 0x06 :  [6] = {up,north,left,south,right,down}
 * 0x07 :  [8] = {north,ne,left,se,south,sw,right,nw}
 */

struct chaptertyp {
unsigned c : 7;	//chapter number
unsigned a : 9;	//alignment type
}

struct turntyp:
uchar sec : 6;
uchar min : 6;
uchar hour : 5;
uchar day : 5;
uchar weekday : 3;
uchar month : 4;
ushort year : 11;

typedef uchar ucoord3[3];
typedef uchar ucoord2[2];
typedef char scoord3[3];
typedef char scoord2[2];
//sentinal for an array of coord3 is {0,0,-1}

struct setcoord3 {
struct setcoord3 * prev
struct setcoord3 * next
uchar x
uchar y
uchar z
}

typedef char *strarry[]
typedef void *ptrarry[]

struct lightyp {
struct lightyp * prev
struct lightyp * next
unsigned x : 7;
unsigned y : 5;
unsigned z : 4;
unsigned xx : 7;
unsigned yy : 5;
unsigned zz : 4;
}

struct agetyp {
	unsigned chrono : 16;
	signed bio : 8;	//entity dies on overflow
	unsigned rem : 8;	/* bio remainder after chrono;
	}			 * bio increments on the next modulo_0 of
				 * the entity's current aging factor
				 * (href basentyp). exploiting the
				 * immediately apparent flaw of this
				 * behavior by frequently shapeshifting
				 * is allowed; but has it's own side
				 * effects. (href shiftstackobj)
				 */

struct mapcoord3:
unsigned x : 7
unsigned y : 5
unsigned z : 4

struct chgat_args_typ {
	uchar y;
	uchar x;
	char n;
	attr_t attr;
	short color;
	}

struct nibbles {
unsigned lo : 4
unsigned hi : 4
}

struct cameratyp {
unsigned dir : 4	//href CAMERA_? in constants.h
bool seeinvis : 1
bool detectalign : 1
bool arrows : 1
bool dingbats : 1
}

struct racetyp {
intptr_t race : 8
intptr_t table : 4
unsigned meta : 4
	// 00,0,F is nul
}

struct attrcolortyp {
	attr_t attr;
	short color;
	}

typedef nanovector {
signed x : 2
signed y : 2
signed z : 2
signed w : 2
}

typedef float vector2[2]
typedef float vector3[3]
//not implemented
/* used for velocity, a parameter that holds
 * motion that carries accross turns. this motion
 * is not always cleared after being done; horizontal
 * velocity persists until a tile with friction is
 * encountered, while downwards vertical velocity 
 * accumulates and persists until the ground is encountered.
 */

typedef char *pluralwords[3];

#define MOVETOKEN_LAND 4
#define MOVETOKEN_FLY 1
#define MOVETOKEN_SWIM 2

struct selftyp {
unsigned az : 3
unsigned phi : 3
unsigned fov : 2
unsigned range : 6
unsigned movetoken : 2
unsigned gravdir : 3 //not implemented
char : 0 // 5 pad
}

struct beamtyp {
unsigned az : 3	//azimuth
unsigned phi : 3	//elevation in eighth turns. 07 is omnidirectional.
unsigned ang : 4	//total solid angle of spread in twelfths of a circle.
unsigned range : 6
}
/* for all azimuths:
 *
 * 701
 * 6 2
 * 543
 *
 * for all elevations:
 *
 * +1
 *  0  ?-2?
 * -1
 */

/*
 * notetyp {
 * (self) next
 * unsigned evnt : 4
 * unsigned chan : 4
 * unsigned note : 8
 * unsigned velo : 8
 * clock_t delay
 * }
 * for interfacing with a raw midi library
 *
 * delay is not part of the midi data, rather,
 * it tells how long to wait until sending the
 * next packet. set to 0 to send immidiately.
 */

/* typedef short sprite[16]
 * typedef sprite *voxel[5]	?/ top, bottom, sides, front, back. if front or back == NULL, side is substituted.
 * typedef sprite vwing[2]	?/ front and back only
 *
 * for future use by a vector graphics library, for 3d rendering by algorithem
 * in non-isogonal modes, single-point perspective is used; points are calculated by adverageing the boundries of a voxel box's perpendicular sides.
 * perpindicular side sizes are calculated by altering the camera's distance and focal length
 *
 * these types provide an abstraction layer for an xlib- or xcb-like frontend,
 * uses a 17*17 point vector grid, distorted according to the perspective, to draw squares for each 1-bit in the sprite array.
 */

//some specific use cases require spheres. these are simply numeric types.

struct diceodds:
unsigned num : 3
unsigned side : 5
unsigned tobeat : 8

struct planetyp {
unsigned rho : 2
unsigned az : 3
signed el : 2
char : 0
}

struct latlontyp {
unsigned dep : 8
unsigned lat : 8
unsigned lon : 9
unsigned rho : 2	//are you plane shifted?
unsigned az : 3
signed el : 2
}
/* in-game altitude is given as the distance from layer 100
 *
 * rho 0 is the prime plane
 * rho 1 are the elemental planes
 * rho 2 are afterlives
 * rho 3 can be used for areas that are meant to not show up on a map.
 *			(said map would be implemented with pipes)
 *
 * az	elemental	afterlife	corrilation
 * 0	water		neutral good	nurturer
 * 1	ice		chaotic good	the ends justify the means
 * 2	air		chaotic neutral	insert obscure fourswords reference here
 * 3	electricity	chaotic evil	force lightning
 * 4	fire		neutral evil	obviously
 * 5	metal		lawful evil	greed
 * 6	earth		lawful neutral	stubborn
 * 7	trees		lawful good	knowladge
 *
 * az rotates by 45 degree steps and el by 90 degree steps.
 * a nonzero el causes az to gimbal lock.
 * also best not to think about where exactly -2 is pointing.
 *
 * el	"		"		"
 * +1	light		true neutral	enlightenment
 * -1	darkness	uncomitted	meh, I'll think of one later
 * -2	entropy		oathbreakers	abandon all hope ye who enter here
 *
 * errors related to this section may generate one of 2 errors:
 * "fell off the edge of the world", N1=±lat,N2=±lon
 * "froze to death on pluto", N1=+az,N2=±el
 *
 * a room stack exists that keeps a number of rooms loaded
 * if a room is not on the stack, it is loaded from the save file and
 * pushed to the stack. this may cause the stack to intentionally drop
 * the room at the bottom to prevent eating too much ram. if the file
 * does not yet exist, the room is generated according to a dispatch table
 * in a shared object. if the function and file are both NULL and the
 * room is being entered, a lost in space death is called. if only the
 * function is NULL, the file is executed in perl. if only the file is
 * NULL, no shared objects are loaded before the function is called. 
 *
 * a swap array keeps track of gating between the 23 major planes,
 * saving the player's position, but not keeping the room loaded.
 */

struct placetyp {
(self) *prev
(self) *next
eventdata eventident
char* name
latlontyp latlon
ucoord3 pos
}

typedef short trackaligntyp[2]
typedef short trackalignplayertyp[3]
/* neutral is the area between -10,000 and 10,000
 * alignments can be between -30,000 and 30,000
 * actions, quests, and being polymorphed into
 * certain monsters can alter your alignment
 * [0] is good/evil, [1] is lawful/chaotic
 *
 * for players, proactivness/passivity is also
 * tracked
 *
 * most negative number in both fields is an antagonist
 */

struct bitfield:
a : 1
b : 1
c : 1
d : 1
w : 1
x : 1
y : 1
z : 1

struct ray_vfx_typ {
(self) * prev
(self) * next
ucoord3 p
uchar dir	//must be a valid octant
float mag
struct attrcolortyp ac
}

struct multiclasstyp:
(self) *prev
(self) *next
bool notnull : 1
unsigned role : 2
unsigned class : 3
unsigned mastery : 2

struct classtyp {
bool notnull : 1
unsigned role : 2
unsigned class : 3
unsigned mastery : 2
}

struct baseclasstyp {
struct paffectyp bonus
uchar spd
char airspd
uchar air
struct conlangtyp lang
_8BITPTR spell[2]
bitfield psyattack
bool mindless : 1
bool shadow : 1
bool incoporeal : 1
bool immortal : 1
unsigned lde : 3	//grants
unsigned alignment : 9	//requires
unsigned element : 8	//grants
}

struct the8stats:	//8* 5D6
stren : u5
psy : u5
dex : u5
con : u5
fort : u5
intl : u5
wis : u5
bluff : u5

struct movecount {
uchar lungs //number of turns that you can go without air.
uchar spd //added to move each turn
char airspd	/* if this is negative, then it's value is immediately
		 * subtracted from move whenever flying is attempted.
		 * otherwise, added to fly each turn
		 */
char knots //ditto but added to swim
float move //value is capped at 2*spd
float fly 	/* carries the extra moves that can be used in the air;
		 * they are used first when applicable
		 */
float swim //ditto but used in water
scoord3 skillgain	/* [0] = ground, [1] = water, [2] = air.
			 * when these overflow, a skill level is
			 * gained if applicable, and they are zeroed.
			 * the existance of a negative value other than
			 * the most negative number in these fields
			 * indicates that an error has occured
			 */
uchar breath //number of turns left before you drown
}

struct conlangtype:
unsigned id : 5
bool r : 1
bool w : 1
bool x : 1	//can be spoken

struct xtraplayertyp {
chaptertyp chapter;
uint64_t kills;
uchar elecollect[8];
uchar questcollect[3];
}

/* note: everything related to players and entitys is
 * copied into the struct, because it might be changed.
 * the base entities and base classes are only templates.
 *
 * whenever you "rest" in-game, all entities are re-verified;
 * meaning that all effect registers are recalculated. this
 * has the side effect of removing any non-item based buffs
 * and debuffs. this should be one of the only times that
 * a baseclasstyp or basentyp are referenced; the others
 * being adding a class, looseing a class, advancing in a class,
 * polymorphing, polylocking, by the renderer,
 * and when spawning a new entity.
 *
 * some stats are spread out accross multiple fields in the structure;
 * most effects have one field for permenant and one field for temporary
 * versions of the effect. a handful of alteration spells have a third
 * register, with the polymorph stack, for timed spells, since the
 * other temporary slot has no timer.
 *
 * nearly all fields of the player struct are created by COMBINING the
 * basentyp and baseclasstyp chosen at the creation of the savefile.
 * the remainder are based on backstory and user input.
 */

struct playertyp:
char * name
classtyp class[3]
uchar element
agetyp age
struct shiftstackobj race
ucoord3 pos
selftyp etc
struct movecount move
paffectyp paffect	//permenant
effectyp effect	//from equipment
trackalignplayertyp align
ushort hp	//they're fun and easy to...wait
ushort mp
uint32_t xp
uchar lvl
short food
float wallet
langlistele *lang_ptr
spellistele *spell_ptr
heldobjtyp *bag_ptr
bitfield psyattack
oneobjtyp helm	//any item
subobjtyp shield	//shld
subobjtyp bow	//weapon
subobjtyp armor	//armor
subobjtyp cape	//armor
subobjtyp amul	//baub
unsigned n_arms : 4
unsigned n_legs : 4
armtyp *arms[2]
legtyp *legs[2]

struct armtyp {
struct armtyp * next
subobjtyp weap[2]
subobjtyp ring[2]
subobjtyp wrist[2]
subobjtyp gloves
subobjtyp cannon
}

struct legtyp {
legtyp * next
subobjtyp boots
subobjtyp greev
}

enum equipenum = {ENUM_WEAP_LEFT,ENUM_WEAP_RIGHT,ENUM_SHIELD_ENUM_BOW,ENUM_ARMOR,ENUM_CAPE,ENUM_HELM,
ENUM_GLOVES,ENUM_CANNON,ENUM_BOOTS,ENUM_GREEV,ENUM_AMUL,ENUM_RING_LEFT,ENUM_RING_RIGHT,ENUM_WRIST_LEFT,
ENUM_WRIST_RIGHT}

struct basentyp:
aggrotyp aggro	//here, shiftable denotes a monster's aggro state is locked. also gives the value that patience is set to when a monster calms down, the value that cooldown is set to when it is angered, and the default AI.
paffectyp base
unsigned n_arms : 4
unsigned n_legs : 4
uchar spd	//distance calculations use M_SQRT2 and local SQRT3 for diagonals
char airspd
uchar hplvl
uchar mplvl
uchar xplvl
uchar air	//how long you can hold your breath
struct conlangtyp lang[2]
_8BITPTR spell[4]
bitfield psyattack
char16_t sprite
struct attrcolortyp attrcolor
char16_t altsprite
struct attrcolortyp altattrcolor
signed size : 2
bool mindless : 1
bool shadow : 1
bool incoporeal : 1
unsigned age_rate : 8
unsigned element : 8
unsigned lde : 3
/* entitys of size 1 or -2 cannot use armor.
 * entitys of larger size automaticly win grapples.
 * entitys of 2 sizes smaller can be picked up and thrown.
 * entitys of size 1 can instakill entitys of size -2. squish.
 * size 1: dragon, size 0: human, size -1: dwarf, size -2: pixie
 */

struct aggrotyp:
bool unhinged : 1
unsigned patience : 3
unsigned ai_type : 4
unsigned anger : 8

struct enttyp:
(self) *prev
(self) *next
npctyp * depth
agetyp age
classtyp class
uchar element
aggrotyp aggro
struct shiftstackobj race
ucoord3 pos
selftyp etc
struct movecount move
paffectyp paffect
effectyp effect
ushort hp
ushort mp
uint32_t xp
uchar lvl
float wallet
oneobjtyp loot
oneobjtyp helm
subobjtyp shield
subobjtyp bow
subobjtyp armor
subobjtyp cape
subobjtyp amul
unsigned n_arms : 4
unsigned n_legs : 4
armtyp *arms[2]
legtyp *legs[2]

struct npctyp {
(self) *prev
(self) *next
ucoord3 * path
char * describe
uchar lang
char **lines[9];	//accessor: (lines[n])[m]
}
/* npc data is controlled by events, and is stored by room or in
 * global space. more complex actors, such as shopkeepers,
 * should be events.
 */

struct followtyp:
(self) * prev
(self) * next
npctyp * depth
agetyp age
classtyp class
uchar element
aggrotyp aggro
struct shiftstackobj race
ucoord3 pos
selftyp etc
struct movecount move
paffectyp permenent
effectyp fromequip
trackaligntyp align
ushort hp
ushort mp
uint32_t xp
uchar lvl
short food
float wallet
bitfield psyattack
oneobjtyp holding
oneobjtyp helm
subobjtyp shield
subobjtyp bow
subobjtyp armor
subobjtyp cape
subobjtyp amul
unsigned n_arms : 4
unsigned n_legs : 4
armtyp *arms[2]
legtyp *legs[2]

struct spawntyp:
npctyp * depth
classtyp class
uchar element
aggrotyp aggro
struct shiftstackobj race
paffectyp paffect
effectyp effect
oneobjtyp loot
oneobjtyp helm
subobjtyp shield
subobjtyp bow
subobjtyp armor
subobjtyp cape
subobjtyp amul
unsigned n_arms : 4
unsigned n_legs : 4
armtyp *arms[2]
legtyp *legs[2]

struct oneobjtyp {
objid type
void* data
}

struct heldobjtyp:
(self) *prev
(self) *next
uchar stack //stack+1 items are present. lumping them together is a complicated operation. 
objid type
void* data

struct langlistele {
(self) * prev
(self) * next
struct conlangtyp data
}

struct spellistele {
(self) * prev
(self) * next
_8BITPTR data
}

struct subobjtyp:
intptr_t itemid : 8
bool cursed : 1
bool oxide : 1
bool burned : 1
signed bonus : 5
intptr_t metadata : 8 //secondary _8bitPtr for legendary objects

struct magictyp:
bool fire : 1
bool air : 1
bool water : 1
bool earth : 1
unsigned lde : 3
bool planer : 1

struct shiftstackobj {
bool topdeck : 1; //does every shift change base[0]?
bool lycan : 1;	//is base[1] valid?
bool swap : 1 //base[swap]
signed depth : 5;	//on overflow, the stack is freed an topdeck is set
struct racetyp base[2];
struct shiftstackele * poly;	//unless this is NULL, this overrides base[]
struct shiftertyp alters;
}

struct shiftstackele {
struct shiftstackele * prev;
unsigned polytimer : 8;	//time remaining in the current polymorph.
intptr_t race : 8;
intptr_t table : 4;
unsigned meta : 4;
}/* polymorphing to the same form twice causes your active base form to change.
  * some ways of aquireing multi-form abilities may place restrictions on what your second form may be.
  */

struct altertimertyp {
	signed n : 5;	//permenant on overflow
	bool q : 1;
	char : 0;
	unsigned t : 8;
	}

struct altertimerwtyp {
	signed n : 5;	//permenant on overflow
	bool q : 1;
	unsigned w_typ : 2;
	bool w_sgn : 1;
	unsigned t : 7;
	}

struct shiftertyp {
struct altertimertyp gills;	//using an alteration spell, including intrensics from polymorph spells, 10 times will make them permenent.
struct altertimertyp lungs;	//these counters can be reset by rest or spells
struct altertimerwtyp wings;
struct altertimertyp tail;
struct altertimertyp claws;
struct altertimertyp fangs;
struct altertimertyp talons;
}/* non-player, non-follower entitys do not have this field,
  * and any polymorph or alteration is permenent. this may be
  * changed in future if memory footprint allows.
  */

struct spelltyp:
intptr_t itemid : 8
diceodds odds
uchar prof

struct basespelltyp:
bool poly : 1
bool self : 1
unsigned lvl : 6
magictyp type
char cost_typ : 2 //0 = at will, 1 = gold, -1 = mp, -2 = hp
unsigned cost_amnt : 6
potiontyp effect
beamtyp delivery
intptr_t polyref : 8

struct psytyp:
signed cost_typ : 2 //0 = at will, 1 = gold, -1 = mp, -2 = hp
unsigned cost_amnt : 6
potiontyp effect
missiletyp delivery

struct missiletyp:
bool psion : 1
bool vamp : 1
unsigned damage : 8
signed recoil : 8
unsigned range : 6
unsigned spread : 4
unsigned splash : 3 //radius of damage on impact
bool dig : 1 
}

struct baseweaptyp:
bool fire : 1
bool air : 1
bool water : 1
bool earth : 1
bool entro : 1
bool light : 1
bool dark : 1
bool fireproof : 1
bool waterproof : 1
bool elecproof : 1
bool iceproof : 1
bool warded : 1
bool illum : 1
unsigned skill : 3
unsigned damage : 8

legendtyp:
paffectyp magic
symtableref base
symtableref spell
legendflagtyp flags

legendflagtyp:
bool fire : 1
bool air : 1
bool water : 1
bool earth : 1
bool entro : 1
bool light : 1
bool dark : 1
bool fireproof : 1
bool waterproof : 1
bool elecproof : 1
bool iceproof : 1
bool warded : 1
bool unbreak : 1
bool infinate : 1
bool spelled : 1
bool vamp : 1
bool drain : 1
bool interest : 1
bool useless : 1
unsigned powermag : 5

struct basearmortyp:
effectyp effect
uchar def
uchar spdef
uchar extfort

struct baseshldtyp:
bool fireproof : 1
bool waterproof : 1
bool elecproof : 1
bool iceproof : 1
bool reflect : 1
bool entro : 1
bool light : 1
bool dark : 1
effectyp effect
unsigned def : 8
unsigned spdef : 8

struct bodytyp {
bool gills : 1;	//affects breathing underwater
bool wings : 1;	//affects flying
bool tail : 1;	//affects unarmed attacks, swimming, flying
bool claws : 1;	//affects unarmed attacks, writing
bool hoof : 1;	//affects walking, swimming, unarmed attacks
bool talon : 1;	//affects walking, swimming, unarmed attacks 
bool fangs : 1;	//affects unarmed attacks
bool legs : 1;	//affects walking, swimming, unarmed attacks
bool arms : 1;	//affects walking, swimming, unarmed attacks, writing
bool nolungs : 1;	//affects breathing above water
bool noswim : 1;	//affects swimming
bool nofly : 1;
bool atktail : 1;	//affects unarmed attacks, swimming, flying
bool atkwing : 1;	//affects unarmed attacks, swimming, flying
bool bite : 1;
bool breath : 1;
bool engulf : 1;
bool permwings : 1;
bool wingsign : 1;
unsigned wingtype : 2;
char : 0;
}

struct stattyp {
unsigned dizzy : 3;
unsigned psn : 4;
unsigned prlz : 4;
unsigned frz : 4;
unsigned brn : 4;
signed stone : 8;	//inverse one's complement; 0x00 is inactive (-0), 0xFF is dead (+0). overflows can be used to extend time to live
signed slime : 8;	//inverse one's complement
unsigned slp : 8;
unsigned invis : 6;
unsigned blind : 8;
signed eaten : 7;	//inverse one's complement
}

struct elixtyp:
dizzy : 1
psn : 1
prlz : 1
frz : 1
brn : 1
stone : 1
slp : 1
invis : 1

struct cursetyp:
stattyp type
uchar polytimer
intptr_t poly : 8

struct resistyp:
bool fireproof : 1
bool waterproof : 1
bool elecproof : 1
bool iceproof : 1
bool stoneproof : 1
bool polyproof : 1
bool sleepproof : 1
bool poisonproof : 1

struct sensetyp:
bool trouble : 1
bool invis : 1
bool infra : 1
bool blind : 1
bool good : 1
bool evil : 1
bool law : 1
bool chaos : 1

struct effectyp:
the8stats eight
bodytyp shape
stattyp stat
resistyp resist
sensetyp sense
skilltyp skill
char atk
char spatk
char def
char spdef

struct paffectyp:
the8stats eight
bodytyp shape
elixtyp ails_ya
resistyp resist
sensetyp sense
skilltyp skill
venomtyp venom
char atk
char spatk
char def
char spdef

struct potiontyp:
bodytyp shape
elixtyp ails_ya
cursetyp curse
resistyp resist
sensetyp sense
short hp
short mp
diceodds odds

struct skilltyp {
unsigned sword : 4; //+skill to sword-type weapon attack
unsigned knife : 4; //+skill to knife-type weapon attack
unsigned stave : 4; //+skill to stave-type weapon attack
unsigned spear : 4; //+skill to spear-type weapon attack
unsigned whip : 4; //+skill to whip-type weapon range (unused range added to attack)
unsigned club : 4; //+skill to club-type weapon attack
unsigned bow : 4; //+(2 * skill) to bow-type weapon range
unsigned throw : 4; //+(2 * skill) to javalin-type weapon range
unsigned monk : 4; //+(2*skill) to unarmed attack, unlocks more modes of attack.
unsigned shield : 4; //skill in (damage-defense)+abs(damage-defense) chance of blocking
unsigned locks : 4; //1 in 2^(lock.level - (skill)) chance of picking
unsigned caster : 6; //-(skill-1)/4 to casting cost, +(skill-1)/4 to spatk and spdef, unlocks spells, 0 is non-caster
bool swim : 1; //may be lost by polymorphing to a form with different locomotion.
bool walk : 1; //may be lost by polymorphing to a form with different locomotion.
unsigned fly : 2; //0 = never had wings, 1 = slow falling, 2 = cannot gain altitude, 3 = free flight. lvl1 learned by falling
bool sink : 1; //overrides any swim or fly skills
bool magnetic : 1;
}
/* damage = MAX( incoming-defense , 0 )
 *
 * polyshock = base.hplvl - ((poly.hplvl * (util__roll(1,20,1) / 20)) * util__roll(1,3,0))
 * ⎧if n < -HPMAX     : Instakill (deathmessage: miscalculated a crucial equivilant-exchange parameter,hath choose...poorly)
 * ⎪if n = -HPMAX     : Stoning
 * ⎨if -HPMAX < n < 0 : abs(n) Damage (deathmessage: could not withstand the cost of transmutation)
 * ⎪if n = 0          : stun for 1D16 (standardmessage: your mind reels from the transformation...)
 * ⎩if n > 0          : success
 *
 * writing =
 * succeed if 4D6 < dex if !talons, break pen on fail if 1D20 < stren
 * succeed if 6D6 < dex if talons, break pen on fail if coinflip
 * talons can engrave without tools
 */

readtyp:
unsigned locale : 6
bool multiuse : 1
bool scroll : 1
unsigned subject : 2 //0 = cooking, 1 = weapons, 2 = language, 3 = spellcraft
unsigned uses : 6
void* contents

wandtyp:
unsigned matter : 4
unsigned uses : 4
intptr_t bound : 8

baubtype :
signed type : 2 //0=ring, 1=bracelet, -1=amulet, -2=tiara
unsigned matter : 3
unsigned color : 3
paffectyp enchnt

struct roomneighbors {
bool north
bool south
bool east
bool west
bool up
bool down
bool upstair
bool downstair
latlontyp latlon[6]	//href ROOM_? in constants.h
}

struct roomtyp: //top-down display of a 3d space
latlontyp latlon
tileset *hightiles
char* tiledata[][MAX_Y][MAX_X]
unsigned ceiling : 4
unsigned bgcolor : 3
bool visited : 1
shadowmask * seen
shadowmask * light
shadowmask * collimap	//entity collision mask
encontyp *encon_ptr
enttyp *ent_ptr
eventtyp *ev_ptr
mapobjtyp *obj_ptr
ray_vfx_typ *ray_ptr
lightyp *light_ptr
char skylightsource	//must be a valid octant
ucoord3 * path_ptr
ucoord2 downstair
ucoord2 upstair
ucoord3 home
struct roomneighbors neighborhood
/* if invalid coords are given for a warp (typically {$FF,$FF}),
 * then the player is dumped at the location indicated by home.
 *
 * if the player has invalid coords, then the error string "fell out of terminal",N1=x,N2=y is generated.
 */

/* the world of the game will be referred to using two different grids of
 * discreet coordinates. the primary grid is the cell space, which is
 * interleaved octohedrally with the boundry space, such that if a given
 * diminsion in cell space has n points, the same dimension in boundry
 * space has n+1 points. the cell space referes to the cells that are
 * displayed (the "cells"), while the boundry space referes to their
 * boundries. exact boundry space coordinates are not expected to be used;
 * only planes and polytopes are meaningful in boundry space.
 *
 * some notable uses of boundry space are in describing the emulated
 * cull plane of the "camera", and as the boundries of a given room.
 */

struct subroomtyp: //used by mapgen
char tiledata[MAX_Z][MAX_Z][MAX_Z]	//cube of MAX_Z
ucoord3 dim
enttype *ent_ptr
mapobjtyp *obj_ptr

struct mapgen_bordertyp {
tileset *hightiles_n
char north[MAX_Z][MAX_X]
tileset *hightiles_s
char south[MAX_Z][MAX_X]
tileset *hightiles_e
char east[MAX_Z][MAX_Y]
tileset *hightiles_w
char west[MAX_Z][MAX_Y]
tileset *hightiles_ne
char northeast[MAX_Z]
tileset *hightiles_nw
char northwest[MAX_Z]
tileset *hightiles_se
char southeast[MAX_Z]
tileset *hightiles_sw
char southwest[MAX_Z]
tileset *hightiles_u
char up[MAX_Y][MAX_X]
tileset *hightiles_d
char down[MAX_Y][MAX_X]
}
/* only used during mapgen, freed immediatly since it's so huge
 * up and down do not need secondary directions as the map cannot be scrolled that way
 */

typedef ushort shadowmask[MAX_Y][MAX_X]
typedef bitfield starfield[MAX_Y][MAX_X/8]

typedef ushort collisionmapcols[MAX_Y+2][MAX_X+2]
typedef uchar collisionmapholes[MAX_Y][MAX_X/8]

struct collisionmaptyp {
	collisionmapcols solid
	collisionmapholes holes
	shadowmask ents
	}

typedef tilemeta tileset[128]

struct tilemeta {
bool ladder : 1
bool solid : 1
bool liquid : 1
bool conductive : 1
bool burns : 1
bool hypotherm : 1
bool sharp : 1
bool entropy : 1

bool shiney : 1
bool slip : 1
signed speed : 2

bool freezes : 1
bool melts : 1
bool petrif : 1

bool dig : 1
bool fence : 1

intptr_t freeze : 8
intptr_t melt : 8
intptr_t stone : 8
unsigned density

bool blink : 1
unsigned color : 6

char16_t unichar : 16
}
/* tiles can be effected by stuff happening around them.
 *
 * if a tile is flammable, a fire is summoned when fire magic
 * enters the space or 1d6 chance if there is fire within 1 taxicab of it.
 *
 * if a tile is conductive, then electricity is summoned for the instant
 * that electrical magic strikes it, and propagates through contiguous tiles.
 *
 * if a tile can freeze, it's _8BITPTR is changed to the number indicated by ice.
 * when ice magic intersects it.
 *
 * if a tile can melt, it's _8bitPtr is changed to the number indicated by melt
 * when fire or electrical magic intersect it.
 *
 * if a tile can be petrified, it is changed to the tile indicated by stone.
 *
 * if a tile can be dug, using a ↧digging tool on it will remove it
 * digging something triggers updates which cause gravity to affect gases (!liquid,!solid),
 * liquids(+liquid,!solid), and granulars(+liquid,+solid), wherin less dense
 * tiles will swap with more dense ones. this effect travels outwards, to the edge of the room,
 * but will not be applied to the border tiles. in the default set, water has a density of 10, snow
 * has a density of -1, and air has a density of -100. 
 */

mapobjflags:
bool hidden : 1
bool moves : 1
bool rclass : 1
unsigned class : 4
unsigned alignment : 9

struct mapobjtyp:
(self) *prev
(self) *next
eventdata eventident
ucoord3 pos
objid type
void* data
mapobjflags flags

struct signtyp {
char16_t unichar
conlangtyp lang
char* lines
char* gibber
}

struct chestyp:
heldobjtyp *bag_ptr
cursetyp curse
locktype locked

struct doortyp {
bool open : 1
unsigned hp : 7
locktype lock : 8

struct locktype {
unsigned level : 4;
bool locked : 1;
unsigned pins : 7;
trapflag flags;
}
/* lockpicking requires the player to enter
 * 0 and + in the correct order to turn the
 * tumblers. in addition to making the correct
 * guess, one must make a skill check:
 * 1 in 2^(lock.level - (skill/2)) chance
 *
 * lockpicking will play an ascending chromatic
 * scale on a loop, starting on C3 and ending
 * at G3, on synthbass (triangle wave)
 */

struct encontyp {
(self) *prev
(self) *next
eventdata eventident
uchar tobeat	//of 10D20
spawntyp spawn

struct miscitembasetyp:
bool key : 1
bool pick : 1
bool dig : 1
bool music : 1
bool light : 1
bool book : 1
bool spark : 1
bool quest : 1
bool fireproof : 1
bool waterproof : 1
bool elecproof : 1
bool iceproof : 1
bool stoneproof : 1
bool arrow : 1
bool poisoned : 1
bool unbreak : 1
unsigned uses : 8
intptr_t metadata : 8

struct eventdata {
unsigned identnumber : 16
bool uses_race : 1
bool uses_role : 1
bool uses_class : 1
unsigned race : 5
unsigned element : 8
unsigned role : 2
unsigned class : 3
unsigned lde : 3
unsigned chapter : 7
unsigned align : 9
}

struct eventdatastack_ele {	//list of events
(self)* prev
(self)* next
eventdata data
char * heylisten
eventdatastack_garbage * head
eventdatastack_garbage * tail
}

struct eventdatastack_garbage {
(self) * next
(self) * prev
objid type
void * data
}

enum eventdatastack_objid = {
EDS_ROOMOBJ_FLAG
EDS_QGLOBOBJ_FLAG
EDS_EVENTTYP_FLAG
EDS_QGLOBEV_FLAG
EDS_ENCONTYP_FLAG
EDS_PLACETYP_FLAG
}

struct eventtyp:
(self) *prev
(self) *next
ucoord3 pos
eventdata eventdatavals
unsigned hours : 24
int (*dothis)(void*,void*,void*,void*)
unsigned radius : 7
bool interact : 1
char16_t unichar
struct attrcolortyp attrcolor
unsigned up : 4
unsigned down : 4
unsigned duration : 16
unsigned remduration : 16

struct triggertyp {
triggerenum key : 4
unsigned value : 4
}

struct qglobobj: //queued global object
(self) *prev
(self) *next
eventdata eventident
qglobflags flags
latlontyp latlon
ucoord3 pos
objid type
void* data

struct qglobev: //queued global event
(self) *prev
(self) *next
qglobflags flags
latlontyp latlon
ucoord3 pos
eventdata eventdatavals
unsigned hours : 24
int (*dothis)(void*,void*,void*,void*)
unsigned radius : 7
bool interact : 1
char16_t unichar
struct attrcolortyp attrcolor
unsigned up : 4
unsigned down : 4
unsigned duration : 16
unsigned remduration : 16

struct qglobflags {
struct racetyp race
canforceload : 1
race-specific : 1
role : u2
class : u3
alignment : u9
}

struct traptyp:
char16_t unichar
ushort duration
magictyp element
stattyp stat
cursetyp curse
diceodds odds
trapflags flags
sensetyp sense
short hp
short mp

struct trapflags:
bool fireproof : 1
bool waterproof : 1
bool elecproof : 1
bool iceproof : 1
bool tamperproof : 1
bool stoneproof : 1
bool warded : 1
unsigned attack_alignments : 9
bool multiuse : 1
bool magic : 1	//whether the trap is a mechanism or a rune
unsigned color : 6

struct subwarptyp {
bool perm : 1
bool blink : 1
unsigned color : 6
ucoord3 pos
ucoord3 dest
short duration	//negative are uses, positive are turns
}

struct warptyp:
bool perm : 1
bool blink : 1
unsigned color : 6
latlontyp glob_loc
ucoord3 pos
latlontyp glob_dest
ucoord3 dest
short duration

struct gemstonetyp:
unsigned color : 3
unsigned quality : 2
unsigned cut : 2

struct meattyp:
struct racetyp race
uchar sellby
uchar amount

struct foodtyp:
intptr_t itemid : 8
intptr_t metadata : 8
unsigned sellby : 8
unsigned amount : 8

foodbasetyp:
effectyp effect
diceodds odds
uchar keepsfor	//0 means non-perishable
uchar hp
uchar nutri

enum objid:
WEAPON_FLAG : contains subobjtyp calling baseweaptyp
LEGEND_FLAG : contains subobjtyp calling baseweaptyp
POTION_FLAG : contains potiontyp
READ_FLAG : contains readtyp
FOOD_FLAG : contains subobjtyp containing foodtyp
MEAT_FLAG : contains subobjtyp containing meattyp
ARMOR_FLAG : contains subobjtyp calling basearmortyp
SHLD_FLAG : contains subobjtyp calling baseshldtyp
BAUB_FLAG : contains subobjtyp calling baubtyp
CONLANG_FLAG : contains conlangtyp
SPELL_FLAG : contains spelltyp
MISC_FLAG : contains _8bitPtr
GEM_FLAG : contains gemstonetyp
TRAP_FLAG : contains traptyp
WARP_FLAG : contains warptyp
SUBWARP_FLAG : contains subwarptyp
CHEST_FLAG : contains chestyp
DOOR_FLAG : contains doortyp
LOCK_FLAG : contains locktyp (gates are this)
MONEY_FLAG : contains float
SPAWN_FLAG : contains spawntyp
SIGN_FLAG : contains signtyp

#endif
