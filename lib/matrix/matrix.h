#include<stdlib.h>
#include "../fraction/fraction.h"

struct matrix {
	int rows;
	int columns;
	struct fraction** f;
};

void matrix_print(struct matrix* m);
struct matrix* matrix_create_column(int r, int* columns);
struct matrix* matrix_create(int r, int c, int** array);
int matrix_solve_linear_equations(struct matrix* A, struct matrix* B);
int transform(struct matrix* A, struct matrix* B, int diagonal);
int reverse_transform(struct matrix* A, struct matrix* B, int diagonal);
void matrix_destroy(struct matrix* m);
