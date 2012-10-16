/*******************************************************************************
Pedro Emílio Machado de Brito - RA 137264
16/10/2012 - MC202 turma B

lab04 - Árvore Balanceada

setcover.c

Funções que implementam a cobertura de conjuntos.
*******************************************************************************/

#include <stdlib.h> 
#include "datastruct.h"

/* estrutura que guarda cada conjunto, em forma de lista ligada */
typedef struct Conj 
{
  no * arvore;
  int id;
  int cardinalidade;  
  struct Conj * prox;
} conj;

/* estrutura que guarda os conjuntos do problema */
typedef struct Conjcob
{
  conj * conjs;
  conj * universo;
} conjcob;

/* inicializa o problema */
conjcob * iniConjCob (int universo)
{
  int i;
  conjcob * problema = malloc(sizeof(conjcob));
  problema->conjs = NULL;
  /* inicializa conjunto universo */
  problema->universo = malloc(sizeof(conj));
  problema->universo->arvore = NULL;
  problema->universo->prox = NULL;
  problema->universo->cardinalidade = 0;  
  /* popula o conjunto universo */
  for (i = 1;  i <= universo; i++)
    problema->universo->cardinalidade += insere (&(problema->universo->arvore), i);
  return problema;  
}

void addConj( conjcob * problema, int * itens, int card)
{
  conj * novo = malloc (sizeof(conj));
  /* cresce id do conjunto */
  novo->id = 1 + (problema->conjs != NULL ? problema->conjs->id : 0 );
  novo->prox = problema->conjs;
  novo->arvore = NULL;
  novo->cardinalidade = 0;  
  problema->conjs = novo;
  /* popula o conjunto com os elementos */
  while (card-- > 0)
    novo->cardinalidade += insere (&(novo->arvore), itens[card]);
}

int cobre ( conjcob * prob)
{
  int max = 0, elemento;
  conj * atual = NULL, * anda;
  /* se o universo está vazio, terminou */
  if (prob->universo->cardinalidade == 0)
    return 0;  
  /* procura conjunto com maior cardinalidade */
  for (anda = prob->conjs; anda != NULL; anda = anda->prox)
    {
      if (anda->cardinalidade > max)
	{
	  max = anda->cardinalidade;
	  atual = anda;
	}
    }
  /* se nao há mais conjuntos com elementos */
  if (atual == NULL || atual->cardinalidade == 0)
    return -1;  
  /* retira os elementos do conjunto de todos os conjuntos */
  while (atual->cardinalidade > 0)
    {
      /* pega elemento */
      elemento = raiz(atual->arvore);
      /* retira dos conjuntos */
      for (anda = prob->conjs; anda != NULL; anda = anda->prox)
	anda->cardinalidade -= retira (&(anda->arvore), elemento);
      /* retira do universo */
      prob->universo->cardinalidade -= retira (&(prob->universo->arvore), elemento);
    }
  /* retorna subconjunto que foi usado */
  return atual->id;  
}

void delConj( conj * conjunto)
{
  if (conjunto == NULL)
    return;
  /* deleta restante da lista */
  delConj(conjunto->prox);
  /* deleta árvore */
  deleta (conjunto->arvore);
  free(conjunto);
}

void delConjCob ( conjcob * problema )
{
  /* deleta conjuntos */
  delConj (problema->conjs);
  delConj (problema->universo);
  free(problema);  
}

  
