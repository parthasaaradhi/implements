#include<stdio.h>
#include<stdlib.h>
#include "../../ansi_iter_gip_merge_sort.h"

int int_cmp(const void *a, const void *b) {
	const int *left = (int*) a;
	const int *right = (int*) b;
	if( (*left) < (*right))
		return -1;
	else if((*left) > (*right))
		return 1;
	else
		return 0;
}

int main() {
	int i;
	int a[10] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
	ansi_iter_gip_merge_sort(a, 10, sizeof(int), int_cmp);
	for(i=0;i<10;i++)
		printf("%d ", a[i]);
	printf("\n");
	return 0;
}
