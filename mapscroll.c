#error this code was based on a pre-prealpha version of the engine's core, and has several issues, including severe rot. until they are fixed, it has been salted.
//another function with an entire header to itself? goshdangit!

struct mapscrollargs {
schar latmove : 2
schar lonmove : 2
schar depmove : 2
bool stair : 1
bool home : 1
}

/*implicit*/mapscroll(args)
mapscrollargs args
{
ulong cullrooms
ulong loadrooms
switch args.latmove : {
	case 0 : break;
	case 1 : cullrooms ← SOUTH_ROOMS_MASK; loadrooms ← NORTH_ROOMS_MASK; break;
	default : cullrooms ← NORTH_ROOMS_MASK; loadrooms ← SOUTH_ROOMS_MASK; break;
	}
switch args.lonmove : {
	case 0 : break;
	case 1 : cullrooms ← WEST_ROOMS_MASK; loadrooms ← EAST_ROOMS_MASK; break;
	default : cullrooms ← EAST_ROOMS_MASK; loadrooms ← WEST_ROOMS_MASK; break;
	}
switch args.depmove : {
	case 0 : break;
	case 1 : cullrooms ← DOWN_ROOMS_MASK; loadrooms ← UP_ROOMS_MASK; break;
	default : cullrooms ← UP_ROOMS_MASK; loadrooms ← DOWN_ROOMS_MASK; break;
	}
if (cullrooms & ROOM_UP_NW_MASKBIT)	{savefreeroom(ROOM_UP_NW)}
if (cullrooms & ROOM_UP_NORTH_MASKBIT)	{savefreeroom(ROOM_UP_NORTH)}
if (cullrooms & ROOM_UP_NE_MASKBIT)	{savefreeroom(ROOM_UP_NE)} 
if (cullrooms & ROOM_UP_WEST_MASKBIT)	{savefreeroom(ROOM_UP_WEST)}
if (cullrooms & ROOM_UP_MASKBIT)	{savefreeroom(ROOM_UP)}
if (cullrooms & ROOM_UP_EAST_MASKBIT)	{savefreeroom(ROOM_UP_EAST)}
if (cullrooms & ROOM_UP_SW_MASKBIT)	{savefreeroom(ROOM_UP_SW)}
if (cullrooms & ROOM_UP_SOUTH_MASKBIT)	{savefreeroom(ROOM_UP_SOUTH)}
if (cullrooms & ROOM_UP_SE_MASKBIT)	{savefreeroom(ROOM_UP_SE)}
if (cullrooms & ROOM_NW_MASKBIT)	{savefreeroom(ROOM_NW)}
if (cullrooms & ROOM_NORTH_MASKBIT)	{savefreeroom(ROOM_NORTH)}
if (cullrooms & ROOM_NE_MASKBIT)	{savefreeroom(ROOM_NE)} 
if (cullrooms & ROOM_WEST_MASKBIT)	{savefreeroom(ROOM_WEST)}
if (cullrooms & ROOM_EAST_MASKBIT)	{savefreeroom(ROOM_EAST)}
if (cullrooms & ROOM_SW_MASKBIT)	{savefreeroom(ROOM_SW)}
if (cullrooms & ROOM_SOUTH_MASKBIT)	{savefreeroom(ROOM_SOUTH)}
if (cullrooms & ROOM_SE_MASKBIT)	{savefreeroom(ROOM_SE)}
if (cullrooms & ROOM_DOWN_NW_MASKBIT)	{savefreeroom(ROOM_DOWN_NW)}
if (cullrooms & ROOM_DOWN_NORTH_MASKBIT)	{savefreeroom(ROOM_DOWN_NORTH)}
if (cullrooms & ROOM_DOWN_NE_MASKBIT)	{savefreeroom(ROOM_DOWN_NE)} 
if (cullrooms & ROOM_DOWN_WEST_MASKBIT)	{savefreeroom(ROOM_DOWN_WEST)}
if (cullrooms & ROOM_DOWN_MASKBIT)	{savefreeroom(ROOM_DOWN)}
if (cullrooms & ROOM_DOWN_EAST_MASKBIT)	{savefreeroom(ROOM_DOWN_EAST)}
if (cullrooms & ROOM_DOWN_SW_MASKBIT)	{savefreeroom(ROOM_DOWN_SW)}
if (cullrooms & ROOM_DOWN_SOUTH_MASKBIT)	{savefreeroom(ROOM_DOWN_SOUTH)}
if (cullrooms & ROOM_DOWN_SE_MASKBIT)	{savefreeroom(ROOM_DOWN_SE)}

switch args.latmove : {
	case 0 : {
		switch args.lonmove : {
			case 0 : {
				switch args.depmove : {
					case 0 : {
						return 1;
						}
					case 1 : {
						ROOM_DOWN_NW = ROOM_NW
						ROOM_DOWN_NORTH = ROOM_NORTH
						ROOM_DOWN_NE = ROOM_NE
						ROOM_DOWN_WEST = ROOM_WEST
						ROOM_DOWN = ROOM
						ROOM_DOWN_EAST = ROOM_EAST
						ROOM_DOWN_SW = ROOM_SW
						ROOM_DOWN_SOUTH = ROOM_SOUTH
						ROOM_DOWN_SE = ROOM_SE

						ROOM_NW = ROOM_UP_NW
						ROOM_NORTH = ROOM_UP_NORTH
						ROOM_NE = ROOM_UP_NE
						ROOM_WEST = ROOM_UP_WEST
						ROOM = ROOM_UP
						ROOM_EAST = ROOM_UP_EAST
						ROOM_SW = ROOM_UP_SW
						ROOM_SOUTH = ROOM_UP_SOUTH
						ROOM_SE = ROOM_UP_SE

						UPDATEWORLDCOORD
						break
						}
					default : {
						ROOM_UP_NW = ROOM_NW
						ROOM_UP_NORTH = ROOM_NORTH
						ROOM_UP_NE = ROOM_NE
						ROOM_UP_WEST = ROOM_WEST
						ROOM_UP = ROOM
						ROOM_UP_EAST = ROOM_EAST
						ROOM_UP_SW = ROOM_SW
						ROOM_UP_SOUTH = ROOM_SOUTH
						ROOM_UP_SE = ROOM_SE

						ROOM_NW = ROOM_DOWN_NW
						ROOM_NORTH = ROOM_DOWN_NORTH
						ROOM_NE = ROOM_DOWN_NE
						ROOM_WEST = ROOM_DOWN_WEST
						ROOM = ROOM_DOWN
						ROOM_EAST = ROOM_DOWN_EAST
						ROOM_SW = ROOM_DOWN_SW
						ROOM_SOUTH = ROOM_DOWN_SOUTH
						ROOM_SE = ROOM_DOWN_SE

						UPDATEWORLDCOORD
						break
						}
					}
				}
			case 1 : {
				switch args.depmove : {
					case 0 : {
						ROOM_UP_NORTH = ROOM_UP_NE
						ROOM_UP = ROOM_UP_EAST
						ROOM_UP_SOUTH = ROOM_UP_SE
						ROOM_NORTH = ROOM_NE
						ROOM = ROOM_EAST
						ROOM_SOUTH = ROOM_SE
						ROOM_DOWN_NORTH = ROOM_DOWN_NE
						ROOM_DOWN = ROOM_DOWN_EAST
						ROOM_DOWN_SOUTH = ROOM_DOWN_SE

						ROOM_UP_NW = ROOM_UP_NORTH
						ROOM_UP_WEST = ROOM_UP
						ROOM_UP_SW = ROOM_UP_SOUTH
						ROOM_NW = ROOM_NORTH
						ROOM_WEST = ROOM
						ROOM_SW = ROOM_SOUTH
						ROOM_DOWN_NW = ROOM_DOWN_NORTH
						ROOM_DOWN_WEST = ROOM_DOWN
						ROOM_DOWN_SW = ROOM_DOWN_SOUTH

						UPDATEWORLDCOORD
						break
						}
					case 1 : {
						ROOM_DOWN_NW = ROOM_NORTH
						ROOM_DOWN_NORTH = ROOM_NE
						ROOM_DOWN_WEST = ROOM
						ROOM_DOWN = ROOM_EAST
						ROOM_DOWN_SW = ROOM_SOUTH
						ROOM_DOWN_SOUTH = ROOM_SE
						
						ROOM_NW = ROOM_UP_NORTH
						ROOM_NORTH = ROOM_UP_NE
						ROOM_WEST = ROOM_UP
						ROOM = ROOM_UP_EAST
						ROOM_SW = ROOM_UP_SOUTH
						ROOM_SOUTH = ROOM_UP_SE
						
						UPDATEWORLDCOORD
						break
						}
					default : {
						ROOM_UP_NW = ROOM_NORTH
						ROOM_UP_NORTH = ROOM_NE
						ROOM_UP_WEST = ROOM
						ROOM_UP = ROOM_EAST
						ROOM_UP_SW = ROOM_SOUTH
						ROOM_UP_SOUTH = ROOM_SE
						
						ROOM_NW = ROOM_DOWN_NORTH
						ROOM_NORTH = ROOM_DOWN_NE
						ROOM_WEST = ROOM_DOWN
						ROOM = ROOM_DOWN_EAST
						ROOM_SW = ROOM_DOWN_SOUTH
						ROOM_SOUTH = ROOM_DOWN_SE
						
						UPDATEWORLDCOORD
						break
						}
					}
				}
			default : {
				switch args.depmove : {
					case 0 : {
						ROOM_UP_NORTH = ROOM_UP_NW
						ROOM_UP = ROOM_UP_WEST
						ROOM_UP_SOUTH = ROOM_UP_SW
						ROOM_NORTH = ROOM_NW
						ROOM = ROOM_WEST
						ROOM_SOUTH = ROOM_SW
						ROOM_DOWN_NORTH = ROOM_DOWN_NW
						ROOM_DOWN = ROOM_DOWN_WEST
						ROOM_DOWN_SOUTH = ROOM_DOWN_SW

						ROOM_UP_NE = ROOM_UP_NORTH
						ROOM_UP_EAST = ROOM_UP
						ROOM_UP_SE = ROOM_UP_SOUTH
						ROOM_NE = ROOM_NORTH
						ROOM_EAST = ROOM
						ROOM_SE = ROOM_SOUTH
						ROOM_DOWN_NE = ROOM_DOWN_NORTH
						ROOM_DOWN_EAST = ROOM_DOWN
						ROOM_DOWN_SE = ROOM_DOWN_SOUTH

						UPDATEWORLDCOORD
						break
						}
					case 1 : {
						ROOM_DOWN_NE = ROOM_NORTH
						ROOM_DOWN_NORTH = ROOM_NW
						ROOM_DOWN_EAST = ROOM
						ROOM_DOWN = ROOM_WEST
						ROOM_DOWN_SE = ROOM_SOUTH
						ROOM_DOWN_SOUTH = ROOM_SW
						
						ROOM_NE = ROOM_UP_NORTH
						ROOM_NORTH = ROOM_UP_NW
						ROOM_EAST = ROOM_UP
						ROOM = ROOM_UP_WEST
						ROOM_SE = ROOM_UP_SOUTH
						ROOM_SOUTH = ROOM_UP_SW
						
						UPDATEWORLDCOORD
						break
						}
					default : {
						ROOM_UP_NE = ROOM_NORTH
						ROOM_UP_NORTH = ROOM_NW
						ROOM_UP_EAST = ROOM
						ROOM_UP = ROOM_WEST
						ROOM_UP_SE = ROOM_SOUTH
						ROOM_UP_SOUTH = ROOM_SW
						
						ROOM_NE = ROOM_DOWN_NORTH
						ROOM_NORTH = ROOM_DOWN_NW
						ROOM_EAST = ROOM_DOWN
						ROOM = ROOM_DOWN_WEST
						ROOM_SE = ROOM_DOWN_SOUTH
						ROOM_SOUTH = ROOM_DOWN_SW
						
						UPDATEWORLDCOORD
						break
						}
					}
				}
			}
		}
	case 1 : {
		switch args.lonmove : {
			case 0 : {
				switch args.depmove : {
					case 0 : {
						ROOM_UP_SW = ROOM_UP_WEST
						ROOM_UP_SOUTH = ROOM_UP
						ROOM_UP_SE = ROOM_UP_EAST
						ROOM_SW = ROOM_WEST
						ROOM_SOUTH = ROOM
						ROOM_SE = ROOM_EAST
						ROOM_DOWN_SW = ROOM_DOWN_WEST
						ROOM_DOWN_SOUTH = ROOM_DOWN
						ROOM_DOWN_SE = ROON_DOWN_EAST

						ROOM_UP_WEST = ROOM_UP_NW
						ROOM_UP = ROOM_UP_NORTH
						ROOM_UP_EAST = ROOM_UP_NE
						ROOM_WEST = ROOM_NW
						ROOM = ROOM_NORTH
						ROOM_EAST = ROOM_NE
						ROOM_DOWN_WEST = ROOM_DOWN_NW
						ROOM_DOWN = ROOM_DOWN_NORTH
						ROON_DOWN_EAST = ROOM_DOWN_NE

						UPDATEWORLDCOORD
						break
						}
					case 1 : {
						ROOM_DOWN_WEST = ROOM_NW
						ROOM_DOWN = ROOM_NORTH
						ROOM_DOWN_EAST = ROOM_NE
						ROOM_DOWN_SW = ROOM_WEST
						ROOM_DOWN_SOUTH = ROOM
						ROOM_DOWN_SE = ROOM_EAST

						ROOM_WEST = ROOM_UP_NW
						ROOM = ROOM_UP_NORTH
						ROOM_EAST = ROOM_UP_NE
						ROOM_SW = ROOM_UP_WEST
						ROOM_SOUTH = ROOM_UP
						ROOM_SE = ROOM_UP_EAST

						UPDATEWORLDCOORD
						break
						}
					default : {
						ROOM_UP_WEST = ROOM_NW
						ROOM_UP = ROOM_NORTH
						ROOM_UP_EAST = ROOM_NE
						ROOM_UP_SW = ROOM_WEST
						ROOM_UP_SOUTH = ROOM
						ROOM_UP_SE = ROOM_EAST

						ROOM_WEST = ROOM_DOWN_NW
						ROOM = ROOM_DOWN_NORTH
						ROOM_EAST = ROOM_DOWN_NE
						ROOM_SW = ROOM_DOWN_WEST
						ROOM_SOUTH = ROOM_DOWN
						ROOM_SE = ROOM_DOWN_EAST

						UPDATEWORLDCOORD
						break
						}
					}
				}
			//this is meditative!
			case 1 : {
				switch args.depmove : {
					case 0 : {
						ROOM_UP_WEST = ROOM_UP_NORTH
						ROOM_UP_SW = ROOM_UP
						ROOM_UP_SOUTH = ROOM_UP_EAST
						ROOM_WEST = ROOM_NORTH
						ROOM_SW = ROOM
						ROOM_SOUTH = ROOM_EAST
						ROOM_DOWN_WEST = ROOM_DOWN_NORTH
						ROOM_DOWN_SW = ROOM_DOWN
						ROOM_DOWN_SOUTH = ROOM_DOWN_EAST

						ROOM_UP = ROOM_UP_NE
						ROOM = ROOM_NE
						ROOM_DOWN = ROOM_DOWN_NE

						UPDATEWORLDCOORD
						break
						}
					case 1 : {
						ROOM_WEST = ROOM_UP_NORTH
						ROOM_SW = ROOM_UP
						ROOM_SOUTH = ROOM_UP_EAST
						ROOM_DOWN_WEST = ROOM_NORTH
						ROOM_DOWN = ROOM_NE
						ROOM_DOWN_SW = ROOM
						ROOM_DOWN_SOUTH = ROOM_EAST

						ROOM = ROOM_UP_NE

						UPDATEWORLDCOORD
						break
						}
					default : {
						ROOM_WEST = ROOM_DOWN_NORTH
						ROOM_SW = ROOM_DOWN
						ROOM_SOUTH = ROOM_DOWN_EAST
						ROOM_UP_WEST = ROOM_NORTH
						ROOM_UP = ROOM_NE
						ROOM_UP_SW = ROOM
						ROOM_UP_SOUTH = ROOM_EAST

						ROOM = ROOM_DOWN_NE

						UPDATEWORLDCOORD
						break
						}
					}
				}
			default : {
				switch args.depmove : {
					case 0 : {
						ROOM_UP_EAST = ROOM_UP_NORTH
						ROOM_UP_SE = ROOM_UP
						ROOM_UP_SOUTH = ROOM_UP_WEST
						ROOM_EAST = ROOM_NORTH
						ROOM_SE = ROOM
						ROOM_SOUTH = ROOM_WEST
						ROOM_DOWN_EAST = ROOM_DOWN_NORTH
						ROOM_DOWN_SE = ROOM_DOWN
						ROOM_DOWN_SOUTH = ROOM_DOWN_WEST

						ROOM_UP = ROOM_UP_NW
						ROOM = ROOM_NW
						ROOM_DOWN = ROOM_DOWN_NW

						UPDATEWORLDCOORD
						break
						}
					case 1 : {
						ROOM_EAST = ROOM_UP_NORTH
						ROOM_SE = ROOM_UP
						ROOM_SOUTH = ROOM_UP_WEST
						ROOM_DOWN_EAST = ROOM_NORTH
						ROOM_DOWN = ROOM_NW
						ROOM_DOWN_SE = ROOM
						ROOM_DOWN_SOUTH = ROOM_WEST

						ROOM = ROOM_UP_NW

						UPDATEWORLDCOORD
						break
						}
					default : {
						ROOM_EAST = ROOM_DOWN_NORTH
						ROOM_SE = ROOM_DOWN
						ROOM_SOUTH = ROOM_DOWN_WEST
						ROOM_UP_EAST = ROOM_NORTH
						ROOM_UP = ROOM_NW
						ROOM_UP_SE = ROOM
						ROOM_UP_SOUTH = ROOM_WEST

						ROOM = ROOM_DOWN_NW

						UPDATEWORLDCOORD
						break
						}
					}
				}
			}
		}
	default : {
		switch args.lonmove : {
			case 0 : {
				switch args.depmove : {
					case 0 : {
						ROOM_UP_NW = ROOM_UP_WEST
						ROOM_UP_NORTH = ROOM_UP
						ROOM_UP_NE = ROOM_UP_EAST
						ROOM_NW = ROOM_WEST
						ROOM_NORTH = ROOM
						ROOM_NE = ROOM_EAST
						ROOM_DOWN_NW = ROOM_DOWN_WEST
						ROOM_DOWN_NORTH = ROOM_DOWN
						ROOM_DOWN_NE = ROON_DOWN_EAST

						ROOM_UP_WEST = ROOM_UP_SW
						ROOM_UP = ROOM_UP_SOUTH
						ROOM_UP_EAST = ROOM_UP_SE
						ROOM_WEST = ROOM_SW
						ROOM = ROOM_SOUTH
						ROOM_EAST = ROOM_SE
						ROOM_DOWN_WEST = ROOM_DOWN_SW
						ROOM_DOWN = ROOM_DOWN_SOUTH
						ROON_DOWN_EAST = ROOM_DOWN_SE

						UPDATEWORLDCOORD
						break
						}
					case 1 : {
						ROOM_DOWN_WEST = ROOM_SW
						ROOM_DOWN = ROOM_SOUTH
						ROOM_DOWN_EAST = ROOM_SE
						ROOM_DOWN_NW = ROOM_WEST
						ROOM_DOWN_NORTH = ROOM
						ROOM_DOWN_NE = ROOM_EAST

						ROOM_WEST = ROOM_UP_SW
						ROOM = ROOM_UP_SOUTH
						ROOM_EAST = ROOM_UP_SE
						ROOM_NW = ROOM_UP_WEST
						ROOM_NORTH = ROOM_UP
						ROOM_NE = ROOM_UP_EAST

						UPDATEWORLDCOORD
						break
						}
					default : {
						ROOM_UP_WEST = ROOM_SW
						ROOM_UP = ROOM_SOUTH
						ROOM_UP_EAST = ROOM_SE
						ROOM_UP_NW = ROOM_WEST
						ROOM_UP_NORTH = ROOM
						ROOM_UP_NE = ROOM_EAST

						ROOM_WEST = ROOM_DOWN_SW
						ROOM = ROOM_DOWN_SOUTH
						ROOM_EAST = ROOM_DOWN_SE
						ROOM_NW = ROOM_DOWN_WEST
						ROOM_NORTH = ROOM_DOWN
						ROOM_NE = ROOM_DOWN_EAST

						UPDATEWORLDCOORD
						break
						}
					}
				}
			case 1 : {
				switch args.depmove : {
					case 0 : {
						ROOM_UP_WEST = ROOM_UP_SOUTH
						ROOM_UP_NW = ROOM_UP
						ROOM_UP_NORTH = ROOM_UP_EAST
						ROOM_WEST = ROOM_SOUTH
						ROOM_NW = ROOM
						ROOM_NORTH = ROOM_EAST
						ROOM_DOWN_WEST = ROOM_DOWN_SOUTH
						ROOM_DOWN_NW = ROOM_DOWN
						ROOM_DOWN_NORTH = ROOM_DOWN_EAST

						ROOM_UP = ROOM_UP_SE
						ROOM = ROOM_SE
						ROOM_DOWN = ROOM_DOWN_SE

						UPDATEWORLDCOORD
						break
						}
					case 1 : {
						ROOM_WEST = ROOM_UP_SOUTH
						ROOM_NW = ROOM_UP
						ROOM_NORTH = ROOM_UP_EAST
						ROOM_DOWN_WEST = ROOM_SOUTH
						ROOM_DOWN = ROOM_SE
						ROOM_DOWN_NW = ROOM
						ROOM_DOWN_NORTH = ROOM_EAST

						ROOM = ROOM_UP_SE

						UPDATEWORLDCOORD
						break
						}
					default : {
						ROOM_WEST = ROOM_DOWN_SOUTH
						ROOM_NW = ROOM_DOWN
						ROOM_NORTH = ROOM_DOWN_EAST
						ROOM_UP_WEST = ROOM_SOUTH
						ROOM_UP = ROOM_SE
						ROOM_UP_NW = ROOM
						ROOM_UP_NORTH = ROOM_EAST

						ROOM = ROOM_DOWN_SE

						UPDATEWORLDCOORD
						break
						}
					}
				}
			default : {
				switch args.depmove : {
					case 0 : {
						ROOM_UP_EAST = ROOM_UP_SOUTH
						ROOM_UP_NE = ROOM_UP
						ROOM_UP_NORTH = ROOM_UP_WEST
						ROOM_EAST = ROOM_SOUTH
						ROOM_NE = ROOM
						ROOM_NORTH = ROOM_WEST
						ROOM_DOWN_EAST = ROOM_DOWN_SOUTH
						ROOM_DOWN_NE = ROOM_DOWN
						ROOM_DOWN_NORTH = ROOM_DOWN_WEST

						ROOM_UP = ROOM_UP_SW
						ROOM = ROOM_SW
						ROOM_DOWN = ROOM_DOWN_SW

						UPDATEWORLDCOORD
						break
						}
					case 1 : {
						ROOM_EAST = ROOM_UP_SOUTH
						ROOM_NE = ROOM_UP
						ROOM_NORTH = ROOM_UP_WEST
						ROOM_DOWN_EAST = ROOM_SOUTH
						ROOM_DOWN = ROOM_SW
						ROOM_DOWN_NE = ROOM
						ROOM_DOWN_NORTH = ROOM_WEST

						ROOM = ROOM_UP_SW

						UPDATEWORLDCOORD
						break
						}
					default : {
						ROOM_EAST = ROOM_DOWN_SOUTH
						ROOM_NE = ROOM_DOWN
						ROOM_NORTH = ROOM_DOWN_WEST
						ROOM_UP_EAST = ROOM_SOUTH
						ROOM_UP = ROOM_SW
						ROOM_UP_NE = ROOM
						ROOM_UP_NORTH = ROOM_WEST

						ROOM = ROOM_DOWN_SW

						UPDATEWORLDCOORD
						break
						}
					}
				}
			}
		}
	}

if (loadrooms & ROOM_UP_NW_MASKBIT)	{ROOM_UP_NW = loadroom(1,-1,1)}
if (loadrooms & ROOM_UP_NORTH_MASKBIT)	{ROOM_UP_NORTH = loadroom(1,0,1)}
if (loadrooms & ROOM_UP_NE_MASKBIT)	{ROOM_UP_NE = loadroom(1,1,1)} 
if (loadrooms & ROOM_UP_WEST_MASKBIT)	{ROOM_UP_WEST = loadroom(0,-1,1)}
if (loadrooms & ROOM_UP_MASKBIT)	{ROOM_UP = loadroom(0,0,1)}
if (loadrooms & ROOM_UP_EAST_MASKBIT)	{ROOM_UP_EAST = loadroom(0,-1,1)}
if (loadrooms & ROOM_UP_SW_MASKBIT)	{ROOM_UP_SW = loadroom(-1,-1,1)}
if (loadrooms & ROOM_UP_SOUTH_MASKBIT)	{ROOM_UP_SOUTH = loadroom(-1,0,1)}
if (loadrooms & ROOM_UP_SE_MASKBIT)	{ROOM_UP_SE = loadroom(-1,1,1)}
if (loadrooms & ROOM_NW_MASKBIT)	{ROOM_NW = loadroom(1,-1,0)}
if (loadrooms & ROOM_NORTH_MASKBIT)	{ROOM_NORTH = loadroom(1,0,0)}
if (loadrooms & ROOM_NE_MASKBIT)	{ROOM_NE = loadroom(1,1,0)} 
if (loadrooms & ROOM_WEST_MASKBIT)	{ROOM_WEST = loadroom(0,-1,0)}
if (loadrooms & ROOM_EAST_MASKBIT)	{ROOM_EAST = loadroom(0,1,0)}
if (loadrooms & ROOM_SW_MASKBIT)	{ROOM_SW = loadroom(-1,-1,0)}
if (loadrooms & ROOM_SOUTH_MASKBIT)	{ROOM_SOUTH = loadroom(-1,0,0)}
if (loadrooms & ROOM_SE_MASKBIT)	{ROOM_SE = loadroom(-1,1,0)}
if (loadrooms & ROOM_DOWN_NW_MASKBIT)	{ROOM_DOWN_NW = loadroom(1,-1,-1)}
if (loadrooms & ROOM_DOWN_NORTH_MASKBIT)	{ROOM_DOWN_NORTH = loadroom(1,0,-1)}
if (loadrooms & ROOM_DOWN_NE_MASKBIT)	{ROOM_DOWN_NE = loadroom(1,1,-1)} 
if (loadrooms & ROOM_DOWN_WEST_MASKBIT)	{ROOM_DOWN_WEST = loadroom(0,-1,-1)}
if (loadrooms & ROOM_DOWN_MASKBIT)	{ROOM_DOWN = loadroom(0,0,-1)}
if (loadrooms & ROOM_DOWN_EAST_MASKBIT)	{ROOM_DOWN_EAST = loadroom(0,1,-1)}
if (loadrooms & ROOM_DOWN_SW_MASKBIT)	{ROOM_DOWN_SW = loadroom(-1,-1,-1)}
if (loadrooms & ROOM_DOWN_SOUTH_MASKBIT)	{ROOM_DOWN_SOUTH = loadroom(-1,0,-1)}
if (loadrooms & ROOM_DOWN_SE_MASKBIT)	{ROOM_DOWN_SE = loadroom(-1,1,-1)}

GLOBREG.NEW = true
GLOBREG.FIRST = !(ROOM→visited)
ROOM→visited = true
}

if (depmove ≥ 0) : {
	if (home) {
		PLAYER.pos.x = ROOM.home.x
		PLAYER.pos.y = ROOM.home.y
	else if (stair) {
		PLAYER.pos.x = ROOM.downstair.x
		PLAYER.pos.y = ROOM.downstair.y
		}
	PLAYER.pos.z = 0
	}
else {
	if (home) {
		PLAYER.pos.x = ROOM.home.x
		PLAYER.pos.y = ROOM.home.y
	else if (stair) {
		PLAYER.pos.x = ROOM.upstair.x
		PLAYER.pos.y = ROOM.upstair.y
		}
	PLAYER.pos.z = CEILING
	}

GLOBREG.NEW = true
GLOBREG.FIRST = !(ROOM→visited)
ROOM→visited = true
}