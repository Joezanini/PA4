#------------------------------------------------------------------------------
# Makefile for CMPS 101 Programming Assignment 2
#
#       make                   makes FindPath
#       make Graph        makes Graph
#------------------------------------------------------------------------------

FindPath : FindPath.o Graph.o List.o
	gcc -o FindPath FindPath.o Graph.o List.o

FindPath.o : FindPath.c List.h
	gcc -c -std=c99 -Wall FindPath.c

Graph: Graph.o List.o
	gcc -o Graph Graph.o List.o

Graph.o : Graph.c List.h
	gcc -c -std=c99 -Wall Graph.c

List.o : List.c List.h
	gcc -c -std=c99 -Wall List.c

clean :
	rm -f FindPath Graph FindPath.o Graph.o List.o
