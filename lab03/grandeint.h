#ifndef GRANDEINT_H
#define GRANDEINT_H
#include "lista.h"

/*******************************************************************************
Pedro Emílio Machado de Brito - RA 137264
18/09/2012 - MC202 turma B

lab03 - Números indefinidamente grandes

grandeint.h

Define assinaturas de funções para lidar com inteiros indefinidamentes grandes
*******************************************************************************/

struct grandeintS{
  lista digitos;
  char sinal;
};

typedef struct grandeintS * grandeint;


/* inicia um grandeint igual a 0 */
grandeint iniciagi(void);

/* converte de int para grandeint */
grandeint itogi(int);

/* lê um grandeint da entrada padrão */
grandeint giscan(void);

/* imprime um grandeint na saída padrão */
void printgi(grandeint);

/* retorna um grandeint com a soma dos argumentos */
grandeint mais(grandeint, grandeint);

/* incrementa o primeiro grandeint do argumento com o segundo */
void incrementa(grandeint, grandeint);

/* retorna um grandeint com o produto dos argumentos */
grandeint vezes(grandeint, grandeint);

/* libera toda a memória de um grandeint */
void liberagi(grandeint);

/* retorna < 0 se o primeiro for menor que o segundo,
0 se ambos forem iguais, e > 0 se o segundo for maior
Passar o argumento int diferente de zero compara módulo */
int compara(grandeint, grandeint, int);

/* retorna um grandeint igual ao quociente entre o primeiro e o segundo */
grandeint divisao(grandeint, grandeint);

/* funções chamadas por main */

void soma(void);

void multiplicacao(void);

void divide(void);

void godel(void);

#endif
