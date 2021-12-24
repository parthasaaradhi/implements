#include<stdio.h>
#include<stdlib.h>
#include "../../graph.h"

int main() {
	int n,i,x,y,e;
	struct Graph* g;
	printf("Number of verticies: ");
	scanf("%d", &n);
	g = get_new_graph(n);
	printf("Number of Edges: ");
	scanf("%d", &e);
	printf("All verticies are numbered from 0 to %d\n", n-1);
	printf("Please input the pair of verticies keeping the above numbering in mind\n");
	for(i=0;i<e;i++) {
		scanf("%d %d", &x, &y);
		if(x<0 || x>=n || y<0 || y>=n || x==y) {
			printf("ERROR : Wrong Input Exit Program.\n");
			destroy_graph(&g);
			return 1;
		}
		add_undir_edge(x,y,g);
	}
	print_graph_cc(g);
	destroy_graph(&g);
	return 0;
}
