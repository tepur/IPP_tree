solution: solution.o tree.o
	gcc -o solution solution.o tree.o
debug: solution.o tree.o
	gcc -g -o solution.dbg solution.o tree.o
tree.o : tree.c
	gcc -g -c tree.c
solution.o : solution.c
	gcc -g -c solution.c
