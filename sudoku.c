#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "sudoku.h"

void leSudoku(sudoku *game) {
  FILE *fp;
  char ch;
	bool primeiro = true;
  int parsedNumber, index=0;
	
  fp = fopen("game1.txt", "r");

  // Validaçao de leitura;
  if(fp == NULL) {
    printf("Erro na leitura");
    exit(1);
  }

	inicializaLista(game);
  // fgetc doc: http://www.cmaismais.com.br/referencia/cstdio/fgetc/
  while((ch = fgetc(fp)) != EOF) {
    // Verifica se o caractere lido é numério
    if(ch-'0' >= 0 && ch-'0' <= 9){
      parsedNumber = ch-'0';
			inserirCelula(game, parsedNumber, primeiro, index);
			primeiro = false;
      index++;
    }
  }

  if (game->tamanho < 81) {
    printf("Invalid game!");
    exit(1);
  }
}

void inserirCelula(sudoku *game, int valor, bool primeiro, int index) {
	celula *novaCelula;
	novaCelula = (celula *)malloc(sizeof(celula));
	novaCelula->valor=valor;
	novaCelula->proximo=NULL;
	novaCelula->anterior=game->fim;
  novaCelula->index=index;

	if (primeiro) {
		game->inicio=novaCelula;
		game->fim=novaCelula;
	} else {
		game->fim->proximo=novaCelula;
		game->fim=novaCelula;
	}
	game->tamanho++;
}

void inicializaLista(sudoku *game) {
	game->fim=NULL;
	game->inicio=NULL;
	game->tamanho=0;
}

void imprimeGame(sudoku *game) {
  int i, j;
	celula *atual;
	atual=game->inicio;


  for(int linha = 0 ; linha < 9 ; linha++) {
    for(int coluna = 0 ; coluna < 9 ; coluna++, atual=atual->proximo) {
      if(coluna==2 || coluna==5) {
        printf("%d  ", atual->valor);
      } else {
        printf("%d ", atual->valor);
      }
    }
    if(linha==2 || linha==5) printf("\n");
    printf("\n");
  }
  printf("\n\n");
}

void resolveGame(sudoku *game) {
  bool coordenadasFixas[81];
  int i=0;
  celula *atual;

  atual=game->inicio;

  while(atual->proximo != NULL) {
    if(atual->valor != 0) {
			coordenadasFixas[i]=true;
    }
		else {
			coordenadasFixas[i]=false;
    }
		i++;
		atual=atual->proximo;
  }


  resolveCelula(game, coordenadasFixas, game->inicio);
}

void resolveCelula(sudoku *game, bool *posicaoPreenchida, celula *atual) {
  int tentativa;

  while(posicaoPreenchida[atual->index])
    atual=atual->proximo;

  tentativa = atual->valor + 1;

  // verifica se a tentativa é maior que 9;
  if(tentativa > 9) {
    backtracking(game, posicaoPreenchida, atual);
    tentativa=1;
  }

  // verifica se a tentativa atende as regras;
  while(!verificaValidade(tentativa, game, atual)) {
    // Debug
    tentativa++;

    if(tentativa > 9) {
      backtracking(game, posicaoPreenchida, atual);
      tentativa=1;
    }
  }

  atual->valor=tentativa;


  // verifica se terminou
  if(verificaSeTerminou(game)) {
    imprimeGame(game);
    exit(0);
  }

  // computa o proximo
  resolveCelula(game, posicaoPreenchida, atual->proximo);
};


bool verificaValidade(int tentativa, sudoku *game, celula *atual) {
  int i;

  if(tentativa == 0)
    return true;


  // verifica linha 
  int linha = atual->index/9;
  for(int i = linha * 9 ; i < linha * 9 + 9 ; i++) {
    if(buscaPorIndex(i, game)->valor == tentativa) {
      return false;
    }
  }

  // verifica coluna
   int coluna = atual->index % 9;
    for(int i = coluna % 9 ; i <= 8 * 9 + coluna % 9 ; i+=9)
    {
        if(buscaPorIndex(i, game)->valor == tentativa) {
            return false;
        }
    }

  // verifica subjogo
  int submatrizX, submatrizY, y, x;
    if(linha < 3)
        submatrizY = 0;
    else if(linha >= 3 && linha < 6)
        submatrizY = 1;
    else if(linha >= 6)
        submatrizY = 2;
        
    if(coluna < 3)
        submatrizX = 0;
    else if(coluna >= 3 && coluna < 6)
        submatrizX = 1;
    else if(coluna >= 6)
        submatrizX = 2;

    for(y = 0 ; y < 3 ; y++)
      for(x = 0 ; x < 3 ; x++) {
          int pos = (x + submatrizX * 3) + ((y * 9) + (submatrizY * 9 * 3));
          if(buscaPorIndex(pos, game)->valor == tentativa) {
              return false;
          }
      }

  return true;
}


celula *buscaPorIndex(int index, sudoku *game) {
  celula *atual;
  atual=game->inicio;
  while(atual->index != index)
    atual=atual->proximo;
  
  return atual;
}

void backtracking(sudoku *game, bool *posicaoPreenchida, celula *atual) {
  atual->valor=0;
  atual=atual->anterior;

  while(posicaoPreenchida[atual->index] == true)
    atual=atual->anterior;

  resolveCelula(game, posicaoPreenchida, atual);  
}

bool verificaSeTerminou(sudoku *game) {
    celula *atual;
    atual=game->inicio;
    for(int i = 0 ; i < 81 ; i++, atual=atual->proximo)
        if(atual->valor == 0)
            return false;
    return true;
}
