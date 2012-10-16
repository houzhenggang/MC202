#include <stdlib.h>
#include "datastruct.h"
#include "balloc.h"
/* #define MALLOC malloc */
/* #define FREE free */

typedef struct Conj 
{
  no * arvore;
  int id;  
  struct Conj * prox;
  
} conj;

typedef struct Conjcob
{
  conj * conjs;
  conj * universo;
} conjcob;
  
conjcob * iniConjCob (int universo)
{
  int i;
  conjcob * inst = MALLOC(sizeof(conjcob));
  inst->conjs = NULL;
  inst->universo = MALLOC(sizeof(conj));
  inst->universo->arvore = NULL;
  for (i = 1;  i <= universo; i++)
    insere (&(inst->universo->arvore), i);
  return inst;  
}

void addConj( conjcob * prob, int * itens, int card)
{
  conj * novo = MALLOC (sizeof(conj));
  novo->id = prob->conjs != NULL ? prob->conjs->id + 1 : 1;
  novo->prox = prob->conjs;
  novo->arvore = NULL;
  prob->conjs = novo;  
  while (card-- > 0)
    insere (&(novo->arvore), itens[card]);
}

int cobre ( conjcob * prob)
{
  int max = 0, card, elemento;
  conj * atual = NULL, * anda;
  if (prob->universo->arvore == NULL)
    return 0;  
  for (anda = prob->conjs; anda != NULL; anda = anda->prox)
    {
      card = conta(anda->arvore);
      if (card > max)
	{
	  max = card;
	  atual = anda;
	}
    }
  if (atual == NULL || atual->arvore == NULL)
    return -1;  
  while (atual->arvore != NULL)
    {
      elemento = raiz(atual->arvore);
      for (anda = prob->conjs; anda != NULL; anda = anda->prox)
	retira (&(anda->arvore), elemento);
      retira (&(prob->universo->arvore), elemento);
    }
  return atual->id;  
}
