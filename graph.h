#ifndef GRAPH_H
#define GRAPH_H
#include<stdlib.h>

struct connected_component {
	int id;
	int size;
};

struct Node {
	char state;
	int id;
	int children_size;
	int* children;
	struct Node* master;
	struct connected_component* cc;
};

struct Graph {
	int size;
	struct Node* verticies;
};

/*-------------------Helper Functions-----Declarations----------*/
struct Graph* get_new_graph(int n);
struct Node* master_recurse(struct Node* node);
struct Node* get_true_master_vertex(int i, struct Graph* g);
struct Node* get_true_master(struct Node* node);
void add_undir_edge(int l, int r, struct Graph* g);
void add_dir_edge(int parent, int child, struct Graph* g);
void connect_two_verticies(int a, int b, struct Graph* g);
void connect_two_nodes(struct Node* a, struct Node* b);
void destroy_graph(struct Graph** g_pointer);
void print_graph_cc(struct Graph* g);
void dsu_print(int root, struct Graph* g);
/**--------------------------------------------Implementations---*/

struct Graph* get_new_graph(int n) {
	int i;
	struct Graph* g = malloc(sizeof(struct Graph));
	g->size = n;
	g->verticies = malloc(g->size*sizeof(struct Node));
	for(i=0;i<g->size;i++) {
		g->verticies[i].id = i;
		g->verticies[i].children_size = 0;
		g->verticies[i].children = malloc(0);
		g->verticies[i].master = &(g->verticies[i]);
		g->verticies[i].cc = malloc(sizeof(struct connected_component));
		g->verticies[i].cc->id = i;
		g->verticies[i].cc->size = 1;
		g->verticies[i].state = 'n';
	}
	return g;
}

void dsu_print(int root, struct Graph* g) {
	if(g->verticies[root].state == 'v')
		return;
	printf("%d ", root);
	g->verticies[root].state = 'v';
	int i;
	for(i=0;i<g->verticies[root].children_size;i++)
		dsu_print(g->verticies[root].children[i], g);
}

void print_graph_cc(struct Graph* g) {
	printf("Printing Connected Components of Graph\n");
	int i;
	for(i=0;i<g->size;i++) {
		if(get_true_master_vertex(i,g) == &(g->verticies[i])) {
			printf("Connected Component Id :%d\t", g->verticies[i].cc->id);
			dsu_print(i, g);
			printf("\n");
		}
	}
	for(i=0;i<g->size;i++)
		g->verticies[i].state = 'n';
}

struct Node* get_true_master_vertex(int i, struct Graph* g) {
	return get_true_master(&(g->verticies[i]));
}

struct Node* get_true_master(struct Node* node) {
	// Sort of Dynamic memorization... To reduce time on search for masters.
	node->master = master_recurse(node);
	return node->master;
}

struct Node* master_recurse(struct Node* node) {
	if(node->master == node)
		return node;
	else
		return master_recurse(node->master);
}

void add_undir_edge(int l, int r, struct Graph* g) {
	add_dir_edge(l, r, g);
	add_dir_edge(r, l, g);
}

void add_dir_edge(int parent, int child, struct Graph* g) {
	g->verticies[parent].children_size++;
	g->verticies[parent].children = realloc(g->verticies[parent].children, g->verticies[parent].children_size*sizeof(int));
	g->verticies[parent].children[g->verticies[parent].children_size-1] = child;
	connect_two_verticies(parent, child, g);
}

void connect_two_verticies(int a, int b, struct Graph* g) {
	connect_two_nodes(&(g->verticies[a]), &(g->verticies[b]));
}

void connect_two_nodes(struct Node* a, struct Node* b) {
	struct Node* left = get_true_master(a);
	struct Node* right = get_true_master(b);
	if(left == right)
		return;
	left->cc->size = left->cc->size + right->cc->size;
	free(right->cc);
	right->cc=NULL;
	right->master = left;
	return;
}

void destroy_graph(struct Graph** g_pointer) {
	int i;
	for(i=0;i< (*g_pointer)->size;i++) {

		if ((*g_pointer)->verticies[i].children != NULL)
			free((*g_pointer)->verticies[i].children);

		if( (*g_pointer)->verticies[i].cc != NULL)
			free((*g_pointer)->verticies[i].cc);
	}

	free((*g_pointer)->verticies);
	free(*g_pointer);
	return;
}

#endif
