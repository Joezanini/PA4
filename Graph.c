/*
Joseph Zanini
cmps101 fall 2018
PA4
jzanini@ucsc.edu
*/

#include<stdio.h>
#include<stdlib.h>
#include "Graph.h"
#include "List.h"

//private Node Object
typedef struct GraphObj {
	List* listPtr;
	char* color;
	int* p;
	int* d;
	int size;
	int order;
	int s;
} GraphObj;

//typedef GraphObj* Graph;

/*** Constructors-Destructors ***/

//newGraph()
// Returns reference to a new empty Graph object.
Graph newGraph(int n) {
	int i;

	Graph G = malloc(sizeof(GraphObj));
	G->listPtr = malloc((n + 1) * sizeof(List)); //declaring array of Lists

	//allocating new empty lists in the array.
	for(i = 0; i < n + 1; i++) {
		//List temp = newList();
		G->listPtr[i] = newList();
	}

	//vertex propery arrays for BFS
	G->color = NULL;
	G->p = NULL;
	G->d = NULL;
	G->size = 0;
	G->order = n;
	G->s = NIL;

	return(G);
}

//freeGraph()
// Frees all heap memory associagted with *pG, and sets *pG to NULL.
void freeGraph(Graph* pG) {

	if ((*pG)->color != NULL) {
		free((*pG)->color);
        (*pG)->color = NULL;
    }

    if ((*pG)->d != NULL) {
        free((*pG)->d);
        (*pG)->d = NULL;
    }

    if ((*pG)->p != NULL) {
        free((*pG)->p);
        (*pG)->p = NULL;
    }

    if ((*pG)->listPtr != NULL) {
    	free((*pG)->listPtr);
    	(*pG)->listPtr =NULL;
    }


    if (pG != NULL && *pG != NULL) {
        free(*pG);
        *pG = NULL;
     }
}

/*** Access functions ***/

//getOrder()
// Returns the value at the order.
// Pre: G != NULL
int getOrder(Graph G) {
	if (G == NULL) {
		printf("Graph Error: calling getOrder() on a NULL Graph pointer\n");
		exit(1);
	}
	return(G->order);
}

//getSize()
// Returns the size of the Graph object.
// Pre: G != NULL
int getSize(Graph G) {
	if (G == NULL) {
		printf("Graph Error: calling getSize() on a NULL Graph pointer\n");
		exit(1);
	}
	return(G->size);
}

//getSource()
// returns the source vertex value
// Pre: G != NULL
int getSource(Graph G) {
	if (G == NULL) {
		printf("Graph Error: calling getSource() on a NULL Graph pointer\n");
		exit(1);
	}
	return(G->s);
}


//getParent()
// Returns the value of the parent of u.
// Pre: G != NULL and (1 <= u < getOrder())
int getParent(Graph G, int u) {
	if (G == NULL) {
		printf("Graph Error: calling getParent() on a NULL Graph pointer\n");
		exit(1);
	}

	if (u < 1 && u > getOrder(G)) {
		printf("Graph Error: calling getParent() on a out of bounds vertex\n");
		exit(1);
	}

	if (G->p != NULL) {
		return(G->p[u]);
	} else {
		return(NIL);
	}
}

//getDist()
// Returns the value of the parent of u.
// Pre: G != NULL and (1 <= u < getOrder())
int getDist(Graph G, int u) {
	if (G == NULL) {
		printf("Graph Error: calling getDist() on a NULL Graph pointer\n");
		exit(1);
	}

	if (u < 1 && u > getOrder(G)) {
		printf("Graph Error: calling getDist() on a out of bounds vertex\n");
		exit(1);
	}

	if (G->d != NULL) {
		return(G->d[u]);
	} else {
		return(INF);
	}
}

//getPath()
// Appends to the List the vertices of a shortest path in 
// the graph G
// pre: G != NULL and getSource(G) != NULL and 1 <= u < getOrder()
void getPath(List L, Graph G, int u) {
	if (G == NULL) {
		printf("Graph Error: calling getPath() on a NULL Graph pointer\n");
		exit(1);
	}

	if (u < 1 && u > getOrder(G)) {
		printf("Graph Error: calling getPath() on a out of bounds vertex\n");
		exit(1);
	}

	if (getSource(G) < 0) {
		printf("Graph Error: calling getPath() on a NULL source\n");
		exit(1);
	}

	
	if (u == getSource(G)) {
		append(L, u);
	} else if (getParent(G, u) == NIL) {
		append(L, NIL);
	} else {
		getPath(L, G, getParent(G, u));
		append(L, u);
	}

	return;
}

/*** Manipulation procedures ***/

//makeNull()
// Deletes all edges of Graph
// pre: G != NULL
void makeNull(Graph G) {
	int i;
	int stop = getOrder(G);
	if (G == NULL) {
		printf("Graph Error: calling makeNull() on a NULL Graph pointer\n");
		exit(1);
	}

	for(i = 1; i < stop; i++) {
		for (moveFront(G->listPtr[i]); index(G->listPtr[i]) >= 0; 
			moveNext(G->listPtr[i])) {
			clear(G->listPtr[i]);
		}
	}

	G->size = 0;
	G->s = NIL;
	return;
}

// addEdge()
// Insert a new edge joining u to v and v to u
// Pre: 1<= u <= getOrder(G) and  1<= v <= getOrder(G)
// and G != NULL
void addEdge(Graph G, int u, int v) {
	if (G == NULL) {
		printf("Graph Error: calling getEdge() on a NULL Graph pointer\n");
		exit(1);
	}

	if (u < 1 && u > getOrder(G)) {
		printf("Graph Error: calling getEdge() on a out of bounds vertex u\n");
		exit(1);
	}

	if (v < 1 && v > getOrder(G)) {
		printf("Graph Error: calling getEdge() on a out of bounds vertex v\n");
		exit(1);
	}

	insertOrdered(G->listPtr[u], v);
	insertOrdered(G->listPtr[v], u);
	G->size ++;
	return;
}

//addArc()
// inserts a directed edge between 2 vertices
// pre: getOrder() > u >= 1
// pre: getOrder() > v >= 1
void addArc(Graph G, int u, int v) {
	if (G == NULL) {
		printf("Graph Error: calling getArc() on a NULL Graph pointer\n");
		exit(1);
	}

	if (u < 1 && u > getOrder(G)) {
		printf("Graph Error: calling getArc() on a out of bounds vertex u\n");
		exit(1);
	}

	if (v < 1 && v > getOrder(G)) {
		printf("Graph Error: calling getArc() on a out of bounds vertex v\n");
		exit(1);
	}

	insertOrdered(G->listPtr[u], v);
	G->size++;
}

//BFS()
//Breadth First Search
// pre: getOrder() > s >= 1 and G != NULL
void BFS(Graph G, int s) {
	int i;
	int u, v;
	int n = getOrder(G);

	if (G == NULL) {
		printf("Graph Error: calling BFS() on a NULL Graph pointer\n");
		exit(1);
	}

	if (s < 1 && s > getOrder(G)) {
		printf("Graph Error: calling BFS() on a out of bounds vertex u\n");
		exit(1);
	}

	G->s = s;
	G->color = malloc((n + 1) * sizeof(char));
	G->p = malloc((n + 1) * sizeof(int));
	G->d = malloc((n + 1) * sizeof(int));


	for (i = 1; i < n + 1; i++) {
		G->color[i] = 'w';
		G->d[i] = INF;
		G->p[i] = NIL;
	}

	G->color[s] = 'g';
	G->d[s] = 0;
	G->p[s] = NIL;

	List q = newList();
	prepend(q, s);


	while (!isEmpty(q)) {
		moveFront(q);
		u = get(q);
		deleteFront(q);
		for (moveFront(G->listPtr[u]); index(G->listPtr[u]) >= 0; 
			moveNext(G->listPtr[u])) {
			v = get(G->listPtr[u]);
			if (G->color[v] == 'w') {
				G->color[v] = 'g';
				G->d[v] = G->d[u] + 1;
				G->p[v] = u;
				append(q, v);
			}
		}
		G->color[u] = 'b';
	}
	return;
}

//printGraph()
// prints the adjacency List representation
//of a Graph Object to a output file.
void printGraph(FILE* out, Graph G) {
	int i;
	int stop = getOrder(G);

	if (G == NULL) {
		printf("Graph Error: calling printGraph() on a NULL Graph pointer\n");
		exit(1);
	}

	for (i = 1; i <= stop; i++) {
		fprintf(out, "%d: ", i);
		for (moveFront(G->listPtr[i]); index(G->listPtr[i]) >= 0; 
			moveNext(G->listPtr[i])) {
			fprintf(out, "%d", get(G->listPtr[i]));
			fprintf(out, "%s", " ");
		}
		fprintf(out, "%s\n", " ");
	}
	return;
}













