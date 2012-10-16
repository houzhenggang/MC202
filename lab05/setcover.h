/*******************************************************************************
Pedro Emílio Machado de Brito - RA 137264
16/10/2012 - MC202 turma B

lab04 - Árvore Balanceada

setcover.h

Assinaturas de funções para cobertura de conjuntos.
*******************************************************************************/


#ifndef SETCOVER_H
#define SETCOVER_H

typedef struct Conjcob conjcob;

conjcob * iniConjCob (int );

void addConj (conjcob *, int *, int);

int cobre (conjcob *);

void delConjCob (conjcob *);

#endif
