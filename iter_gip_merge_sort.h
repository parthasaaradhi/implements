#ifndef ITER_GIP_MERGE_SORT
#define ITER_GIP_MERGE_SORT

#include<stdlib.h>
#include<string.h>

void iter_gip_merge_sort(void* p, size_t n, size_t size,int (*compar) (const void*, const void*))
{
	size_t iter,cut,i,m,left,right,f;
	void* temp;

	temp = malloc(n*size);
	memcpy(temp, p, n*size);

	cut = 2;
	while(cut<2*n) {
		iter = 0;
		while(iter<n) {
			left = iter;
			f = (left+cut)>n ? n : left+cut;
			m = (left+cut/2)>n ? n : left+cut/2;
			i = left;
			right = m;
			while(left<m && right<f) {
				if((*compar)(p+left*size, p+right*size) <=0) {
					memcpy(temp+i*size, p+left*size, size);
					left++;
				} else {
					memcpy(temp+i*size, p+right*size, size);
					right++;
				}
				i++;
			}
			while(left<m) {
				memcpy(temp+i*size, p+left*size, size);
				left++;
				i++;
			}

			while(right<f) {
				memcpy(temp+i*size, p+right*size, size);
				right++;
				i++;
			}
			iter = iter+cut;
		}
		memcpy(p, temp, n*size);
		cut = cut*2;
	}
	free(temp);
}
#endif
