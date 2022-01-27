#ifndef ANSI_ITER_GIP_MERGE_SORT
#define ANSI_ITER_GIP_MERGE_SORT

#include<stdlib.h>
#include<string.h>

void merge(char* p, char* temp, size_t l, size_t r, size_t f, size_t size, int(*compar) (const void*, const void*)) {
	if(r == f) return;
	size_t i,left,right;
	i = l;
	left = l; right = r;
	while(left<r && right<f) {
		if((*compar)(p+left*size, p+right*size) <=0) {
			memcpy(temp+i*size, p+left*size, size);
			left++;
		} else {
			memcpy(temp+i*size, p+right*size, size);
			right++;
		}
		i++;
	}

	while(left<r) {
		memcpy(temp+i*size, p+left*size, size);
		left++;
		i++;
	}

	while(right<f) {
		memcpy(temp+i*size, p+right*size, size);
		right++;
		i++;
	}
}

void ansi_iter_gip_merge_sort(void* p, size_t n, size_t size,int (*compar) (const void*, const void*))
{
	size_t i,cut,l,r,f;
	void* temp = malloc(n*size);
	cut=2;
	while(cut<2*n) {
		i=0;
		while(i<n) {
			l = i;
			f = (i+cut)>n ? n : i+cut;
			r = (l+cut/2)>n ? n : l+cut/2;
			merge((char*)p, (char*)temp, l, r, f, size, compar);
			i= i+cut;
		}
		memcpy(p, temp, n*size);
		cut = cut*2;
	}
	free(temp);
}
#endif
