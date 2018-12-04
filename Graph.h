/*
Joseph Zanini
cmps101 fall 2018
PA4
jzanini@ucsc.edu
*/

#ifndef _Graph_H_INCLUDED
#define _Graph_H_INCLUDED
#define INF -1
#define NIL -2

#include "List.h"

//Exported type
typedef struct GraphObj* Graph;

/*** Constructors-Destructors ***/

//newGraph()
// Returns reference to a new empty Graph object.
Graph newGraph(int n);

//freeGraph()
// Frees all heap memory associagted with *pG, and sets *pG to NULL.
void freeGraph(Graph* pG);

/*** Access functions ***/

//getOrder()
// Returns the value at the order.
// Pre: G != NULL
int getOrder(Graph G);

//getSize()
// Returns the size of the Graph object.
// Pre: G != NULL
int getSize(Graph G);

//getSource()
// returns the source vertex value
// Pre: G != NULL
int getSource(Graph G);

//getParent
// Returns the value of the parent of u.
// Pre: G != NULL 
// pre: getOrder() > u >= 1
int getParent(Graph G, int u);

//getDist()
// Returns the value of the distance to the node u
// Pre: G != NULL 
// pre: getOrder() > u >= 1
int getDist(Graph G, int u);

void getPath(List L, Graph G, int u);

/*** Manipulation procedures ***/

//makeNull()
// Deletes all edges of Graph
void makeNull(Graph G);

//addEdge()
// inserts an edge between 2 vertices
// pre: getOrder() > u >= 1
// pre: getOrder() > v >= 1
void addEdge(Graph G, int u, int v);

//addArc()
// inserts a directed edge between 2 vertices
// pre: getOrder() > u >= 1
// pre: getOrder() > v >= 1
void addArc(Graph G, int u, int v);

//BFS()
//Breadth First Search
void BFS(Graph G, int s);

/*** Other operations ***/

//printGraph()
// prints the adjacency List representation
//of a Graph Object to a output file.
void printGraph(FILE* out, Graph G);

#endif












