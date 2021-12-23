#include<stdio.h>
#include<stdlib.h>
#include "../../general_inplace_merge_sort.h"

int long_long_cmp(const void *a, const void *b) {
	long long *left  = (long long *) a;
	long long *right = (long long *) b;
	if( (*left) < (*right))
		return -1;
	else if((*left) > (*right))
		return 1;
	else
		return 0;
}

int main() {
	int i;
	long long a[10] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
	gip_merge_sort(a, 10, sizeof(long long), long_long_cmp);
	for(i=0;i<10;i++)
		printf("%lld ", a[i]);
	printf("\n");
	return 0;
}
