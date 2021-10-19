#include <stdbool.h>

struct regCelula {
	int valor;
	struct regCelula *proximo;
	struct regCelula *anterior;
};

typedef struct regCelula celula;
struct regSudoku {
	celula *inicio;
	celula *fim;
	int tamanho;
};

typedef struct regSudoku sudoku;

void leSudoku(sudoku *game);
void inserirCelula(sudoku *game, int valor, bool primeiro);
void inicializaLista(sudoku *game);
void imprimeGame(sudoku *game);