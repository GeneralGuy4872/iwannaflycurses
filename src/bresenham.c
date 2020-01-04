ucoord3list * bline (ucoord3 p1, ucoord3 p2) {
float deltax = p2[0] - p1[0];
int signx = sgnf(deltax);
float deltay = p2[1] - p1[1];
int signy = sgnf(deltay);
float deltaz = p2[2] - p1[2];
int signz = sgnf(deltaz);
ucoordlist3 * output = ucoordlist3__new(p1);
ucoordlist3 * output_tail = output;

if ( (deltax == 0.0) && (deltay == 0.0) && (deltaz == 0.0) ) {
	return output;
	}

else if ( (deltay == 0.0) && (deltaz == 0.0) ) {
	for (int x = p1[0];x != p2[0];x += signx) {
		output_tail = ucoordlist3__tail_push_int(output_tail,x,p1[1],p1[2]);
		}
	return output;
	}

else if ( (deltax == 0.0) && (deltaz == 0.0) ) {
	for (int y = p1[1];y != p2[1];y += signy) {
		output_tail = ucoordlist3__tail_push_int(output_tail,p1[0],y,p1[2]);
		}
	return output;
	}

else if ( (deltax == 0.0) && (deltay == 0.0) ) {
	for (int z = p1[2];z != p2[2];z += signz) {
		output_tail = ucoordlist3__tail_push_int(output_tail,p1[0],p1[1],z);
		}
	return output;
	}

/* handling for single zeros here */

else if ( (fabs(deltax) == 1.0) && (fabs(deltay) == 1.0) && (fabs(deltaz) == 1.0) ) {
	int x = p1[0];
	int y = p1[1];
	int z = p1[2];
	while (x != p2[0]) { //for 45 degree angles, only one needs to be checked
		x += signx;
		y += signy;
		z += signz;
		output_tail = ucoordlist3__tail_push_int(output_tail,x,y,z);
		}
	return output;
	}

else if ( (fabs(deltay) ≤ 1.0) && (fabs(deltaz) ≤ 1.0) ) {
	float deltaerrory = fabs(deltay / deltax);
	float errory = 0.0;
	float deltaerrorz = fabs(deltaz / deltax);
	float errorz = 0.0;
	int x = p1[0];
	int y = p1[1];
	int z = p1[2];
	forever {
		errory += deltaerrory;
		if (errory ≥ 0.5) {
			y += signy;
			errory -= 1.0;}
		errorz += deltaerrorz;
		if (errorz ≥ 0.5) {
			z += signz;
			errorz -= 1.0;}
		x += signx;
		output_tail = ucoordlist3__tail_push_int(output_tail,x,y,z);

		/*conditional exits below*/
		if (signx < 0) {
			if (x ≤ p2[0]) {return output}
		} else {
			if (x ≥ p2[0]) {return output}
		}
	}

/*same for y, z*/
