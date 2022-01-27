#include<stdio.h>
#include<stdlib.h>
#include "../../ansi_iter_gip_merge_sort.h"
struct mp {
	int x;
	int y;
};

int compare_mps(const void* left, const void* right) {
	const struct mp *a = (const struct mp *) left;
	const struct mp *b = (const struct mp *) right;
	if((*a).x < (*b).x)
		return -1;
	else if((*a).x > (*b).x)
		return 1;
	else {
		if((*a).y < (*b).y)
			return -1;
		else if((*a).y > (*b).y)
			return 1;
		else
			return 0;
	}
}

int main() {
	struct mp* l;
	int i;
	l = malloc(10*sizeof(struct mp));
	for(i=0;i<10;i++) {
		l[i].x = i%3;
		l[i].y = i;
	}
	printf("Pre:\t");
	for(i=0;i<10;i++)
		printf("%d %d\t", l[i].x, l[i].y);
	printf("\nPost:\t");
	ansi_iter_gip_merge_sort(l, 10, sizeof(struct mp), compare_mps);
	for(i=0;i<10;i++) {
		printf("%d %d\t", l[i].x, l[i].y);
	}
	printf("\n");
	return 0;
}
