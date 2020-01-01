ucoord3list * bline (ucoord3 p1, ucoord3 p2) {
float deltax = p2[0] - p1[0];
int signx = sgnf(deltax);
float deltay = p2[1] - p1[1];
int signy = sgnf(deltay);
float deltaz = p2[2] - p1[2];
int signz = sgnf(deltaz);
ucoordlist3 * output = ucoordlist3__new(p1);
ucoordlist3 * output_tail = output;

if ( (fabs(deltay) ≤ 1.0) && (fabs(deltaz) ≤ 1.0) ) {
	float deltaerrory = fabs(deltay / deltax);
	float errory = 0.0;
	float deltaerrorz = fabs(deltaz / deltax);
	float errorz = 0.0;
	int x,y,z;
	forever {
		output_tail = ucoordlist3__tail_push_int(output_tail,x,y,z);
		errory += deltaerrory;
		if (errory ≥ 0.5) {
			y += signy;
			errory -= 1.0;}
		errorz += deltaerrorz;
		if (errorz ≥ 0.5) {
			z += signz;
			errorz -= 1.0;}
		x += signx;

		/*conditional exits below*/
		if (signx < 0) {
			if (x ≤ p2[0]) {return output}
		} else {
			if (x ≥ p2[0] {return output}
		}
	}

/*same for y, z*/
