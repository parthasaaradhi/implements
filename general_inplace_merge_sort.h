#ifndef GENERAL_INPLACE_MERGE_SORT
#define GENERAL_INPLACE_MERGE_SORT

#include<stdlib.h>

#define MYCOPY(a,b,size) do { size_t __size = (size); char * __a = (a), *__b = (b); do { *__a = *__b; __a++; __b++; } while(--__size > 0); }while(0)

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
				MYCOPY(temp+i*size, p+m*size, size);
				m++;
			}
			else if(m == r) {
				MYCOPY(temp+i*size, p+s*size, size);
				s++;
			}
			else if((*compar) (p+s*size, p+m*size) <= 0) {
				MYCOPY(temp+i*size, p+s*size, size);
				s++;
			}
			else {
				MYCOPY(temp+i*size, p+m*size, size);
				m++;
			}
		}
		for(i=l;i<r;i++)
			MYCOPY(p+i*size, temp+i*size, size);
		return;
	}
	internal_sorting(0, n);
	free(temp);
}
#endif
