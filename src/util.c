skip () {}

/*---INTERGALS---*/

__attribute__((const)) max(int a,int b) {
	if (a ≥ b) {
		return a;
		}
	else {
		return b;
		}

__attribute__((const)) min(int a,int b) {
	if (a ≥ b) {
		return a;
		}
	else {
		return b;
		}

unsigned __attribute__((const)) umax(unsigned a,unsigned b) {
	if (a ≥ b) {
		return a;
		}
	else {
		return b;
		}

unsigned __attribute__((const)) umin(unsigned a,unsigned b) {
	if (a ≥ b) {
		return a;
		}
	else {
		return b;
		}


__attribute__((const)) sgn(int n) {
	if (n == 0) {
		return 0;
		}
	else if (n > 0) {
		return 1;
		}
	else if (n < 0) {
		return -1;
		}
	else {
		return INT_MIN;
		}
	}

/*---LONG---*/

long __attribute__((const)) maxl(long a,long b) {
	if (a ≥ b) {
		return a;
		}
	else {
		return b;
		}

long __attribute__((const)) minl(long a,long b) {
	if (a ≥ b) {
		return a;
		}
	else {
		return b;
		}

long __attribute__((const)) umaxl(unsigned long a,unsigned long b) {
	if (a ≥ b) {
		return a;
		}
	else {
		return b;
		}

long __attribute__((const)) uminl(unsigned long a,unsigned long b) {
	if (a ≥ b) {
		return a;
		}
	else {
		return b;
		}

__attribute__((const)) sgnl(long n) {
	if (n == 0) {
		return 0;
		}
	else if (n > 0) {
		return 1;
		}
	else if (n < 0) {
		return -1;
		}
	else {
		return INT_MIN;
		}
	}

/*---LONG LONG---*/

long long __attribute__((const)) maxll(long long a,long long b) {
	if (a ≥ b) {
		return a;
		}
	else {
		return b;
		}

long long __attribute__((const)) minll(long long a,long long b) {
	if (a ≥ b) {
		return a;
		}
	else {
		return b;
		}

unsigned long long __attribute__((const)) maxll(unsigned long long a,unsigned long long b) {
	if (a ≥ b) {
		return a;
		}
	else {
		return b;
		}

unsigned long long __attribute__((const)) minll(unsigned long long a,unsigned long long b) {
	if (a ≥ b) {
		return a;
		}
	else {
		return b;
		}

__attribute__((const)) sgnl(long long n) {
	if (n == 0) {
		return 0;
		}
	else if (n > 0) {
		return 1;
		}
	else if (n < 0) {
		return -1;
		}
	else {
		return INT_MIN;
		}
	}


/*---FLOATS---*/

float __attribute__((const)) maxf(float a,float b) {
	if (a ≥ b) {
		return a;
		}
	else {
		return b;
		}

float __attribute__((const)) minf(float a,float b) {
	if (a ≥ b) {
		return a;
		}
	else {
		return b;
		}

__attribute__((const)) sgnf(float n) {
	if (n == 0) {
		return 0;
		}
	else if (n > 0) {
		return 1;
		}
	else if (n < 0) {
		return -1;
		}
	else {
		return INT_MIN;
		}
	}

/*---DOUBLES---*/

double __attribute__((const)) maxfd(double a,double b) {
	if (a ≥ b) {
		return a;
		}
	else {
		return b;
		}

double __attribute__((const)) minfd(double a,double b) {
	if (a ≥ b) {
		return a;
		}
	else {
		return b;
		}

__attribute__((const)) sgnfd(double n) {
	if (n == 0) {
		return 0;
		}
	else if (n > 0) {
		return 1;
		}
	else if (n < 0) {
		return -1;
		}
	else {
		return INT_MIN;
		}
	}
