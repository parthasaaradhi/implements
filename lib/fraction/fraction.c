#include<stdio.h>
#include<stdlib.h>
#include "../gcd/gcd.h"

#include "fraction.h" /* Implementations */

void fraction_print(struct fraction* f) {
	printf("%d/%d", f->numerator, f->denominator);
}

struct fraction* fraction_create(int n) {
	struct fraction* f = (struct fraction*) malloc(sizeof(struct fraction));
	f->numerator = n;
	f->denominator = 1;
	return f;
}

void fraction_set(struct fraction* f, int n) {
	f->numerator = n;
	f->denominator = 1;
	return;
}

void fraction_copy(struct fraction* dest, struct fraction* src) {
	dest->numerator = src->numerator;
	dest->denominator = src->denominator;
	return;
}

void fraction_simplify(struct fraction* f) {
	int g;
	if(f->numerator == 0) {
		f->numerator = 0;
		f->denominator = 1;
		return;
	}
	g = gcd_int(abs(f->numerator), f->denominator);
	f->numerator = f->numerator/g;
	f->denominator = f->denominator;
	return;
}

int fraction_inverse(struct fraction* result, struct fraction* f) {
	int n,d;
	if(f->numerator == 0) {
		printf("ERROR: Fraction: Cannot Invert 0\n");
		return 1;
	}
	n = f->numerator;
	d = f->denominator;
	result->denominator = n>0 ? n : -1*n;
	result->numerator = n>0 ? d : -1*d;
	return 0;
}

void fraction_add(struct fraction* dest ,struct fraction* left, struct fraction* right) {
	int g,ln,ld,rn,rd;
	ln = left->numerator;
	ld = right->denominator;
	rn = right->numerator;
	rd = right->denominator;
	g = gcd_int(ld, rd);
	dest->numerator = ln*(rd/g) + rn*(ld/g);
	dest->denominator = (ld/g)*rd;
	fraction_simplify(dest);
	return;
}

void fraction_subtract(struct fraction* dest, struct fraction* left, struct fraction* right) {
	int g,ln,ld,rn,rd;
	ln = left->numerator;
	ld = left->denominator;
	rn = right->numerator;
	rd = right->denominator;
	g = gcd_int(ld, rd);
	dest->numerator = ln*(rd/g) - rn*(ld/g);
	dest->denominator = (ld/g)*rd;
	fraction_simplify(dest);
	return;
}

void fraction_mult(struct fraction* dest, struct fraction* left, struct fraction* right) {
	int g,ln,ld,rn,rd;
	ln = left->numerator;ld = left->denominator;
	rn = right->numerator;rd = right->denominator;
	g = gcd_int(abs(ln), rd);
	ln = ln/g;
	rd = rd/g;
	g = gcd_int(abs(rn), ld);
	rn = rn/g;
	ld = ld/g;
	dest->numerator = ln*rn;
	dest->denominator = ld*rd;
	fraction_simplify(dest);
	return;
}

int fraction_divide(struct fraction* dest, struct fraction* left, struct fraction* right) {
	int g,ln,ld,rn,rd;
	if(right->numerator == 0) {
		printf("ERROR: Fraction: Cannot divide by 0\n");
		return 1;
	}
	ln = left->numerator; ld = left->denominator;
	rn = right->numerator; rd = right->denominator;
	g = gcd_int(abs(ln), abs(rn));
	ln = ln/g;
	rn = rn/g;
	g = gcd_int(ld, rd);
	ld = ld/g;
	rd = rd/g;
	dest->numerator = ln*rd;
	dest->denominator = rn*ld;
	fraction_simplify(dest);
	return 0;
}
