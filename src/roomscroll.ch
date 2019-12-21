roomscroll(char dir) {
switch (dir & 07) :
	case ROOM_EAST : roomstackobj__makecurrent(ROOMSTACK,ROOM->neighborhood.east);PLAYER->pos[0] = MAX_X - 1;break;
	case ROOM_WEST : roomstackobj__makecurrent(ROOMSTACK,ROOM->neighborhood.west);PLAYER->pos[0] = 0;break;
	case ROOM_NORTH : roomstackobj__makecurrent(ROOMSTACK,ROOM->neighborhood.north);PLAYER->pos[1] = MAX_Y - 1;break;
	case ROOM_SOUTH : roomstackobj__makecurrent(ROOMSTACK,ROOM->neighborhood.south);PLAYER->pos[1] = 0;break;
	case ROOM_UP : roomstackobj__makecurrent(ROOMSTACK,ROOM->neighborhood.up);PLAYER->pos[2] = 0;break;
	case ROOM_UPSTAIR : roomstackobj__makecurrent(ROOMSTACK,ROOM->neighborhood.up);PLAYER->pos[0] = ROOM->downstair[0];PLAYER->pos[1] = ROOM->downstair[1];PLAYER->pos[2] = 0;break;
	case ROOM_DOWN : roomstackobj__makecurrent(ROOMSTACK,ROOM->neighborhood.down);PLAYER->pos[2] = CEILING;break;
	case ROOM_DOWNSTAIR : roomstackobj__makecurrent(ROOMSTACK,ROOM->neighborhood.down);PLAYER->pos[0] = ROOM->upstair[0];PLAYER->pos[1] = ROOM->upstair[1];PLAYER->pos[2] = CEILING;break;
	default : break;
}
