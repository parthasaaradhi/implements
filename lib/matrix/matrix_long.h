#include<stdlib.h>
#include "../fraction/fraction_long.h"

struct matrix {
	int rows;
	int columns;
	struct fraction** f;
};

void matrix_print(struct matrix* m);
struct matrix* matrix_create_column(int r, long long* columns);
struct matrix* matrix_create(int r, int c, long long** array);
int matrix_solve_linear_equations(struct matrix* A, struct matrix* B);
int transform(struct matrix* A, struct matrix* B, int diagonal);
int reverse_transform(struct matrix* A, struct matrix* B, int diagonal);
void matrix_destroy(struct matrix* m);
