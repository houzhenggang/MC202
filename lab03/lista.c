#include "lista.h"
#include "balloc.h"

/* estrutura que guarda cada nó da fila */
struct listaElementoS
{
  void * dado;
  struct listaElementoS * prox;
};

typedef struct listaElementoS listaElemento;

/* estrutura que guarda informação sobre o tamanho atual da fila e seu nó final */
struct listaLigada
{
  int tamanho;
  listaElemento * cabeca;
};

/* inicia uma fila */

lista inicia (void)
{
  lista novo = (lista) MALLOC(sizeof(struct listaLigada));
  if (novo == NULL)
    return NULL;
  novo->cabeca = (listaElemento *) MALLOC(sizeof(listaElemento));
  if (novo->cabeca == NULL)
    {
      FREE(novo);
      return NULL;
    }
  novo->cabeca->dado = (void *) NULL;
  novo->cabeca->prox = NULL;
  novo->tamanho = 0;
  return novo;
}

/*insere um elemento no fim da fila */

int insere(lista l, void * elemento, int pos)
{
  listaElemento * temp, * novo;
  if (l == NULL)
    return -2;
  if (pos < 0)
    return -3;
  for (temp = l->cabeca; pos > 0 && temp != NULL; pos--, temp = temp->prox);
  if (temp == NULL)
    return -3;
  novo = (listaElemento *) MALLOC(sizeof(listaElemento));
  if (novo == NULL)
    return -1;
  novo->prox = temp->prox;
  novo->dado = elemento;
  temp->prox = novo;
  l->tamanho++;
  return 0;
}

void * pega (lista f, int pos)
{
  listaElemento * temp;
  if (f == NULL)
    return NULL;
  if (pos < 0)
    return NULL;
  for (temp = f->cabeca->prox; temp != NULL && pos > 0; pos--, temp = temp->prox);
  if (temp == NULL)
    return NULL;
  return temp->dado;  
}

/* retorna no número de elementos atualmente */

int tamanho(lista l)
{
  if (l == NULL)
    return -2;
  return l->tamanho;
}

int retira(lista l, int pos)
{
  listaElemento * temp, * del;
  if (l == NULL)
    return -2;
  if(pos < 0)
    return -3;
  for (temp = l->cabeca; temp != NULL && pos > 0; pos--, temp = temp->prox);
  if (temp == NULL || temp->prox == NULL)
    return -3;
  del = temp->prox;
  temp->prox = del->prox;
  FREE(del);
  l->tamanho--;
  return 0;
}

int libera (lista l)
{
  if (l == NULL)
    return -2;
  while(!retira(l,0));
  FREE(l->cabeca);
  FREE(l);
  return 0;
}


  
