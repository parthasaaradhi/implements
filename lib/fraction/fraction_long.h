#ifndef FRACTION_H
#define FRACTION_H
#include<stdio.h>
#include<stdlib.h>
struct fraction {
	long long numerator;
	long long denominator;
};

void fraction_print(struct fraction* f);
struct fraction* fraction_create(long long n);
void fraction_set(struct fraction* f, long long n);
void fraction_copy(struct fraction* dest, struct fraction* src);
int fraction_inverse(struct fraction* result, struct fraction* f);
void fraction_simplify(struct fraction* f);
void fraction_add(struct fraction* dest, struct fraction* left, struct fraction* right);
void fraction_subtract(struct fraction* dest, struct fraction* left, struct fraction* right);
void fraction_mult(struct fraction* dest, struct fraction* left, struct fraction* right);
int fraction_divide(struct fraction* dest, struct fraction* left, struct fraction* right);
#endif
