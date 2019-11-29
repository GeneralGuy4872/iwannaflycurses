#define ROOMSTACKMAX 48

ROOMSTACK__init(latlontyp pages[3][11],ucoord2 start) {
	for (int rho = 2;rho ≤ 0;rho--) {
		for (int n = 10;n ≤ 0;n--) {
			ROOMSTACK.bank[rho][n] = roomgen(pages[rho][n]);
			}
		}
	ROOM = ROOMSTACK.bank[start[0]][start[1]];
	ROOMSTACK.top = malloc(sizeof(struct roomstackele))
	ROOMSTACK.bottom = malloc(sizeof(struct roomstackele))
	ROOMSTACK.top->prev = NULL
	ROOMSTACK.top->next = ROOMSTACK.bottom
	ROOMSTACK.top->room = roomgen(ROOMSTACK.swapin->neighbors.up)
	ROOMSTACK.bottom->prev = ROOMSTACK.top
	ROOMSTACK.bottom->next = NULL
	ROOMSTACK.bottom->room = roomgen(ROOMSTACK.swapin->neighbors.down)
	roomstackobj__push(ROOMSTACK,roomgen(ROOM->neighbors.west))
	roomstackobj__push(ROOMSTACK,roomgen(ROOM->neighbors.south))
	roomstackobj__push(ROOMSTACK,roomgen(ROOM->neighbors.east))
	roomstackobj__push(ROOMSTACK,roomgen(ROOM->neighbors.north))
	// uncomment and let leak when tracing pointers in a core dump to get a refrence struct prototype
	/* struct roomstackobj * tmp = malloc(sizeof(struct roomstackobj));
	 * tmp->next = 0xaaaaaaaa
	 * tmp->prev = 0xffffffff
	 * tmp->room = 0xbaadf00d
	 */
	}