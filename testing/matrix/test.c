#include<stdio.h>
#include<stdlib.h>
#include "../../lib/matrix/matrix_long.h"
#include "../../lib/fraction/fraction_long.h"
long long power(long long n, long long x) {
	long long ans=1;
	while(x!=0) {
		ans = ans*n;
		x--;
	}
	return ans;
}

long long given_polynomial(long long n) {
	return (power(n, 11) + 1)/(n+1);
}

int main() {
	long long i,j;
	long long* actual_result;
	long long** exponents; 
	struct matrix *A, *B;
	struct fraction *ans, *temp;
	
	actual_result = malloc(11*sizeof(long long));
	for(i=0;i<11;i++) actual_result[i] = given_polynomial(i);
	exponents = malloc(11*sizeof(long long*));
	for(i=0;i<11;i++) {
		exponents[i] = malloc(11*sizeof(long long));
		exponents[i][0] = 1;
		for(j=1;j<11;j++)
			exponents[i][j] = exponents[i][j-1]*i;
	}
	B = matrix_create_column(11, actual_result);
	matrix_print(B);
	matrix_destroy(B);
	for(i=0;i<10;i++) {
		B = matrix_create_column(i+1, actual_result);
		A = matrix_create(i+1, i+1, exponents);
		matrix_solve_linear_equations(A, B);
		//matrix_print(A);
		//matrix_print(B);
		ans = malloc(sizeof(struct fraction));
		fraction_set(ans, 0);
		for(j=0;j<i+1;j++) {
			temp = malloc(sizeof(struct fraction));
			fraction_set(temp, power(i+1, j));
			fraction_multiply(temp, temp, &(B->f[j][0]));
			fraction_add(ans, ans, temp);
			free(temp);
		}
		temp = malloc(sizeof(struct fraction));
		fraction_set(temp, actual_result[i+1]);
		fraction_subtract(ans, temp, ans);
		fraction_print(ans);
		printf("\n");
		free(ans);
		matrix_destroy(A);
		matrix_destroy(B);
	}
	return 0;
}
