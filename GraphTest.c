/*
Joseph Zanini
cmps101 fall 2018
PA4
jzanini@ucsc.edu
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "Graph.h"
#include "List.h"

int main(int argc, char* argv[]) {
	Graph g = newGraph(1);

	printf("new Graph size: %d\n", getSize(g));
	printf("new Graph order: %d\n", getOrder(g));
	printf("new Graph source: %d\n", getSource(g));
	printf("new Graph parent: %d\n", getParent(g, 2));
	printf("new Graph distance: %d\n", getDist(g, 2));

	//freeGraph(&g);

	//printf("new Graph size: %d\n", getSize(g));



	List L = newList();
	prepend(L, 3);
	insertOrdered(L, 1);
	insertOrdered(L, 5);
	insertOrdered(L, 4);
	insertOrdered(L, 7);

	for (moveFront(L); index(L) >= 0; moveNext(L)) {
		printf("List Value : %d\n", get(L));
    }

    freeList(&L);
    freeGraph(&g);
    g = newGraph(6);

    addEdge(g, 1, 2);
    //printf("new Graph size: %d\n", getSize(g));
    addEdge(g, 1, 3);
    //printf("new Graph size: %d\n", getSize(g));
    addEdge(g, 2, 4);
    //printf("new Graph size: %d\n", getSize(g));
    addEdge(g, 2, 5);
    //printf("new Graph size: %d\n", getSize(g));
    addEdge(g, 2, 6);
    //printf("new Graph size: %d\n", getSize(g));
    addEdge(g, 3, 4);
    //printf("new Graph size: %d\n", getSize(g));
    addEdge(g, 4, 5);
    addEdge(g, 5, 6);
    //printf("new Graph size: %d\n", getSize(g));
    //addArc(g, 5, 6);
    //printf("new Graph size: %d\n", getSize(g));

    //makeNull(g);
    //addEdge(g, 1, 2);
    //printf("new Graph size: %d\n", getSize(g));

    //FILE *out = fopen(argv[1], "w");
    //printGraph(out, g);

    BFS(g, 1);
    printf("new s : %d\n", getSource(g));
    L = newList();
    getPath(L, g, 5);

    //printf("6 distance: %d\n", getDist(g, 6));
    //printf("6 parent: %d\n", getParent(g, 6));

    for (moveFront(L); index(L) >= 0; moveNext(L)) {
		printf("List Value : %d\n", get(L));
    }
    

    freeList(&L);

    BFS(g, 3);
    L = newList();
    printf("new s : %d\n", getSource(g));
    getPath(L, g, 6);

    for (moveFront(L); index(L) >= 0; moveNext(L)) {
		printf("List Value : %d\n", get(L));
    }

    //printf("6 distance: %d\n", getDist(g, 6));
    //printf("6 parent: %d\n", getParent(g, 6));

    BFS(g, 4);
    L = newList();
    printf("new s : %d\n", getSource(g));
    getPath(L, g, 4);

    for (moveFront(L); index(L) >= 0; moveNext(L)) {
		printf("List Value : %d\n", get(L));
    }

	return 0;
}