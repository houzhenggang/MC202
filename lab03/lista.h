#ifndef LISTA_H
#define LISTA_H
#include "grandeint.h"

/*******************************************************************************
lista.h

Define as funções do TAD lista duplamente ligada;

Permite inserção, leitura e remoção no começo e fim da lista.
*******************************************************************************/

typedef struct listaElementoS * lista;

/*
   Códigos de erro
   NULL: Algum dos três abaixo;
   -1 em problema de alocação
   -2 em lista inexistente
   -3 em posição inválida
*/

lista inicial(void);

/* 0 insere no comeco, resto no fim */

char pega (lista);

void atribui (lista, char);

grandeint tamanho (lista);

int insereDir(lista, char);

int insereEsq(lista, char);

lista andaDir(lista);

lista andaEsq(lista);

void libera(lista);

void deleta(lista);
#endif
