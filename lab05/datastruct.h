/*******************************************************************************
Pedro Emílio Machado de Brito - RA 137264
16/10/2012 - MC202 turma B

lab04 - Árvore Balanceada

datastruct.h

Assinaturas de funções para árvore binária com afunilamento.
*******************************************************************************/

#ifndef DATASTRUCT_C
#define DATASTRUCT_C

typedef struct NoArv no;

int insere (no **, int);

int retira (no **, int);

int raiz (no *);

void deleta (no *);

#endif
