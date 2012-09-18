#ifndef LISTA_H
#define LISTA_H

/*******************************************************************************
lista.h

Define as funções do TAD lista duplamente ligada;

Permite inserção, leitura e remoção no começo e fim da lista.

*******************************************************************************/


struct listaElementoS
{
  char digito;
  struct listaElementoS * dir;
  struct listaElementoS * esq;
};

typedef struct listaElementoS listaElemento;

typedef listaElemento * lista;

/*
   Códigos de erro
   NULL: Algum dos três abaixo;
   -1 em problema de alocação
   -2 em lista inexistente
   -3 em posição inválida
*/

lista inicial(void);

int insereDir(lista, char);

int insereEsq(lista, char);

void libera(lista);

void deleta(lista);
#endif
