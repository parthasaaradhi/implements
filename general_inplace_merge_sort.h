#ifndef GENERAL_INPLACE_MERGE_SORT
#define GENERAL_INPLACE_MERGE_SORT

#include<stdlib.h>

#define MYCOPY(a,b,size) do { size_t __size = (size); char * __a = (a), *__b = (b); do { *__a = *__b; __a++; __b++; } while(--__size > 0); }while(0)

extern void gip_merge_sort(void* p, size_t n, size_t size,int (*compar) (const void*, const void*)) __nonnull ((1,4));

void internal_sorting(void* p, size_t l, size_t r, size_t size, int (*compar) (const void*, const void*)) {
	if(r-l == 1 || r-l==0)
		return;

	size_t s,m,f,i;
	void* temp;

	s=l;m=(l+r)/2;f=r;

	internal_sorting(p, s, m, size, compar);
	internal_sorting(p, m, r, size, compar);

	temp = malloc((r-l)*size);

	for(i=l;i<r;i++) {
		if(s == (l+r)/2) {
			MYCOPY(temp+(i-l)*size, p+m*size, size);
			m++;
		}
		else if(m == r) {
			MYCOPY(temp+(i-l)*size, p+s*size, size);
			s++;
		}
		else if((*compar) (p+s*size, p+m*size) <= 0) {
			MYCOPY(temp+(i-l)*size, p+s*size, size);
			s++;
		}
		else {
			MYCOPY(temp+(i-l)*size, p+m*size, size);
			m++;
		}
	}
	for(i=l;i<r;i++)
		MYCOPY(p+i*size, temp+(i-l)*size, size);
	free(temp);
	return;
}

void gip_merge_sort(void* p, size_t n, size_t size,int (*compar) (const void*, const void*)) {
	internal_sorting(p, 0, n, size, compar);
}
#endif
