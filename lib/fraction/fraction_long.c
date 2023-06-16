#include<stdio.h>
#include<stdlib.h>
#include "../gcd/gcd.h"

#include "fraction_long.h" /* Implementations */

long long abs_long(long long x) {
	return x>=0? x : -1*x;
}

void fraction_print(struct fraction* f) {
	printf("%lld/%lld", f->numerator, f->denominator);
}

struct fraction* fraction_create(long long n) {
	struct fraction* f = (struct fraction*) malloc(sizeof(struct fraction));
	f->numerator = n;
	f->denominator = 1;
	return f;
}

void fraction_set(struct fraction* f, long long n) {
	f->numerator = n;
	f->denominator = 1;
}

void fraction_copy(struct fraction* dest, struct fraction* src) {
	dest->numerator = src->numerator;
	dest->denominator = src->denominator;
}

void fraction_simplify(struct fraction* f) {
	long long g;
	if(f->numerator == 0)
		f->denominator = 1;
	else {
		g = gcd_long(abs_long(f->numerator), f->denominator);
		f->numerator = f->numerator/g;
		f->denominator = f->denominator/g;
	}
}

int fraction_inverse(struct fraction* result, struct fraction* f) {
	if(f->numerator == 0) {
		printf("ERROR: Fraction: Cannot Invert 0\n");
		return 1;
	} else {
		result->denominator = abs_long(f->numerator);
		result->numerator = f->numerator>0? abs_long(f->denominator) : -1*abs_long(f->denominator);
		return 0;
	}
}

void fraction_add(struct fraction* dest ,struct fraction* left, struct fraction* right) {
	long long g;
	g = gcd_long(right->denominator, left->denominator);
	dest->numerator = left->numerator*(right->denominator/g) + right->numerator*(left->denominator/g);
	dest->denominator = left->denominator*(right->denominator/g);
	fraction_simplify(dest);
}

void fraction_subtract(struct fraction* dest, struct fraction* left, struct fraction* right) {
	dest->numerator = left->numerator*right->denominator - right->numerator*left->denominator;
	dest->denominator = left->denominator*right->denominator;
	fraction_simplify(dest);
}

void fraction_mult(struct fraction* dest, struct fraction* left, struct fraction* right) {
	dest->numerator = left->numerator*right->numerator;
	dest->denominator = left->denominator*right->denominator;
	fraction_simplify(dest);
}

int fraction_divide(struct fraction* dest, struct fraction* left, struct fraction* right) {
	if(right->numerator == 0) {
		printf("ERROR: Fraction: Cannot divide by 0\n");
		return 1;
	} else {
		dest->numerator = left->numerator * right->denominator;
		dest->denominator = left->denominator * right->numerator;
		fraction_simplify(dest);
		return 0;
	}
}
