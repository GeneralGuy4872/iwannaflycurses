astar(ortho,params,tile,pointa,pointb,fly,swim)
bool ortho
astarparamtyp params
schar tile
coord3 pointa
coord3 pointb
bool fly
bool swim
{
float best = INFINITY
float winning
datakeeper = makepathdata(pointa.x,pointa.y,pointa.z)

switch params.weightnorm : {
	case 0 : {
		for (uchar z;z < CEILING;z++) {
			for (uchar y;y < MAX_Y;y++) {
				for (uchar x;x < MAX_X;x++) {
					datakeeper.grid[COORDSUB(z,y,x)].goaldist = normINF((coord3){x,y,z},pointb)
					}
				}
			}
		break;
	case 1 : {
		for (uchar z;z < CEILING;z++) {
			for (uchar y;y < MAX_Y;y++) {
				for (uchar x;x < MAX_X;x++) {
					datakeeper.grid[COORDSUB(z,y,x)].goaldist = norm1((coord3){x,y,z},pointb)
					}
				}
			}
		break;
	case 2 : {
		for (uchar z;z < CEILING;z++) {
			for (uchar y;y < MAX_Y;y++) {
				for (uchar x;x < MAX_X;x++) {
					datakeeper.grid[COORDSUB(z,y,x)].goaldist = norm2((coord3){x,y,z},pointb)
					}
				}
			}
		break;
	default : {return -1}

datakeeper.grid[COORDSUB(pointa.z,pointa.y,pointa.x + 1)].runningdist = 0.0

setpathobs(&datakeeper,mode,fly,swim)

setcoord3* current = datakeeper.hydra_ptr
setcoord3* last = datakeeper.hydra_ptr
setcoord3* ptrnext = NULL
float diagonal2
float diagonal3

setcoord3* neighborhood[3][3][3] = {{
{NULL,NULL,NULL}
{NULL,NULL,NULL}
{NULL,NULL,NULL}
},{
{NULL,NULL,NULL}
{NULL,current,NULL}
{NULL,NULL,NULL}
},{
{NULL,NULL,NULL}
{NULL,NULL,NULL}
{NULL,NULL,NULL}
}}

#define RESETNEIGHBORHOOD do {neighborhood[0][0][0] = NULL; neighborhood[0][0][1] = NULL; neighborhood[0][0][2] = NULL; neighborhood[0][1][0] = NULL; neighborhood[0][1][1] = NULL; neighborhood[0][1][2] = NULL; neighborhood[0][2][0] = NULL; neighborhood[0][2][1] = NULL; neighborhood[0][2][2] = NULL; neighborhood[1][0][0] = NULL; neighborhood[1][0][1] = NULL; neighborhood[1][0][2] = NULL; neighborhood[1][1][0] = NULL; neighborhood[1][1][1] = current; neighborhood[1][1][2] = NULL; neighborhood[1][2][0] = NULL; neighborhood[1][2][1] = NULL; neighborhood[1][2][2] = NULL; neighborhood[2][0][0] = NULL; neighborhood[2][0][1] = NULL; neighborhood[2][0][2] = NULL; neighborhood[2][1][0] = NULL; neighborhood[2][1][1] = NULL; neighborhood[2][1][2] = NULL; neighborhood[2][2][0] = NULL; neighborhood[2][2][1] = NULL; neighborhood[2][2][2] = NULL;} while (0)

if (best > (datakeeper.grid[COORDSUB(current→z,current→y,current→x)].runningdist)) {goto(skip)}
if (best > (datakeeper.grid[COORDSUB(current→z,current→y,current→x)].runningdist + 1)) {
	forever {
		if (
			(current→x + 1 < MAX_X) &&
			(!(datakeeper.grid[COORDSUB(current→z,current→y,current→x + 1)].obs)) &&
			(best > (datakeeper.grid[COORDSUB(current→z,current→y,current→x)].runningdist + 1)) && (
				((datakeeper.grid[COORDSUB(current→z,current→y,current→x + 1)].runningdist) > (datakeeper.grid[COORDSUB(current→z,current→y,current→x)].runningdist + 1)) ||
				((datakeeper.grid[COORDSUB(current→z,current→y,current→x + 1)].runningdist) < 0)
				)
			) {
			datakeeper.grid[COORDSUB(current→z,current→y,current→x + 1)].runningdist = datakeeper.grid[COORDSUB(current→z,current→y,current→x)].runningdist + 1
			datakeeper.grid[COORDSUB(current→z,current→y,current→x + 1)].az = 2
			datakeeper.grid[COORDSUB(current→z,current→y,current→x + 1)].up = false
			datakeeper.grid[COORDSUB(current→z,current→y,current→x + 1)].fwd = true
			datakeeper.grid[COORDSUB(current→z,current→y,current→x + 1)].down = false
			setcoord3* tmp = malloc(sizeof(setcoord3))
			tmp→x = current→x + 1
			tmp→y = current→y
			tmp→z = current→z
			tmp→prev = last
			last→next = tmp
			datakeeper.hydra_ptr→prev = tmp
			tmp→next = datakeeper.hydra_ptr
			last = tmp
			neighborhood[1][1][2] = tmp
			}
		if (
			(current→x - 1 ≥ 0) &&
			(!(datakeeper.grid[COORDSUB(current→z,current→y,current→x - 1)].obs)) &&
			(best > (datakeeper.grid[COORDSUB(current→z,current→y,current→x)].runningdist + 1)) && (
				((datakeeper.grid[COORDSUB(current→z,current→y,current→x - 1)].runningdist) > (datakeeper.grid[COORDSUB(current→z,current→y,current→x)].runningdist + 1)) ||
				((datakeeper.grid[COORDSUB(current→z,current→y,current→x - 1)].runningdist) < 0)
				)
			) {
			datakeeper.grid[COORDSUB(current→z,current→y,current→x - 1)].runningdist = datakeeper.grid[COORDSUB(current→z,current→y,current→x)].runningdist + 1
			datakeeper.grid[COORDSUB(current→z,current→y,current→x - 1)].az = 6
			datakeeper.grid[COORDSUB(current→z,current→y,current→x - 1)].up = false
			datakeeper.grid[COORDSUB(current→z,current→y,current→x - 1)].fwd = true
			datakeeper.grid[COORDSUB(current→z,current→y,current→x - 1)].down = false
			setcoord3* tmp = malloc(sizeof(setcoord3))
			tmp→x = current→x - 1
			tmp→y = current→y
			tmp→z = current→z
			tmp→prev = last
			last→next = tmp
			datakeeper.hydra_ptr→prev = tmp
			tmp→next = datakeeper.hydra_ptr
			last = tmp
			neighborhood[1][1][0] = tmp
			}
		if (
			(current→y + 1 < MAX_Y) &&
			(!(datakeeper.grid[COORDSUB(current→z,current→y + 1,current→x)].obs)) &&
			(best > (datakeeper.grid[COORDSUB(current→z,current→y,current→x)].runningdist + 1)) && (
				((datakeeper.grid[COORDSUB(current→z,current→y + 1,current→x)].runningdist) > (datakeeper.grid[COORDSUB(current→z,current→y,current→x)].runningdist + 1)) ||
				((datakeeper.grid[COORDSUB(current→z,current→y + 1,current→x)].runningdist) < 0)
				)
			) {
			datakeeper.grid[COORDSUB(current→z,current→y + 1,current→x)].runningdist = datakeeper.grid[COORDSUB(current→z,current→y,current→x)].runningdist + 1
			datakeeper.grid[COORDSUB(current→z,current→y + 1,current→x)].az = 0
			datakeeper.grid[COORDSUB(current→z,current→y + 1,current→x)].up = false
			datakeeper.grid[COORDSUB(current→z,current→y + 1,current→x)].fwd = true
			datakeeper.grid[COORDSUB(current→z,current→y + 1,current→x)].down = false
			setcoord3* tmp = malloc(sizeof(setcoord3))
			tmp→x = current→x
			tmp→y = current→y + 1
			tmp→z = current→z
			tmp→prev = last
			last→next = tmp
			datakeeper.hydra_ptr→prev = tmp
			tmp→next = datakeeper.hydra_ptr
			last = tmp
			neighborhood[1][2][1] = tmp
			}
		if (
			(current→z - 1 ≥ 0) &&
			(!(datakeeper.grid[COORDSUB(current→z,current→y - 1,current→x)].obs)) &&
			(best > (datakeeper.grid[COORDSUB(current→z,current→y,current→x)].runningdist + 1)) && (
				((datakeeper.grid[COORDSUB(current→z,current→y - 1,current→x)].runningdist) > (datakeeper.grid[COORDSUB(current→z,current→y,current→x)].runningdist + 1)) ||
				((datakeeper.grid[COORDSUB(current→z,current→y - 1,current→x)].runningdist) < 0)
				)
			) {
			datakeeper.grid[COORDSUB(current→z,current→y - 1,current→x)].runningdist = datakeeper.grid[COORDSUB(current→z,current→y,current→x)].runningdist + 1
			datakeeper.grid[COORDSUB(current→z,current→y - 1,current→x)].az = 0
			datakeeper.grid[COORDSUB(current→z,current→y - 1,current→x)].up = false
			datakeeper.grid[COORDSUB(current→z,current→y - 1,current→x)].fwd = true
			datakeeper.grid[COORDSUB(current→z,current→y - 1,current→x)].down = false
			setcoord3* tmp = malloc(sizeof(setcoord3))
			tmp→x = current→x
			tmp→y = current→y - 1
			tmp→z = current→z
			tmp→prev = last
			last→next = tmp
			datakeeper.hydra_ptr→prev = tmp
			tmp→next = datakeeper.hydra_ptr
			last = tmp
			neighborhood[1][0][1] = tmp
			}
		if (
			(current→z + 1 < CEILING) &&
			(!(datakeeper.grid[COORDSUB(current→z + 1,current→y,current→x)].obs)) &&
			(best > (datakeeper.grid[COORDSUB(current→z,current→y,current→x)].runningdist + 1)) && (
				((datakeeper.grid[COORDSUB(current→z + 1,current→y,current→x)].runningdist) > (datakeeper.grid[COORDSUB(current→z,current→y,current→x)].runningdist + 1)) ||
				((datakeeper.grid[COORDSUB(current→z + 1,current→y,current→x)].runningdist) < 0)
				)
			) {
			datakeeper.grid[COORDSUB(current→z + 1,current→y,current→x)].runningdist = datakeeper.grid[COORDSUB(current→z,current→y,current→x)].runningdist + 1
			datakeeper.grid[COORDSUB(current→z + 1,current→y,current→x)].up = true
			datakeeper.grid[COORDSUB(current→z + 1,current→y,current→x)].fwd = false
			datakeeper.grid[COORDSUB(current→z + 1,current→y,current→x)].down = false
			setcoord3* tmp = malloc(sizeof(setcoord3))
			tmp→x = current→x
			tmp→y = current→y
			tmp→z = current→z + 1
			tmp→prev = last
			last→next = tmp
			datakeeper.hydra_ptr→prev = tmp
			tmp→next = datakeeper.hydra_ptr
			last = tmp
			neighborhood[2][1][1] = tmp
			}
		if (
			(current→x - 1 ≥ 0) &&
			(!(datakeeper.grid[COORDSUB(current→z - 1,current→y,current→x)].obs)) &&
			(best > (datakeeper.grid[COORDSUB(current→z,current→y,current→x)].runningdist + 1)) && (
				((datakeeper.grid[COORDSUB(current→z - 1,current→y,current→x)].runningdist) > (datakeeper.grid[COORDSUB(current→z,current→y,current→x)].runningdist + 1)) ||
				((datakeeper.grid[COORDSUB(current→z - 1,current→y,current→x)].runningdist) < 0)
				)
			) {
			datakeeper.grid[COORDSUB(current→z - 1,current→y,current→x)].runningdist = datakeeper.grid[COORDSUB(current→z,current→y,current→x)].runningdist + 1
			datakeeper.grid[COORDSUB(current→z - 1,current→y,current→x)].up = false
			datakeeper.grid[COORDSUB(current→z - 1,current→y,current→x)].fwd = false
			datakeeper.grid[COORDSUB(current→z - 1,current→y,current→x)].down = true
			setcoord3* tmp = malloc(sizeof(setcoord3))
			tmp→x = current→x
			tmp→y = current→y
			tmp→z = current→z - 1
			tmp→prev = last
			last→next = tmp
			datakeeper.hydra_ptr→prev = tmp
			tmp→next = datakeeper.hydra_ptr
			last = tmp
			neighborhood[0][1][1] = tmp
			}
		
		if (!ortho) {
			switch params.runningnorm : {
				case 0 : diagonal2 = 1; diagonal3 = 1; break;
				case 1 : diagonal2 = 2; diagonal3 = 3; break;
				case 2 : diagonal2 = M_SQRT2; diagonal3 = SQRT3; break;
				default : //invalid norm
				}
	
			if (best > (datakeeper.grid[COORDSUB(current→z,current→y,current→x)].runningdist + diagonal2)) {	
				if (
					(current→x + 1 < MAX_X) &&
					(current→y + 1 < MAX_Y) &&
					(!(datakeeper.grid[COORDSUB(current→z,current→y + 1,current→x + 1)].obs)) &&
					(best > (datakeeper.grid[COORDSUB(current→z,current→y,current→x)].runningdist + diagonal2)) && (
						((datakeeper.grid[COORDSUB(current→z,current→y + 1,current→x + 1)].runningdist) > (datakeeper.grid[COORDSUB(current→z,current→y,current→x)].runningdist + diagonal2)) ||
						((datakeeper.grid[COORDSUB(current→z,current→y + 1,current→x + 1)].runningdist) < 0)
						)
					) {
					datakeeper.grid[COORDSUB(current→z,current→y + 1,current→x + 1)].runningdist = datakeeper.grid[COORDSUB(current→z,current→y,current→x)].runningdist + diagonal2
					datakeeper.grid[COORDSUB(current→z,current→y + 1,current→x + 1)].az = 3
					datakeeper.grid[COORDSUB(current→z,current→y + 1,current→x + 1)].up = false
					datakeeper.grid[COORDSUB(current→z,current→y + 1,current→x + 1)].fwd = true
					datakeeper.grid[COORDSUB(current→z,current→y + 1,current→x + 1)].down = false
					setcoord3* tmp = malloc(sizeof(setcoord3))
					tmp→x = current→x + 1
					tmp→y = current→y + 1
					tmp→z = current→z
					tmp→prev = last
					last→next = tmp
					datakeeper.hydra_ptr→prev = tmp
					tmp→next = datakeeper.hydra_ptr
					last = tmp
					neighborhood[1][2][2] = tmp
					}
				if (
					(current→x - 1 ≥ 0) &&
					(current→y + 1 < MAX_Y) &&
					(!(datakeeper.grid[COORDSUB(current→z,current→y + 1,current→x - 1)].obs)) &&
					(best > (datakeeper.grid[COORDSUB(current→z,current→y,current→x)].runningdist + diagonal2)) && (
						((datakeeper.grid[COORDSUB(current→z,current→y + 1,current→x - 1)].runningdist) > (datakeeper.grid[COORDSUB(current→z,current→y,current→x)].runningdist + diagonal2)) ||
						((datakeeper.grid[COORDSUB(current→z,current→y + 1,current→x - 1)].runningdist) < 0)
						)
					) {
					datakeeper.grid[COORDSUB(current→z,current→y + 1,current→x - 1)].runningdist = datakeeper.grid[COORDSUB(current→z,current→y,current→x)].runningdist + diagonal2
					datakeeper.grid[COORDSUB(current→z,current→y + 1,current→x - 1)].az = 5
					datakeeper.grid[COORDSUB(current→z,current→y + 1,current→x - 1)].up = false
					datakeeper.grid[COORDSUB(current→z,current→y + 1,current→x - 1)].fwd = true
					datakeeper.grid[COORDSUB(current→z,current→y + 1,current→x - 1)].down = false
					setcoord3* tmp = malloc(sizeof(setcoord3))
					tmp→x = current→x - 1
					tmp→y = current→y + 1
					tmp→z = current→z
					tmp→prev = last
					last→next = tmp
					datakeeper.hydra_ptr→prev = tmp
					tmp→next = datakeeper.hydra_ptr
					last = tmp
					neighborhood[1][2][0] = tmp
					}
				if (
					(current→x + 1 < MAX_X) &&
					(current→y - 1 ≥ 0) &&
					(!(datakeeper.grid[COORDSUB(current→z,current→y - 1,current→x + 1)].obs)) &&
					(best > (datakeeper.grid[COORDSUB(current→z,current→y - 1,current→x + 1)].runningdist + diagonal2)) && (
						((datakeeper.grid[COORDSUB(current→z,current→y - 1,current→x + 1)].runningdist) > (datakeeper.grid[COORDSUB(current→z,current→y,current→x)].runningdist + diagonal2)) ||
						((datakeeper.grid[COORDSUB(current→z,current→y - 1,current→x + 1)].runningdist) < 0)
						)
					) {
					datakeeper.grid[COORDSUB(current→z,current→y - 1,current→x + 1)].runningdist = datakeeper.grid[COORDSUB(current→z,current→y,current→x)].runningdist + diagonal2
					datakeeper.grid[COORDSUB(current→z,current→y - 1,current→x + 1)].az = 1
					datakeeper.grid[COORDSUB(current→z,current→y - 1,current→x + 1)].up = false
					datakeeper.grid[COORDSUB(current→z,current→y - 1,current→x + 1)].fwd = true
					datakeeper.grid[COORDSUB(current→z,current→y - 1,current→x + 1)].down = false
					setcoord3* tmp = malloc(sizeof(setcoord3))
					tmp→x = current→x + 1
					tmp→y = current→y - 1
					tmp→z = current→z
					tmp→prev = last
					last→next = tmp
					datakeeper.hydra_ptr→prev = tmp
					tmp→next = datakeeper.hydra_ptr
					last = tmp
					neighborhood[1][0][2] = tmp
					}
				if (
					(current→x - 1 ≥ 0) &&
					(current→y - 1 ≥ 0) &&
					(!(datakeeper.grid[COORDSUB(current→z,current→y - 1,current→x - 1)].obs)) &&
					(best > (datakeeper.grid[COORDSUB(current→z,current→y - 1,current→x - 1)].runningdist + diagonal2)) && (
						((datakeeper.grid[COORDSUB(current→z,current→y - 1,current→x - 1)].runningdist) > (datakeeper.grid[COORDSUB(current→z,current→y,current→x)].runningdist + diagonal2)) ||
						((datakeeper.grid[COORDSUB(current→z,current→y - 1,current→x - 1)].runningdist) < 0)
						)
					) {
					datakeeper.grid[COORDSUB(current→z,current→y - 1,current→x - 1)].runningdist = datakeeper.grid[COORDSUB(current→z,current→y,current→x)].runningdist + diagonal2
					datakeeper.grid[COORDSUB(current→z,current→y - 1,current→x - 1)].az = 7
					datakeeper.grid[COORDSUB(current→z,current→y - 1,current→x - 1)].up = false
					datakeeper.grid[COORDSUB(current→z,current→y - 1,current→x - 1)].fwd = true
					datakeeper.grid[COORDSUB(current→z,current→y - 1,current→x - 1)].down = false
					setcoord3* tmp = malloc(sizeof(setcoord3))
					tmp→x = current→x - 1
					tmp→y = current→y - 1
					tmp→z = current→z
					tmp→prev = last
					last→next = tmp
					datakeeper.hydra_ptr→prev = tmp
					tmp→next = datakeeper.hydra_ptr
					last = tmp
					neighborhood[1][0][0] = tmp
					}
			
				if (
					(current→x + 1 < MAX_X) &&
					(current→z + 1 < CEILING) &&
					(!(datakeeper.grid[COORDSUB(current→z + 1,current→y,current→x + 1)].obs)) &&
					(best > (datakeeper.grid[COORDSUB(current→z,current→y,current→x)].runningdist + diagonal2)) && (
						((datakeeper.grid[COORDSUB(current→z + 1,current→y,current→x + 1)].runningdist) > (datakeeper.grid[COORDSUB(current→z,current→y,current→x)].runningdist + diagonal2)) ||
						((datakeeper.grid[COORDSUB(current→z + 1,current→y,current→x + 1)].runningdist) < 0)
						)
					) {
					datakeeper.grid[COORDSUB(current→z + 1,current→y,current→x + 1)].runningdist = datakeeper.grid[COORDSUB(current→z,current→y,current→x)].runningdist + diagonal2
					datakeeper.grid[COORDSUB(current→z + 1,current→y,current→x + 1)].az = 2
					datakeeper.grid[COORDSUB(current→z + 1,current→y,current→x + 1)].up = true
					datakeeper.grid[COORDSUB(current→z + 1,current→y,current→x + 1)].fwd = true
					datakeeper.grid[COORDSUB(current→z + 1,current→y,current→x + 1)].down = false
					setcoord3* tmp = malloc(sizeof(setcoord3))
					tmp→x = current→x + 1
					tmp→y = current→y
					tmp→z = current→z + 1
					tmp→prev = last
					last→next = tmp
					datakeeper.hydra_ptr→prev = tmp
					tmp→next = datakeeper.hydra_ptr
					last = tm
					) {
					datakeeper.grid[COORDSUB(current→z + 1,current→y,current→x - 1)].runningdist = datakeeper.grid[COORDSUB(current→z,current→y,current→x)].runningdist + diagonal2
					datakeeper.grid[COORDSUB(current→z + 1,current→y,current→x - 1)].az = 6
					datakeeper.grid[COORDSUB(current→z + 1,current→y,current→x - 1)].up = true
					datakeeper.grid[COORDSUB(current→z + 1,current→y,current→x - 1)].fwd = true
					datakeeper.grid[COORDSUB(current→z + 1,current→y,current→x - 1)].down = false
					setcoord3* tmp = malloc(sizeof(setcoord3))
					tmp→x = current→x - 1
					tmp→y = current→y
					tmp→z = current→z + z
					tmp→prev = last
					last→next = tmp
					datakeeper.hydra_ptr→prev = tmp
					tmp→next = datakeeper.hydra_ptr
					last = tmp
					neighborhood[2][1][0] = tmp
					}
				if (
					(current→x + 1 < MAX_X) &&
					(current→z - 1 ≥ 0) &&
					(!(datakeeper.grid[COORDSUB(current→z - 1,current→y,current→x + 1)].obs)) &&
					(best > (datakeeper.grid[COORDSUB(current→z,current→y,current→x)].runningdist + diagonal2)) && (
						((datakeeper.grid[COORDSUB(current→z - 1,current→y,current→x + 1)].runningdist) > (datakeeper.grid[COORDSUB(current→z,current→y,current→x)].runningdist + diagonal2)) ||
						((datakeeper.grid[COORDSUB(current→z - 1,current→y,current→x + 1)].runningdist) < 0)
						)
					) {
					datakeeper.grid[COORDSUB(current→z - 1,current→y,current→x + 1)].runningdist = datakeeper.grid[COORDSUB(current→z,current→y,current→x)].runningdist + diagonal2
					datakeeper.grid[COORDSUB(current→z - 1,current→y,current→x + 1)].az = 2
					datakeeper.grid[COORDSUB(current→z - 1,current→y,current→x + 1)].up = false
					datakeeper.grid[COORDSUB(current→z - 1,current→y,current→x + 1)].fwd = true
					datakeeper.grid[COORDSUB(current→z - 1,current→y,current→x + 1)].down = true
					setcoord3* tmp = malloc(sizeof(setcoord3))
					tmp→x = current→x + 1
					tmp→y = current→y
					tmp→z = current→z - 1
					tmp→prev = last
					last→next = tmp
					datakeeper.hydra_ptr→prev = tmp
					tmp→next = datakeeper.hydra_ptr
					last = tmp
					neighborhood[0][1][2] = tmp
					}
				if (
					(current→x - 1 ≥ 0) &&
					(current→z - 1 ≥ 0) &&
					(!(datakeeper.grid[COORDSUB(current→z - 1,current→y,current→x - 1)].obs)) &&
					(best > (datakeeper.grid[COORDSUB(current→z,current→y,current→x)].runningdist + diagonal2)) && (
						((datakeeper.grid[COORDSUB(current→z - 1,current→y,current→x - 1)].runningdist) > (datakeeper.grid[COORDSUB(current→z,current→y,current→x)].runningdist + diagonal2)) ||
						((datakeeper.grid[COORDSUB(current→z - 1,current→y,current→x - 1)].runningdist) < 0)
						)
					) {
					datakeeper.grid[COORDSUB(current→z - 1,current→y,current→x - 1)].runningdist = datakeeper.grid[COORDSUB(current→z,current→y,current→x)].runningdist + diagonal2
					datakeeper.grid[COORDSUB(current→z - 1,current→y,current→x - 1)].az = 2
					datakeeper.grid[COORDSUB(current→z - 1,current→y,current→x - 1)].up = false
					datakeeper.grid[COORDSUB(current→z - 1,current→y,current→x - 1)].fwd = true
					datakeeper.grid[COORDSUB(current→z - 1,current→y,current→x - 1)].down = true
					setcoord3* tmp = malloc(sizeof(setcoord3))
					tmp→x = current→x - 1
					tmp→y = current→y
					tmp→z = current→z - 1
					tmp→prev = last
					last→next = tmp
					datakeeper.hydra_ptr→prev = tmp
					tmp→next = datakeeper.hydra_ptr
					last = tmp
					neighborhood[0][1][0] = tmp
					}
			
				if (
					(current→y + 1 < MAX_Y) &&
					(current→z + 1 < CEILING) &&
					(!(datakeeper.grid[COORDSUB(current→z + 1,current→y + 1,current→x)].obs)) &&
					(best > (datakeeper.grid[COORDSUB(current→z,current→y,current→x)].runningdist + diagonal2)) && (
						((datakeeper.grid[COORDSUB(current→z + 1,current→y + 1,current→x)].runningdist) > (datakeeper.grid[COORDSUB(current→z,current→y,current→x)].runningdist + diagonal2)) ||
						((datakeeper.grid[COORDSUB(current→z + 1,current→y + 1,current→x)].runningdist) < 0)
						)
					) {
					datakeeper.grid[COORDSUB(current→z + 1,current→y + 1,current→x)].runningdist = datakeeper.grid[COORDSUB(current→z,current→y,current→x)].runningdist + diagonal2
					datakeeper.grid[COORDSUB(current→z + 1,current→y + 1,current→x)].az = 4
					datakeeper.grid[COORDSUB(current→z + 1,current→y + 1,current→x)].up = true
					datakeeper.grid[COORDSUB(current→z + 1,current→y + 1,current→x)].fwd = true
					datakeeper.grid[COORDSUB(current→z + 1,current→y + 1,current→x)].down = false
					setcoord3* tmp = malloc(sizeof(setcoord3))
					tmp→x = current→x
					tmp→y = current→y + 1
					tmp→z = current→z + 1
					tmp→prev = last
					last→next = tmp
					datakeeper.hydra_ptr→prev = tmp
					tmp→next = datakeeper.hydra_ptr
					last = tmp
					neighborhood[2][2][1] = tmp
					}
				if (
					(current→y - 1 ≥ 0) &&
					(current→z + 1 < CEILING) &&
					(!(datakeeper.grid[COORDSUB(current→z + 1,current→y - 1,current→x)].obs)) &&
					(best > (datakeeper.grid[COORDSUB(current→z,current→y,current→x)].runningdist + diagonal2)) && (
						((datakeeper.grid[COORDSUB(current→z + 1,current→y - 1,current→x)].runningdist) > (datakeeper.grid[COORDSUB(current→z,current→y,current→x)].runningdist + diagonal2)) ||
						((datakeeper.grid[COORDSUB(current→z + 1,current→y - 1,current→x)].runningdist) < 0)
						)
					) {
					datakeeper.grid[COORDSUB(current→z + 1,current→y - 1,current→x)].runningdist = datakeeper.grid[COORDSUB(current→z,current→y,current→x)].runningdist + diagonal2
					datakeeper.grid[COORDSUB(current→z + 1,current→y - 1,current→x)].az = 0
					datakeeper.grid[COORDSUB(current→z + 1,current→y - 1,current→x)].up = true
					datakeeper.grid[COORDSUB(current→z + 1,current→y - 1,current→x)].fwd = true
					datakeeper.grid[COORDSUB(current→z + 1,current→y - 1,current→x)].down = false
					setcoord3* tmp = malloc(sizeof(setcoord3))
					tmp→x = current→x
					tmp→y = current→y - 1
					tmp→z = current→z + 1
					tmp→prev = last
					last→next = tmp
					datakeeper.hydra_ptr→prev = tmp
					tmp→next = datakeeper.hydra_ptr
					last = tmp
					neighborhood[2][0][1] = tmp
					}
				if (
					(current→y + 1 < MAX_Y) &&
					(current→z - 1 ≥ 0) &&
					(!(datakeeper.grid[COORDSUB(current→z - 1,current→y + 1,current→x)].obs)) &&
					(best > (datakeeper.grid[COORDSUB(current→z,current→y,current→x)].runningdist + diagonal2)) && (
						((datakeeper.grid[COORDSUB(current→z - 1,current→y + 1,current→x)].runningdist) > (datakeeper.grid[COORDSUB(current→z,current→y,current→x)].runningdist + diagonal2)) ||
						((datakeeper.grid[COORDSUB(current→z - 1,current→y + 1,current→x)].runningdist) < 0)
						)
					) {
					datakeeper.grid[COORDSUB(current→z - 1,current→y + 1,current→x)].runningdist = datakeeper.grid[COORDSUB(current→z,current→y,current→x)].runningdist + diagonal2
					datakeeper.grid[COORDSUB(current→z - 1,current→y + 1,current→x)].az = 4
					datakeeper.grid[COORDSUB(current→z - 1,current→y + 1,current→x)].up = false
					datakeeper.grid[COORDSUB(current→z - 1,current→y + 1,current→x)].fwd = true
					datakeeper.grid[COORDSUB(current→z - 1,current→y + 1,current→x)].down = true
					setcoord3* tmp = malloc(sizeof(setcoord3))
					tmp→x = current→x
					tmp→y = current→y + 1
					tmp→z = current→z - 1
					tmp→prev = last
					last→next = tmp
					datakeeper.hydra_ptr→prev = tmp
					tmp→next = datakeeper.hydra_ptr
					last = tmp
					neighborhood[0][2][1] = tmp
					}
				if (
					(current→y - 1 ≥ 0) &&
					(current→z - 1 ≥ 0) &&
					(!(datakeeper.grid[COORDSUB(current→z - 1,current→y - 1,current→x)].obs)) &&
					(best > (datakeeper.grid[COORDSUB(current→z,current→y,current→x)].runningdist + diagonal2)) && (
						((datakeeper.grid[COORDSUB(current→z - 1,current→y - 1,current→x)].runningdist) > (datakeeper.grid[COORDSUB(current→z,current→y,current→x)].runningdist + diagonal2)) ||
						((datakeeper.grid[COORDSUB(current→z - 1,current→y - 1,current→x)].runningdist) < 0)
						)
					) {
					datakeeper.grid[COORDSUB(current→z - 1,current→y - 1,current→x)].runningdist = datakeeper.grid[COORDSUB(current→z,current→y,current→x)].runningdist + diagonal2
					datakeeper.grid[COORDSUB(current→z - 1,current→y - 1,current→x)].az = 0
					datakeeper.grid[COORDSUB(current→z - 1,current→y - 1,current→x)].up = false
					datakeeper.grid[COORDSUB(current→z - 1,current→y - 1,current→x)].fwd = true
					datakeeper.grid[COORDSUB(current→z - 1,current→y - 1,current→x)].down = true
					setcoord3* tmp = malloc(sizeof(setcoord3))
					tmp→x = current→x
					tmp→y = current→y - 1
					tmp→z = current→z - 1
					tmp→prev = last
					last→next = tmp
					datakeeper.hydra_ptr→prev = tmp
					tmp→next = datakeeper.hydra_ptr
					last = tmp
					neighborhood[0][0][1] = tmp
					}
				
				if (best > (datakeeper.grid[COORDSUB(current→z,current→y,current→x)].runningdist + diagonal3)) {
					if (
						(current→x + 1 < MAX_X) &&
						(current→y + 1 < MAX_Y) &&
						(current→z + 1 < CEILING) &&
						(!(datakeeper.grid[COORDSUB(current→z + 1,current→y + 1,current→x + 1)].obs)) && (
							((datakeeper.grid[COORDSUB(current→z + 1,current→y + 1,current→x + 1)].runningdist) > (datakeeper.grid[COORDSUB(current→z,current→y,current→x)].runningdist + diagonal3)) ||
							((datakeeper.grid[COORDSUB(current→z + 1,current→y + 1,current→x + 1)].runningdist) < 0)
							)
						) {
						datakeeper.grid[COORDSUB(current→z + 1,current→y + 1,current→x + 1)].runningdist = datakeeper.grid[COORDSUB(current→z,current→y,current→x)].runningdist + diagonal3
						datakeeper.grid[COORDSUB(current→z + 1,current→y + 1,current→x + 1)].az = 3
						datakeeper.grid[COORDSUB(current→z + 1,current→y + 1,current→x + 1)].up = true
						datakeeper.grid[COORDSUB(current→z + 1,current→y + 1,current→x + 1)].fwd = true
						datakeeper.grid[COORDSUB(current→z + 1,current→y + 1,current→x + 1)].down = false
						setcoord3* tmp = malloc(sizeof(setcoord3))
						tmp→x = current→x + 1
						tmp→y = current→y + 1
						tmp→z = current→z + 1
						tmp→prev = last
						last→next = tmp
						datakeeper.hydra_ptr→prev = tmp
						tmp→next = datakeeper.hydra_ptr
						last = tmp
						neighborhood[2][2][2] = tmp
						}
					if (
						(current→x - 1 ≥ 0) &&
						(current→y + 1 < MAX_Y) &&
						(current→z + 1 < CEILING) &&
						(!(datakeeper.grid[COORDSUB(current→z + 1,current→y + 1,current→x - 1)].obs)) && (
							((datakeeper.grid[COORDSUB(current→z + 1,current→y + 1,current→x - 1)].runningdist) > (datakeeper.grid[COORDSUB(current→z,current→y,current→x)].runningdist + diagonal3)) ||
							((datakeeper.grid[COORDSUB(current→z + 1,current→y + 1,current→x - 1)].runningdist) < 0)
							)
						) {
						datakeeper.grid[COORDSUB(current→z + 1,current→y + 1,current→x - 1)].runningdist = datakeeper.grid[COORDSUB(current→z,current→y,current→x)].runningdist + diagonal3
						datakeeper.grid[COORDSUB(current→z + 1,current→y + 1,current→x - 1)].az = 5
						datakeeper.grid[COORDSUB(current→z + 1,current→y + 1,current→x - 1)].up = true
						datakeeper.grid[COORDSUB(current→z + 1,current→y + 1,current→x - 1)].fwd = true
						datakeeper.grid[COORDSUB(current→z + 1,current→y + 1,current→x - 1)].down = false
						setcoord3* tmp = malloc(sizeof(setcoord3))
						tmp→x = current→x - 1
						tmp→y = current→y + 1
						tmp→z = current→z + 1
						tmp→prev = last
						last→next = tmp
						datakeeper.hydra_ptr→prev = tmp
						tmp→next = datakeeper.hydra_ptr
						last = tmp
						neighborhood[2][2][0] = tmp
						}
					if (
						(current→x + 1 < MAX_X) &&
						(current→y - 1 ≥ 0) &&
						(current→z + 1 < CEILING) &&
						(!(datakeeper.grid[COORDSUB(current→z + 1,current→y - 1,current→x + 1)].obs)) && (
							((datakeeper.grid[COORDSUB(current→z + 1,current→y - 1,current→x + 1)].runningdist) > (datakeeper.grid[COORDSUB(current→z,current→y,current→x)].runningdist + diagonal3)) ||
							((datakeeper.grid[COORDSUB(current→z + 1,current→y - 1,current→x + 1)].runningdist) < 0)
							)
						) {
						datakeeper.grid[COORDSUB(current→z + 1,current→y - 1,current→x + 1)].runningdist = datakeeper.grid[COORDSUB(current→z,current→y,current→x)].runningdist + diagonal3
						datakeeper.grid[COORDSUB(current→z + 1,current→y - 1,current→x + 1)].az = 1
						datakeeper.grid[COORDSUB(current→z + 1,current→y - 1,current→x + 1)].up = true
						datakeeper.grid[COORDSUB(current→z + 1,current→y - 1,current→x + 1)].fwd = true
						datakeeper.grid[COORDSUB(current→z + 1,current→y - 1,current→x + 1)].down = false
						setcoord3* tmp = malloc(sizeof(setcoord3))
						tmp→x = current→x + 1
						tmp→y = current→y - 1
						tmp→z = current→z + 1
						tmp→prev = last
						last→next = tmp
						datakeeper.hydra_ptr→prev = tmp
						tmp→next = datakeeper.hydra_ptr
						last = tmp
						neighborhood[2][0][2] = tmp
						}
					if (
						(current→x - 1 ≥ 0) &&
						(current→y - 1 ≥ 0) &&
						(current→z + 1 < CEILING) &&
						(!(datakeeper.grid[COORDSUB(current→z + 1,current→y - 1,current→x - 1)].obs)) && (
							((datakeeper.grid[COORDSUB(current→z + 1,current→y - 1,current→x - 1)].runningdist) > (datakeeper.grid[COORDSUB(current→z,current→y,current→x)].runningdist + diagonal3)) ||
							((datakeeper.grid[COORDSUB(current→z + 1,current→y - 1,current→x - 1)].runningdist) < 0)
							)
						) {
						datakeeper.grid[COORDSUB(current→z + 1,current→y - 1,current→x - 1)].runningdist = datakeeper.grid[COORDSUB(current→z,current→y,current→x)].runningdist + diagonal3
						datakeeper.grid[COORDSUB(current→z + 1,current→y - 1,current→x - 1)].az = 7
						datakeeper.grid[COORDSUB(current→z + 1,current→y - 1,current→x - 1)].up = true
						datakeeper.grid[COORDSUB(current→z + 1,current→y - 1,current→x - 1)].fwd = true
						datakeeper.grid[COORDSUB(current→z + 1,current→y - 1,current→x - 1)].down = false
						setcoord3* tmp = malloc(sizeof(setcoord3))
						tmp→x = current→x - 1
						tmp→y = current→y - 1
						tmp→z = current→z + 1
						tmp→prev = last
						last→next = tmp
						datakeeper.hydra_ptr→prev = tmp
						tmp→next = datakeeper.hydra_ptr
						last = tmp
						neighborhood[2][0][0] = tmp
						}
					if (
						(current→x + 1 < MAX_X) &&
						(current→y + 1 < MAX_Y) &&
						(current→z - 1 ≥ 0) &&
						(!(datakeeper.grid[COORDSUB(current→z - 1,current→y + 1,current→x + 1)].obs)) && (
							((datakeeper.grid[COORDSUB(current→z - 1,current→y + 1,current→x + 1)].runningdist) > (datakeeper.grid[COORDSUB(current→z,current→y,current→x)].runningdist + diagonal3)) ||
							((datakeeper.grid[COORDSUB(current→z - 1,current→y + 1,current→x + 1)].runningdist) < 0)
							)
						) {
						datakeeper.grid[COORDSUB(current→z - 1,current→y + 1,current→x + 1)].runningdist = datakeeper.grid[COORDSUB(current→z,current→y,current→x)].runningdist + diagonal3
						datakeeper.grid[COORDSUB(current→z - 1,current→y + 1,current→x + 1)].az = 3
						datakeeper.grid[COORDSUB(current→z - 1,current→y + 1,current→x + 1)].up = false
						datakeeper.grid[COORDSUB(current→z - 1,current→y + 1,current→x + 1)].fwd = true
						datakeeper.grid[COORDSUB(current→z - 1,current→y + 1,current→x + 1)].down = true
						setcoord3* tmp = malloc(sizeof(setcoord3))
						tmp→x = current→x - 1
						tmp→y = current→y - 1
						tmp→z = current→z - 1
						tmp→prev = last
						last→next = tmp
						datakeeper.hydra_ptr→prev = tmp
						tmp→next = datakeeper.hydra_ptr
						last = tmp
						neighborhood[0][2][2] = tmp
						}
					if (
						(current→x - 1 ≥ 0) &&
						(current→y + 1 < MAX_Y) &&
						(current→z - 1 ≥ 0) &&
						(!(datakeeper.grid[COORDSUB(current→z - 1,current→y + 1,current→x - 1)].obs)) && (
							((datakeeper.grid[COORDSUB(current→z - 1,current→y + 1,current→x - 1)].runningdist) > (datakeeper.grid[COORDSUB(current→z,current→y,current→x)].runningdist + diagonal3)) ||
							((datakeeper.grid[COORDSUB(current→z - 1,current→y + 1,current→x - 1)].runningdist) < 0)
							)
						) {
						datakeeper.grid[COORDSUB(current→z - 1,current→y + 1,current→x - 1)].runningdist = datakeeper.grid[COORDSUB(current→z,current→y,current→x)].runningdist + diagonal3
						datakeeper.grid[COORDSUB(current→z - 1,current→y + 1,current→x - 1)].az = 5
						datakeeper.grid[COORDSUB(current→z - 1,current→y + 1,current→x - 1)].up = false
						datakeeper.grid[COORDSUB(current→z - 1,current→y + 1,current→x - 1)].fwd = true
						datakeeper.grid[COORDSUB(current→z - 1,current→y + 1,current→x - 1)].down = true
						setcoord3* tmp = malloc(sizeof(setcoord3))
						tmp→x = current→x - 1
						tmp→y = current→y + 1
						tmp→z = current→z - 1
						tmp→prev = last
						last→next = tmp
						datakeeper.hydra_ptr→prev = tmp
						tmp→next = datakeeper.hydra_ptr
						last = tmp
						neighborhood[0][2][0] = tmp
						}
					if (
						(current→x + 1 < MAX_X) &&
						(current→y - 1 ≥ 0) &&
						(current→z - 1 ≥ 0) &&
						(!(datakeeper.grid[COORDSUB(current→z - 1,current→y - 1,current→x + 1)].obs)) &&
						(best > (datakeeper.grid[COORDSUB(current→z,current→y,current→x)].runningdist + diagonal3)) && (
							((datakeeper.grid[COORDSUB(current→z - 1,current→y - 1,current→x + 1)].runningdist) > (datakeeper.grid[COORDSUB(current→z,current→y,current→x)].runningdist + diagonal3)) ||
							((datakeeper.grid[COORDSUB(current→z - 1,current→y - 1,current→x + 1)].runningdist) < 0)
							)
						) {
						datakeeper.grid[COORDSUB(current→z - 1,current→y - 1,current→x + 1)].runningdist = datakeeper.grid[COORDSUB(current→z,current→y,current→x)].runningdist + diagonal3
						datakeeper.grid[COORDSUB(current→z - 1,current→y - 1,current→x + 1)].az = 1
						datakeeper.grid[COORDSUB(current→z - 1,current→y - 1,current→x + 1)].up = false
						datakeeper.grid[COORDSUB(current→z - 1,current→y - 1,current→x + 1)].fwd = true
						datakeeper.grid[COORDSUB(current→z - 1,current→y - 1,current→x + 1)].down = true
						setcoord3* tmp = malloc(sizeof(setcoord3))
						tmp→x = current→x + 1
						tmp→y = current→y - 1
						tmp→z = current→z - 1
						tmp→prev = last
						last→next = tmp
						datakeeper.hydra_ptr→prev = tmp
						tmp→next = datakeeper.hydra_ptr
						last = tmp
						neighborhood[0][0][2] = tmp
						}
					if (
						(current→x - 1 ≥ 0) &&
						(current→y - 1 ≥ 0) &&
						(current→z - 1 ≥ 0) &&
						(!(datakeeper.grid[COORDSUB(current→z - 1,current→y - 1,current→x - 1)].obs)) && (
							((datakeeper.grid[COORDSUB(current→z - 1,current→y - 1,current→x - 1)].runningdist) > (datakeeper.grid[COORDSUB(current→z,current→y,current→x)].runningdist + diagonal3)) ||
							((datakeeper.grid[COORDSUB(current→z - 1,current→y - 1,current→x - 1)].runningdist) < 0)
							)
						) {
						datakeeper.grid[COORDSUB(current→z - 1,current→y - 1,current→x - 1)].runningdist = datakeeper.grid[COORDSUB(current→z,current→y,current→x)].runningdist + diagonal3
						datakeeper.grid[COORDSUB(current→z - 1,current→y - 1,current→x - 1)].az = 7
						datakeeper.grid[COORDSUB(current→z - 1,current→y - 1,current→x - 1)].up = false
						datakeeper.grid[COORDSUB(current→z - 1,current→y - 1,current→x - 1)].fwd = true
						datakeeper.grid[COORDSUB(current→z - 1,current→y - 1,current→x - 1)].down = true
						setcoord3* tmp = malloc(sizeof(setcoord3))
						tmp→x = current→x - 1
						tmp→y = current→y - 1
						tmp→z = current→z - 1
						tmp→prev = last
						last→next = tmp
						datakeeper.hydra_ptr→prev = tmp
						tmp→next = datakeeper.hydra_ptr
						last = tmp
						neighborhood[0][0][0] = tmp
						}
					}
				}
			}
		}
skip:
	if (current == datakeeper.hydra_ptr) {
		datakeeper.hydra_ptr→next→prev = datakeeper.hydra_ptr→prev
		datakeeper.hydra_ptr→prev→next = datakeeper.hydra_ptr→next
		datakeeper.hydra_ptr = datakeeper.hydra_ptr→next
		}
	free(current)
	current = NULL
	neighborhood[1][1][1] = NULL	
	
	winning = INFINITY
	for (uchar z = 0,z < 3,z++) {
		for (uchar y = 0,y < 3,y++) {
			for (uchar x = 0,x < 3,x++) {
				if (neighborhood[z][y][x] != NULL) {
					if (datakeeper.grid[COORDSUB(neighborhood[z][y][x]→z,neighborhood[z][y][x]→y,neighborhood[z][y][x]→x)].goaldist < winning) {current = neighborhood[z][y][x]}
					}
				}
			}
		}
	RESETNEIGHBORHOOD
	if (current == NULL) {
		current = datakeeper.hydra_ptr
		ptrnext = datakeeper.hydra_ptr→next
		for (;ptrnext != datakeeper.hydra_ptr;ptrnext = ptrnext→next) {
			ptrnext→runningdist < current→runningdist ? noop() : current = ptrnext
			}
		}
	if (((current→x == pointb.x) && (current→y == pointb.y) && (current→z == pointb.z)) && (params.pathtyp > 0)) {goto(breakout)}
	}
breakout:
coord3 currentcoord
currentcoord.x = current→x
currentcoord.y = current→y
currentcoord.z = current→z
coord3 nextcoord

current = datakeeper.hydra_ptr→prev
setcoord3* previous = datakeeper.hydra_ptr→prev→prev
datakeeper.hydra_ptr→next = NULL
datakeeper.hydra_ptr→prev = NULL
while (previous != NULL) {
	free (current)
	current = previous
	previous = previous→prev
	}
free(current)
current = NULL


while (!((currentcoord.x == pointa.x) && (currentcoord.y == pointa.y) && (currentcoord.z == pointa.z))) {
	//extrapolate origin from trajectory
	nextcoord.z = currentcoord.z + datakeeper.grid[COORDSUB(currentcoord.z,currentcoord.y,currentcoord.x)].down - datakeeper.grid[COORDSUB(currentcoord.z,currentcoord.y,currentcoord.x)].up
	if (datakeeper.grid[COORDSUB(currentcoord.z,currentcoord.y,currentcoord.x)].fwd) {
		switch datakeeper.grid[COORDSUB(currentcoord.z,currentcoord.y,currentcoord.x)].az : {
			case 1 : nextcoord.y = currentcoord.y - 1; nextcoord.x = currentcoord.x + 1; break;
			case 2 : nextcoord.y = currentcoord.y; nextcoord.x = currentcoord.x + 1; break;
			case 3 : nextcoord.y = currentcoord.y + 1; nextcoord.x = currentcoord.x + 1; break;
			case 4 : nextcoord.y = currentcoord.y + 1; nextcoord.x = currentcoord.x; break;
			case 5 : nextcoord.y = currentcoord.y + 1; nextcoord.x = currentcoord.x - 1; break;
			case 6 : nextcoord.y = currentcoord.y; nextcoord.x = currentcoord.x - 1; break;
			case 7 : nextcoord.y = currentcoord.y - 1; nextcoord.x = currentcoord.x - 1; break; 
			default : nextcoord.y = currentcoord.y - 1; nextcoord.x = currentcoord.x; break;
			}
		}
	currentcoord = nextcoord
	if (!datakeeper.grid[COORDSUB(currentcoord.z,currentcoord.y,currentcoord.x)].ex) {
		activeroom→tiledata[COORDSUB(currentcoord.z,currentcoord.y,currentcoord.x)] = tile
		}
	}
}