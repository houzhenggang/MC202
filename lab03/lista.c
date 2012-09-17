#include "lista.h"
#include "grandeint.h"
#include "balloc.h"
#include <stdlib.h>

#define malloc MALLOC
#define free FREE

/* estrutura que guarda cada nó da lista */

struct listaElementoS
{
  char digito;
  struct listaElementoS * dir;
  struct listaElementoS * esq;
};

typedef struct listaElementoS listaElemento;

/* inicia uma fila */

lista inicial(void)
{
  lista novo = (lista) malloc(sizeof(listaElemento));
  if (novo == NULL)
    return NULL;
  novo->digito = 127;

  novo->dir = novo;
  novo->esq = novo;
  return novo;
}

/* insere um elemento na lista */

int insereDir(lista l, char dig)
{
  lista novo;
  if (l == NULL)
    return -2;
  novo = (lista) malloc(sizeof(listaElemento));
  if (novo == NULL)
    return -1;
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
  if (l == NULL)
    return -2;
  novo = (lista) malloc(sizeof(listaElemento));
  if (novo == NULL)
    return -1;
  novo->digito = dig;
  novo->dir = l;
  novo->esq = l->esq;
  l->esq->dir = novo;
  l->esq = novo;
  return 0;
}

lista andaEsq(lista l)
{
  return l->esq;
}

lista andaDir(lista l)
{
  return l->dir;
}

char pega(lista l)
{
  return l->digito;
}

void libera (lista l)
{
  lista temp;
  for (temp = l->dir->dir; temp != l->dir; temp = temp->dir)
     free(temp->esq);
  free(l);
}

grandeint tamanho(lista l)
{
  grandeint tam = iniciagi(), um = itogi(1), temp;
  lista iter;
  for (iter = l->dir; iter != l; iter = iter->dir)
    {
      temp = mais(tam,um);
      liberagi(tam);
      tam = temp;
    }
  liberagi(um);
  return tam;
}

void atribui(lista l, char digito)
{
  if (l == NULL)
    return;
  l->digito = digito;  
}

void deleta(lista l)
{
  if (l == NULL)
    return;
  l->esq->dir = l->dir;
  l->dir->esq = l->esq;
  free(l);
}

