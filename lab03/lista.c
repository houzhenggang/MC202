#include "lista.h"
#include "balloc.h"

/*******************************************************************************
Pedro Emílio Machado de Brito - RA 137264
18/09/2012 - MC202 turma B

lab03 - Números indefinidamente grandes

lista.c

Implementa funções para lidar com o TAD lista.
*******************************************************************************/

/* a lista é duplamente ligada circular  */

lista inicial(void)
{
  lista novo = (lista) MALLOC(sizeof(listaElemento));
  /* valor armazenado no nó cabeça */
  novo->digito = 127;
  novo->dir = novo;
  novo->esq = novo;
  return novo;
}

int insereDir(lista l, char dig)
{
  lista novo;
  novo = (lista) MALLOC(sizeof(listaElemento));
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
  novo = (lista) MALLOC(sizeof(listaElemento));
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
  /* percorre liberando todos */
  for (temp = l->dir->dir; temp != l->dir; temp = temp->dir)
     FREE(temp->esq);
  FREE(l);
}

void deleta(lista l)
{
  l->esq->dir = l->dir;
  l->dir->esq = l->esq;
  FREE(l);
}

