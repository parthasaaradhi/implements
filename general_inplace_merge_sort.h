#ifndef GENERAL_INPLACE_MERGE_SORT
#define GENERAL_INPLACE_MERGE_SORT

#include<stdlib.h>
#include<string.h>

void gip_merge_sort(void* p, size_t n, size_t size,int (*compar) (const void*, const void*)) {	
	void* temp;
	temp = malloc(n*size);

	void internal_sorting(size_t l, size_t r) {
		if(r-l == 1 || r-l==0)
			return;

		size_t s,m,f,i;

		s=l;m=(l+r)/2;f=r;

		internal_sorting(s, m);
		internal_sorting(m, r);

		for(i=l;i<r;i++) {
			if(s == (l+r)/2) {
				memcpy(temp+i*size, p+m*size, size);
				m++;
			}
			else if(m == r) {
				memcpy(temp+i*size, p+s*size, size);
				s++;
			}
			else if((*compar) (p+s*size, p+m*size) <= 0) {
				memcpy(temp+i*size, p+s*size, size);
				s++;
			}
			else {
				memcpy(temp+i*size, p+m*size, size);
				m++;
			}
		}

		memcpy(p+l*size, temp+l*size, (r-l)*size);
		return;
	}
	internal_sorting(0, n);
	free(temp);
}
#endif
