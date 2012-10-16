#include <stdlib.h>
#include "datastruct.h"
/* #include "balloc.h" */

typedef struct Conj 
{
  no * arvore;
  int id;
  int cardinalidade;  
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
  conjcob * problema = malloc(sizeof(conjcob));
  problema->conjs = NULL;
  problema->universo = malloc(sizeof(conj));
  problema->universo->arvore = NULL;
  problema->universo->prox = NULL;
  problema->universo->cardinalidade = 0;  
  for (i = 1;  i <= universo; i++)
    problema->universo->cardinalidade += insere (&(problema->universo->arvore), i);
  return problema;  
}

void addConj( conjcob * problema, int * itens, int card)
{
  conj * novo = malloc (sizeof(conj));
  novo->id = 1 + (problema->conjs != NULL ? problema->conjs->id : 0 );
  novo->prox = problema->conjs;
  novo->arvore = NULL;
  novo->cardinalidade = 0;  
  problema->conjs = novo;
  while (card-- > 0)
    novo->cardinalidade += insere (&(novo->arvore), itens[card]);
}

int cobre ( conjcob * prob)
{
  int max = 0, elemento;
  conj * atual = NULL, * anda;
  if (prob->universo->arvore == NULL)
    return 0;  
  for (anda = prob->conjs; anda != NULL; anda = anda->prox)
    {
      if (anda->cardinalidade > max)
	{
	  max = anda->cardinalidade;
	  atual = anda;
	}
    }
  if (atual == NULL || atual->arvore == NULL)
    return -1;  
  while (atual->arvore != NULL)
    {
      elemento = raiz(atual->arvore);
      for (anda = prob->conjs; anda != NULL; anda = anda->prox)
	anda->cardinalidade -= retira (&(anda->arvore), elemento);
      prob->universo->cardinalidade -= retira (&(prob->universo->arvore), elemento);
    }
  return atual->id;  
}

void delConj( conj * conjunto)
{
  if (conjunto == NULL)
    return;
  delConj(conjunto->prox);
  deleta (conjunto->arvore);
  free(conjunto);
}


void delConjCob ( conjcob * problema )
{
  delConj (problema->conjs);
  delConj (problema->universo);
  free(problema);  
}

  
