#include "lista.h"
#include "balloc.h"
#include <stdlib.h>

#define malloc MALLOC
#define free FREE

/* inicia uma fila */

lista inicial(void)
{
  lista novo = (lista) malloc(sizeof(listaElemento));
  novo->digito = 127;
  novo->dir = novo;
  novo->esq = novo;
  return novo;
}

/* insere um elemento na lista */

int insereDir(lista l, char dig)
{
  lista novo;
  novo = (lista) malloc(sizeof(listaElemento));
  novo->digito = dig;
  novo->dir = l->dir;
  novo->esq = l;
  l->dir->esq = novo;
  l->dir = novo;
  return 0;
}

int insereEsq(lista l, char dig)
{
  lista novo;
  novo = (lista) malloc(sizeof(listaElemento));
  novo->digito = dig;
  novo->dir = l;
  novo->esq = l->esq;
  l->esq->dir = novo;
  l->esq = novo;
  return 0;
}

void libera (lista l)
{
  lista temp;
  for (temp = l->dir->dir; temp != l->dir; temp = temp->dir)
     free(temp->esq);
  free(l);
}

void deleta(lista l)
{
  l->esq->dir = l->dir;
  l->dir->esq = l->esq;
  free(l);
}

