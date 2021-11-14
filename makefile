all: main.o sudoku.o
	clang main.o sudoku.o -o main

main.o: main.c
	clang -c main.c

sudoku.o: sudoku.c
	clang -c sudoku.c
    
clean:
	rm -rf *.o *~ main