#include<stdlib.h>
#include "matrix_long.h"

void matrix_print(struct matrix* m) {
	int i,j;
	printf("Printing Matrix\n");
	for(i=0;i<m->rows;i++) {
		printf("Row %d...\t", i);
		for(j=0;j<m->columns;j++) {
			fraction_print(&(m->f[i][j]));
			printf(" ");
		}
		printf("\n");
	}
	printf("End Printing\n");
}

struct matrix* matrix_create_column(int r, long long* columns) {
	int i;
	struct matrix* m = (struct matrix *) malloc(sizeof(struct matrix));
	m->rows = r;
	m->columns = 1;
	m->f = malloc(r*sizeof(struct fraction *));
	for(i=0;i<r;i++) {
		m->f[i] = malloc(sizeof(struct fraction));
		fraction_set(&(m->f[i][0]), columns[i]);
	}
	return m;
}

struct matrix* matrix_create(int r, int c, long long** array) {
	int i,j;
	struct matrix* m = (struct matrix *) malloc(sizeof(struct matrix));
	m->rows = r;
	m->columns = c;
	m->f = malloc(r*sizeof(struct fraction *));
	for(i=0;i<r;i++)
		m->f[i] = malloc(c*sizeof(struct fraction));
	for(i=0;i<r;i++)
		for(j=0;j<c;j++)
			fraction_set(&(m->f[i][j]), array[i][j]);
	return m;
}

int transform(struct matrix* A, struct matrix* B, int diagonal) {
	int i,j;
	struct fraction *inverse, *temp, *nullifier;

	inverse = (struct fraction*) malloc(sizeof(struct fraction));
	if(fraction_inverse(inverse, &(A->f[diagonal][diagonal])) != 0) {
		free(inverse);
		return 1;
	}

	for(j=diagonal;j<A->columns;j++)
		fraction_mult(&(A->f[diagonal][j]), &(A->f[diagonal][j]), inverse);
	fraction_mult(&(B->f[diagonal][0]), &(B->f[diagonal][0]), inverse);
	free(inverse);

	temp = (struct fraction*) malloc(sizeof(struct fraction));
	nullifier = (struct fraction*) malloc(sizeof(struct fraction));
	for(i=diagonal+1;i<A->rows;i++) {
		fraction_copy(nullifier, &(A->f[i][diagonal]));

		fraction_mult(temp, nullifier, &(B->f[diagonal][0]));
		fraction_subtract(&(B->f[i][0]), &(B->f[i][0]), temp);

		for(j=0;j<A->columns;j++) {
			fraction_mult(temp, nullifier, &(A->f[diagonal][j]));
			fraction_subtract(&(A->f[i][j]), &(A->f[i][j]), temp);
		}
	}
	free(nullifier);
	free(temp);
	return 0;
}

int reverse_transform(struct matrix* A, struct matrix* B, int diagonal) {
	int i,j;
	struct fraction *inverse, *temp, *nullifier;

	inverse = (struct fraction*) malloc(sizeof(struct fraction));
	if(fraction_inverse(inverse, &(A->f[diagonal][diagonal])) != 0) {
		free(inverse);
		return 1;
	}

	for(i=0;i<A->rows;i++)
		fraction_mult(&(A->f[diagonal][i]), &(A->f[diagonal][i]), inverse);

	fraction_mult(&(B->f[diagonal][0]), &(B->f[diagonal][0]), inverse);
	free(inverse);

	temp = (struct fraction*) malloc(sizeof(struct fraction));
	nullifier = (struct fraction*) malloc(sizeof(struct fraction));
	for(i=diagonal-1;i>=0;i--) {
		fraction_copy(nullifier, &(A->f[i][diagonal]));
		fraction_mult(temp, nullifier, &(B->f[diagonal][0]));
		fraction_subtract(&(B->f[i][0]), &(B->f[i][0]), temp);

		for(j=0;j<A->columns;j++) {
			fraction_mult(temp, nullifier, &(A->f[diagonal][j]));
			fraction_subtract(&(A->f[i][j]), &(A->f[i][j]), temp);
		}
	}
	free(nullifier);
	free(temp);
	return 0;
}

int matrix_solve_linear_equations(struct matrix* A, struct matrix* B) {
	int i;
	if(A->rows != A->columns || A->rows != B->rows) return 1;
	for(i=0;i<A->rows-1;i++) {
		if(transform(A, B, i) != 0) return 1;
	}
	for(i=A->rows-1;i>0;i--) {
		if(reverse_transform(A, B, i) != 0) return 1;
	}
	return 0;
}

void matrix_destroy(struct matrix* m) {
	int i;
	for(i=0;i<m->rows;i++)
		free(m->f[i]);
	free(m->f);
	free(m);
	return;
}
