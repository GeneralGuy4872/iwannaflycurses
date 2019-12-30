#ifndef UTIL_H_REENTERANT
#define UTIL_H_REENTERANT 1
skip () {}

extern signed max(signed a,signed b);
extern signed min(signed a,signed b);
extern unsigned umax(unsigned a,unsigned b);
extern unsigned umin(unsigned a,unsigned b);
extern int sgn(signed n);

extern signed long maxl(signed long a,signed long b);
extern signed long minl(signed long a,signed long b);
extern unsigned long umaxl(unsigned long a,unsigned long b);
extern unsigned long uminl(unsigned long a,unsigned long b);
extern int sgnl(signed long n);

extern signed long long maxll(signed long long a,signed long long b);
extern signed long minll(signed long long a,signed long long b);
extern unsigned long long umaxll(unsigned long long a,unsigned long long b);
extern unsigned long long uminll(unsigned long long a,unsigned long long b);
extern int sgnll(signed long long n);

extern float maxf(float a,float b);
extern float minf(float a,float b);
extern int sgnf(float n);

extern double maxfd(double a,double b);
extern double minfd(double a,double b);
extern int sgnfd(float n);
#endif
