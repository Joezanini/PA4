/*
Joseph Zanini
cmps101 fall 2018
PA4
jzanini@ucsc.edu
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "List.h"
#include "Graph.h"

#define MAX_LEN 160

int main(int argc, char* argv[]) {
	int n = 0;
	int vert1, vert2;
	int u, p;
	FILE *in, *out;
	Graph G = NULL;

	//check command line for correct number of arguments
	if (argc != 3) {
		printf("Usage: %s <input file> <output file>\n", argv[0]);
		exit(1);
	}

	in = fopen(argv[1], "r");
	out = fopen(argv[2], "w");

	if (in == NULL) {
		printf("Unable to open file %s for reading\n", argv[1]);
		exit(1);
	}

	if (out == NULL) {
		printf("Unable to open file %s for reading\n", argv[2]);
		exit(1);
	}

	//storing first value of file
	fscanf(in, "%d", &n);
	G = newGraph(n);

	while (fgetc(in) != EOF) {
		fscanf(in, "%d", &vert1);
		fscanf(in, "%d", &vert2);

		if (vert1 == 0 && vert2 == 0) {
			break;
		}

		addEdge(G, vert1, vert2);
	}

	printGraph(out, G);

	while (fgetc(in) != EOF) {
		fscanf(in, "%d", &u);
		fscanf(in, "%d", &p);

		if (u == 0 && p == 0) {
			break;
		}

		List L = newList();
		BFS(G, u);
		getPath(L, G, p);

		if (getDist(G, p) != INF) {
			fprintf(out, "\n\nThe distance from %d to %d is %d\n", u, p, getDist(G, p));
			fprintf(out, "A shortest %d-%d path is: ", u, p);
			printList(out, L);
		} else {
			fprintf(out, "\n\nThe distance from %d to %d is infinity\n", u, p);
			fprintf(out, "No %d-%d path exists", u, p);
		}
		freeList(&L);
	}

	freeGraph(&G);

	fclose(in);
	fclose(out);
	
	return 0;
}
