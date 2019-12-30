ucoord3list * attractorline(ucoord3 p1, ucoord3 p2,int glyph) {

x = p2[0] - p1[0];
y = p2[1] - p1[1];
z = p2[2] - p1[2];
euclid = sqrt((x * x) + (y * y) + (z * z));

ucoord3list * head = ucoord3list(p1);
ucoord3list * tail = ucoord3list(p2);
head->next = tail;
tail->prev = head;

/*for*/{
	int i = 1;
	int n = 2;	
	struct setcoord3 * oldprev = head;
	struct setcoord3 * oldnext = tail;
		
	while ((n < euclid) && (oldprev->next != NULL)) {
		/*do*/
		oldnext = oldprev->next;
		struct setcoord3 * new = malloc(sizeof(struct setcoord3));
		oldprev->next = new;
		oldnext->prev = new;
		new->prev = oldprev;
		new->next = oldnext;
		new->x = (oldprev->x + oldnext->x) / 2;
		new->y = (oldprev->y + oldnext->y) / 2;
		/*and then do*/
		oldprev = oldnext;
		n += i;
		i++;
		}
	}
return head;
}


/*unfinished*/
breshamline(char args,ucoord3 p1,ucoord3 p2,int glyph)
	int deltx = p1[0] - p0[0];
	int xdir = sgn(deltx);
	if (xdir < 0) {
		deltx *= -1;
		}
	int delty = p1[1] - p0[1];
	int ydir = sgn(delty);
	if (ydir < 0) {
		delty *= -1;
		}
	int deltz = p1[2] - p0[2];
	int zdir = sgn(deltz);
	if (zdir < 0) {
		deltz *= -1;
		}
	
	/*HR*/

	if ((abs(delty) ≤ 1) && (abs(deltz) ≤ 1)) {
		goto(goforx);
		}
	else if ((abs(deltx) ≤ 1) && (abs(deltz) ≤ 1)) {
		goto(gofory);
		}
	else if ((abs(deltx) ≤ 1) && (abs(delty) ≤ 1)) {
		goto(goforz);
		}

	/*HR*/

	goforx:
	/*for*/{
	int n = 0;
	int x = p0[0];

	while ((x != p1[0]) && (n < 100)) {
		
	/*and then*/
	x += xdir;
	n++;
	}