#include<stdlib.h>
#include "gcd.h" /* Implementations */
int gcd_int(int a, int b) {
	if(a==0) return b==0? 1 : b;
	return a>b? gcd_int(b,a) : gcd_int(b%a, a);
}

long long gcd_long(long long a, long long b) {
	if(a==0) return b==0? 1 : b;
	return a>b? gcd_long(b,a) : gcd_long(b%a, a);
}
