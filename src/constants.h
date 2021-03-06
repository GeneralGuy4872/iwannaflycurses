#define NIL ""

#ifndef OK
#define OK 0
#endif

#ifndef ERR
#define ERR -1
#endif

#define GRAV 3.2174	/*if you backtrack this to determine the size of a grid unit, you're trying to hard
#define MAX_X 64
#define MAX_Y 24	//MAX_X ≥ MAX_Y ≥ MAX_Z
#define MAX_Z 16
#define EQUATOR 360	//the number of rooms in the circumfrence of the sphere

#define GOOD_MASK 0700
#define LAWFUL_MASK 0444
#define EVIL_MASK 0007
#define CHAOTIC_MASK 0111

#define NEUT_HORIZ_MASK 0070
#define NEUT_VERT_MASK 0222

#define LAW_GOOD_BIT 0400
#define NEUT_GOOD_BIT 0200
#define CHAOS_GOOD_BIT 0100
#define LAW_NEUT_BIT 0040
#define TRUE_NEUT_BIT 0020
#define CHAOS_NEUT_BIT 0010
#define LAW_EVIL_BIT 0004
#define NEUT_EVIL_BIT 0002
#define CHAOS_EVIL_BIT 0001

#define LAW_GOOD_WIDEMSK 0764
#define CHAOS_GOOD_WIDEMSK 0731
#define LAW_EVIL_WIDEMSK 0467
#define CHAOS_EVIL_WIDEMSK 0137
#define NEUTRAL_WIDEMSK 0272

#define ELE_WATER_BIT 0x80
#define ELE_ICE_BIT 0x40
#define ELE_AIR_BIT 0x20
#define ELE_ELEC_BIT 0x10
#define ELE_FIRE_BIT 0x08
#define ELE_METAL_BIT 0x04
#define ELE_EARTH_BIT 0x02
#define ELE_TREE_BIT 0x01

#define ELE_WATER_WIDEMSK 0xC1
#define ELE_ICE_WIDEMSK 0xE0
#define ELE_AIR_WIDEMSK 0x70
#define ELE_ELEC_WIDEMSK 0x38
#define ELE_FIRE_WIDEMSK 0x1C
#define ELE_METAL_WIDEMSK 0x0C
#define ELE_EARTH_WIDEMSK 0x07
#define ELE_TREE_WIDEMSK 0x83

#define LIGHT_BIT 04
#define DARK_BIT 02
#define ENTROPY_BIT 01

#define GOLDMAX 130999
#define COPPERMAX 99

#define ROOM_STACK_MAX 40

#define ROOM_NORTH 0
#define ROOM_SOUTH 1
#define ROOM_WEST 2
#define ROOM_EAST 3
#define ROOM_DOWN 4
#define ROOM_UP 5
#define ROOM_DOWNSTAIR 6
#define ROOM_UPSTAIR 7

//not implemented
#define GRAV_DOWN 0
#define GRAV_UP 7
#define GRAV_EAST 1
#define GRAV_WEST 6
#define GRAV_NORTH 5
#define GRAV_SOUTH 2
#define GRAV_HOLE 4
#define GRAV_NONE 3

#define CAMERA_DEFAULT 0	//0000
#define CAMERA_UP 2	//?010
#define CAMERA_DOWN 3	//?011
#define CAMERA_LEFT 4	//?100
#define CAMERA_RIGHT 5	//?101
#define CAMERA_PGUP 6	//?110
#define CAMERA_PGDN 7	//?111
#define CAMERA_FLAT 8	//1???
//CAMERA_DEFAULT | CAMERA_FLAT must be corner-case handled to be 0xF instead of invalid value 0x8

#define BUFFER_MAX 512
#define FLOPPYSIZE 1474560
#define DRUMSIZE 16384
#define BGCOLORS 8
#define FGCOLORS 8

#define SQRT3 1.732050807568877293528
