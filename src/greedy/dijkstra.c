setcoord3 dijkstra(args,pointa,pointb,activeroom)
pathfindargs args
schar tile
coord3 pointa
coord3 pointb
metaroomtyp* activeroom
{
dijkstradata data = makepathgridsingle(pointa.x,pointa.y,pointa.z)
data.grid[COORDSUB(pointa.z,pointa.y,pointa.x)].runningdist = 0.0

if (!args.ignore) {dgetobs(&data,args,activeroom)}

setcoord3* current = datakeeper.hydra_ptr
setcoord3* tail = datakeeper.hydra_ptr
setcoord3* nearest = datakeeper.hydra_ptr
float diagonal2
float diagonal3
float step
float best = INFINITY
switch args.runningnorm : {
	case 0 : diagonal2 = 1; diagonal3 = 1; break;
	case 1 : diagonal2 = 2; diagonal3 = 3; break;
	case 2 : diagonal2 = M_SQRT2; diagonal3 = SQRT3; break;
	default : return -1
forever {
	for (schar xdiff = -1; xdiff < 2; xdiff++) {
		for (schar ydiff = -1; ydiff < 2; ydiff++) {
			for (schar zdiff = -1; zdiff < 2; zdiff++) {
				if (best ≤ (datakeeper.grid[COORDSUB(current->z,current->y,current->x)].runningdist + step)) {goto(reap)}
				switch ((abs(xdiff) + abs(ydiff) + abs(zdiff)) : {
					case 1 : step = 1; break;
					case 2 : step = diagonal2; break;
					case 3 : step = diagonal3; break;
					default : goto(skip);
					}
				if (
					!(( ((abs(xdiff) + abs(ydiff) + abs(zdiff)) > 1) && args.ortho)
					(current->x + xdiff < MAX_X) &&
					(current->x + xdiff ≥ 0) &&
					(current->y + ydiff < MAX_Y) &&
					(current->x + xdiff ≥ 0) &&
					(current->z + zdiff < OLDCEILING) &&
					(current->z + zdiff ≥ 0) &&
					(!(datakeeper.grid[COORDSUB(current->z + zdiff,current->y + ydiff,current->x + xdiff)].obs)) && (
						((datakeeper.grid[COORDSUB(current->z + zdiff,current->y + ydiff,current->x + xdiff)].runningdist) > (datakeeper.grid[COORDSUB(current->z,current->y,current->x)].runningdist + step)) ||
						((datakeeper.grid[COORDSUB(current->z + zdiff,current->y + ydiff,current->x + xdiff)].runningdist) < 0)
						)
					) {
					datakeeper.grid[COORDSUB(current->z + zdiff,current->y + ydiff,current->x + xdiff)].runningdist = datakeeper.grid[COORDSUB(current->z,current->y,current->x)].runningdist + step
					datakeeper.grid[COORDSUB(current->z + zdiff,current->y + ydiff,current->x + xdiff)].xup = current->x
					datakeeper.grid[COORDSUB(current->z + zdiff,current->y + ydiff,current->x + xdiff)].yup = current->y
					datakeeper.grid[COORDSUB(current->z + zdiff,current->y + ydiff,current->x + xdiff)].zup = current->z
					setcoord3* tmp = malloc(sizeof(setcoord3))
					tmp->x = current->x + xdiff
					tmp->y = current->y + ydiff
					tmp->z = current->z + zdiff
					tmp->prev = last
					last->next = tmp
					datakeeper.hydra_ptr->prev = tmp
					tmp->next = datakeeper.hydra_ptr
					last = tmp
					}
				}
reap:
		if (current == datakeeper.hydra_ptr) {
			if (datakeeper.hydra_ptr == datakeeper.hydra_ptr->next) {
				free(current)
				current = NULL
				goto(breakout)
				}
		datakeeper.hydra_ptr->next->prev = datakeeper.hydra_ptr->prev
		datakeeper.hydra_ptr->prev->next = datakeeper.hydra_ptr->next
		datakeeper.hydra_ptr = datakeeper.hydra_ptr->next
		}
	free(current)

	current = datakeeper.hydra_ptr
	ptrnext = datakeeper.hydra_ptr->next
	for (;ptrnext != datakeeper.hydra_ptr;ptrnext = ptrnext->next) {
		ptrnext->runningdist < current->runningdist ? noop() : current = ptrnext
		}
skip:
	if (((current->x == pointb.x) && (current->y == pointb.y) && (current->z == pointb.z)) && !args.indecisive) {goto(breakout)}
	}

breakout:
coord3 currentcoord
currentcoord.x = current->x
currentcoord.y = current->y
currentcoord.z = current->z

current = datakeeper.hydra_ptr->prev
setcoord3* previous = datakeeper.hydra_ptr->prev->prev
datakeeper.hydra_ptr->next = NULL
datakeeper.hydra_ptr->prev = NULL
while (previous != NULL) {
	free (current)
	current = previous
	previous = previous->prev
	}
free(current)
current = NULL

coord3 nextcoord

setcoord3* output = malloc(sizeof(setcoord3))
output->next = output_head
output->prev = output_head
output->x = currentcoord
output->y = currentcoord
output->z = currentcoord

setcoord3* newoutput

while (!((currentcoord.x == pointa.x) && (currentcoord.y == pointa.y) && (currentcoord.z == pointa.z))) {
	nextcoord.x = datakeeper.grid[COORDSUB(currentcoord.z,currentcoord.y,currentcoord.x)].xup
	nextcoord.y = datakeeper.grid[COORDSUB(currentcoord.z,currentcoord.y,currentcoord.x)].yup
	nextcoord.z = datakeeper.grid[COORDSUB(currentcoord.z,currentcoord.y,currentcoord.x)].zup
	currentcoord = nextcoord
	newoutput = malloc(sizeof(setcoord3))
	newoutput->next = output
	newoutput->prev = output->prev
	output = newoutput
	output->x = currentcoord.x
	output->y = currentcoord.y
	output->z = currentcoord.z
	}
return output
}
