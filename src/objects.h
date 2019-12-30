#ifndef IWANNAFLY_OBJECTS_H_REENTERANT
#define IWANNAFLY_OBJECTS_H_REENTERANT 1

struct roomstackele {
struct roomstackele * prev;
struct roomstackele * next;
roomtyp * room;
}

struct roomstackobj {
roomtyp * swapin;
roomtyp *neighbor[2][6];	//first row are the pointers to the swapped in neighboring rooms. second row is for storing neighbor rooms that are not from the stack and will not be put there.
roomtyp *bank[3][11];
struct roomstackele * top;
struct roomstackele * bottom;
ushort depth;
}

extern roomstackele * roomstackobj__pushover(roomstackobj * this,roomtyp * room);
#define ROOMSTACK__pushover(R) roomstackobj(ROOMSTACK,R)

extern void roomstackobj__trim(roomstackobj * this);
#define ROOMSTACK__trim() roomstackobj__trim(ROOMSTACK)

extern roomstackele * roomstackobj__push(roomstackobj * this,roomtyp * room);
#define ROOMSTACK__push(R) roomstackobj__push(ROOMSTACK,R)

#define roomstackobj__roompull(X,Y) roomstackobj__pull(X,roomstackobj__roomp(X,Y))
#define ROOMSTACK__roompull(Y) roomstackobj__roompull(ROOMSTACK,Y)

extern roomstackele * roomstackobj__pull (roomstackobj * this, roomstackele * that);
#define ROOMSTACK__pull(X) roomstackobj__pull(ROOMSTACK,X)

extern roomstackobj__setswap (roomstackobj * this, roomtyp * that);
#define ROOMSTACK__setswap(X) roomstackobj__setswap(ROOMSTACK,X)

#define roomstackobj__setswap_ele(X,Y) roomstackobj__setswap(X,roomstackobj__drop(X,Y))
#define ROOMSTACK__setswap_ele(Y) roomstackobj__setswap_ele(ROOMSTACK,Y)

extern roomstackobj__makecurrent(roomstackobj * this,latlontyp query);
#define ROOMSTACK__makecurrent(Q) roomstackobj__makecurrent(ROOMSTACK,Q)

extern roomstackobj__scroll(roomstackobj * this,playertyp * you,char dir);
#define ROOMSCROLL(D) roomstackobj__scroll(ROOMSTACK,PLAYER,D)

extern roomstackobj__neighbor_reset (struct roomstack * this);
#define ROOMSTACK__neighbor_reset() roomstackobj__neighbor_reset(ROOMSTACK)

extern smrtloadroom (struct latlontyp query);

extern struct planetyp getplanetyp (struct latlontyp input);

#endif
