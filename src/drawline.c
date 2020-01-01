ucoord3list * attractorline(ucoord3 p1, ucoord3 p2) {

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
