#include<stdio.h>
#include<stdlib.h>
#include "../../lib/fraction/fraction.h"

int main() {
	int x;
	struct fraction *l,*r;
	l = fraction_create(0);
	r = fraction_create(5);
	fraction_inverse(l,l);
	fraction_inverse(r,r);
	printf("l is : ");
	fraction_print(l);
	printf("\n");
	fraction_subtract(l,l,r);
	printf("After adding 1/5, l is : ");
	fraction_print(l);
	printf("\n");
	fraction_divide(l,l,r);
	printf("After dividing by 1/5 l is : ");
	fraction_print(l);
	printf("\n");
	free(l);
	free(r);
	return 0;
}
