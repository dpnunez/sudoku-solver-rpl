#include <stdbool.h>

struct regCelula {
	int valor;
  int index;
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
void inserirCelula(sudoku *game, int valor, bool primeiro, int index);
void inicializaLista(sudoku *game);
void imprimeGame(sudoku *game);
void resolveGame(sudoku *game);
void resolveCelula(sudoku *game, bool *posicaoPreenchida, celula *atual);
bool verificaValidade(int tentativa, sudoku *game, celula *atual);
celula *buscaPorIndex(int index, sudoku *game);