#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "sudoku.h"

int main() {
	sudoku *game;
	leSudoku(game);
	imprimeGame(game);
	return 0;
}