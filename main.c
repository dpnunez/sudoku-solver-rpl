#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "sudoku.h"

int main() {
	sudoku *game;
	leSudoku(game);
  // resolveGame(game);
	imprimeGame(game);
  printf("\n\n");
  printf("%d ", buscaPorIndex(2, game)->valor);
	return 0;
}