/*******************************************************************************
Pedro Emílio Machado de Brito - RA 137264
16/10/2012 - MC202 turma B

lab04 - Árvore Balanceada

datastruct.c

Implementa uma árvore binária balanceada com afunilamento.
*******************************************************************************/

#include <stdlib.h>

typedef struct NoArv 
{
  int dado;
  struct NoArv * pai;
  struct NoArv * esq, * dir;
} no;

void rotacaoDir( no * pai, no ** refAvo, no * avo)
{
  /*  pega o nó a ser girado */
  no * filho = pai->esq;
  /* conserta as referências de/para avô */
  *refAvo = filho;
  filho->pai = avo;
  /* muda a subarvore direita do filho */
  pai->esq = filho->dir;
  /* se não nula conserta sua referência de pai */
  if (filho->dir != NULL)
    filho->dir->pai = pai;
  /* muda a subárvore direita do filho para seu antigo pai */
  filho->dir = pai;
  /* conserta a referência do pai para o filho */
  pai->pai = filho;  
}

/* exatamente o mesmo que o acima, porém direita <-> esquerda */
void rotacaoEsq( no * pai, no ** refAvo, no * avo)
{
  no * filho = pai->dir;
  *refAvo = filho;
  filho->pai = avo;
  pai->dir = filho->esq;
  if (filho->esq != NULL)
  filho->esq->pai = pai;
  filho->esq = pai;
  pai->pai = filho;  
}

void afunila ( no * novo, no ** arvore)
{
  /* enquanto o nó não for raiz */
  while (novo->pai != NULL)
    {
      /* se for filho esquerdo */
      if (novo->pai->esq == novo)
	{ /* se o pai é raiz */
	  if (novo->pai->pai == NULL)
	    rotacaoDir(novo->pai, arvore, NULL);
	  /* caso homogêneo esquerdo */
	  else if (novo->pai->pai->esq == novo->pai)
	    {
	      /* se o avô é raiz */
	      if (novo->pai->pai->pai == NULL)
		{
		  rotacaoDir(novo->pai->pai, arvore, NULL);
		  rotacaoDir(novo->pai, arvore, NULL);
		}
	      /* se não, precisa consertar a referência do bisavô do lado apropriado */
	      else if (novo->pai->pai->pai->esq == novo->pai->pai)
		{
		  rotacaoDir(novo->pai->pai, &(novo->pai->pai->pai->esq), novo->pai->pai->pai);
		  rotacaoDir(novo->pai, &(novo->pai->pai->esq), novo->pai->pai);		      
		}
	      else
		{
		  rotacaoDir(novo->pai->pai, &(novo->pai->pai->pai->dir), novo->pai->pai->pai);
		  rotacaoDir(novo->pai, &(novo->pai->pai->dir), novo->pai->pai);
		}
	    }
	  /* caso heterogêneo esquerdo */
	  else
	    {
	      /* rotação inicial do caso heterogêneo */
	      rotacaoDir(novo->pai, &(novo->pai->pai->dir), novo->pai->pai);
	      /* se o novo pai é raiz */
	      if (novo->pai->pai == NULL)
		rotacaoEsq(novo->pai, arvore, NULL);
	      /* se não, conserta a referência do avô do lado apropriado */
	      else if (novo->pai->pai->esq == novo->pai)
		rotacaoEsq(novo->pai, &(novo->pai->pai->esq), novo->pai->pai);
	      else
		rotacaoEsq(novo->pai, &(novo->pai->pai->dir), novo->pai->pai);
	    }
	}
      /* exatamente a mesma coisa, só que esquerda <-> direita */
      else
	{
	  if (novo->pai->pai == NULL)
	    rotacaoEsq(novo->pai, arvore, NULL);
	  else if (novo->pai->pai->dir == novo->pai)
	    {
	      if (novo->pai->pai->pai == NULL)
		{
		  rotacaoEsq(novo->pai->pai, arvore, NULL);
		  rotacaoEsq(novo->pai, arvore, NULL);
		}
	      else if (novo->pai->pai->pai->dir == novo->pai->pai)
		{
		  rotacaoEsq(novo->pai->pai, &(novo->pai->pai->pai->dir), novo->pai->pai->pai);
		  rotacaoEsq(novo->pai, &(novo->pai->pai->dir), novo->pai->pai);
		}
	      else
		{
		  rotacaoEsq(novo->pai->pai, &(novo->pai->pai->pai->esq), novo->pai->pai->pai);
		  rotacaoEsq(novo->pai, &(novo->pai->pai->esq), novo->pai->pai);
		}

	    }
	  else
	    {
	      rotacaoEsq(novo->pai, &(novo->pai->pai->esq), novo->pai->pai);
	      if (novo->pai->pai == NULL)
		rotacaoDir(novo->pai, arvore, NULL);
	      else if (novo->pai->pai->dir == novo->pai)
		rotacaoDir(novo->pai, &(novo->pai->pai->dir), novo->pai->pai);
	      else
		rotacaoDir(novo->pai, &(novo->pai->pai->esq), novo->pai->pai);
	    }
	}
    } /* eu acho que isso deve cobrir todos os casos */  
}

no * busca (no * arvore, int dado )
{
  /* caso de árvore vazia */
  if (arvore == NULL)
    return NULL;
  /* se não encontrar o nó com o dado, encontra quem deve ser seu pai ao ser inserido */
  while (1)
    {
      if (dado < arvore->dado && arvore->esq != NULL)
	arvore = arvore->esq;
      else if (dado > arvore->dado && arvore->dir != NULL)
	arvore = arvore->dir;      
      else
	return arvore;
    }
}

int insere ( no ** arvore, int dado )
{
  no * novo;
  novo = malloc(sizeof(no));
  novo->dado = dado;
  novo->dir = novo->esq = NULL;
  /* caso de árvore vazia */
  if ((novo->pai = busca(*arvore, dado)) == NULL)
    {
      *arvore = novo;
      return 1;
    }
  /* já existe o nó na árvore, só afunila */
  if (dado == novo->pai->dado)
    {
      afunila(novo->pai, arvore);      
      free(novo);
      return 0;
    }
  /* insere o nó do lado certo */
  if (novo->dado < novo->pai->dado)
    novo->pai->esq = novo;
  else
    novo->pai->dir = novo;
  afunila (novo, arvore);
  return 1;  
}

int retira (no ** arvore, int dado)
{
  no * chave = busca (*arvore, dado), *pai;
  int tmp;  
  /* caso de árvore vazia */
  if (chave == NULL)
    return 0;
  /* não encontrou a chave, afunila o último visitado na procura */
  if (chave->dado != dado)
    {
      afunila(chave, arvore);
      return 0;
    }
  pai = chave->pai;
  /* é uma folha */
  if (chave->dir == NULL && chave->esq == NULL) 
    {
      if (pai != NULL)
	{
	  if(pai->dir == chave)
	    pai->dir = NULL;
	  else
	    pai->esq = NULL;
	  afunila(pai, arvore);	  
	}
      else
	*arvore = NULL;
      free(chave);
    }
  /* só tem filho direito */
  else if (chave->esq == NULL)
    {

      if (pai != NULL)
	{
	  /* referência do pai aponta para o filho */
	  if (pai->dir == chave)
	    pai->dir = chave->dir;
	  else
	    pai->esq = chave->dir;
	  /* referência do filho aponta para o pai */
	  chave->dir->pai = pai;
	  /* afunila o pai */
	  afunila(pai,arvore);	  
	}
      else
	/* nó é raiz */
	{
	  *arvore = chave->dir;
	  chave->dir->pai = NULL;
	  /* não há pai para afunilar */
	}
      free(chave); /* libera a memória */
    }
  /* só tem filho esquerdo, igual ao de cima porém esquerda <-> direita */
  else if (chave->dir == NULL)
    {
      if (pai != NULL)
	{
	  if (pai->esq == chave)
	    pai->esq = chave->esq;
	  else
	    pai->dir = chave->esq;
	  chave->esq->pai = pai;	  
	  afunila(pai, arvore);	  
	}
      else
	{
	  *arvore = chave->esq;
	  chave->esq->pai = NULL;
	}      
      free(chave);      
    }
  else
    /* nó tem duas subárvores */
    {
      /* vai encontrar o nó mais a direita da subárvore esquerda */
      pai = busca (chave->esq, dado);
      /* guarda dado desse nó */
      tmp = pai->dado;
      /* recursão remove e afunila o nó (que tem no máximo um filho) */
      retira (arvore, tmp);
      /* sobrescreve o nó a ser removido "de verdade" */
      chave->dado = tmp;
    }
  /* retorna remoção bem sucedida */
  return 1;  
}

/* int conta (no * arvore) */
/* { */
/*   if (arvore == NULL) */
/*     return 0; */
/*   return conta(arvore->dir) + conta(arvore->esq) + 1; */
/* } */

/* retorna dado da raiz ou 0 */

int raiz (no * arvore)
{
  if (arvore == NULL)
    return 0;
  return arvore->dado;
}

/* deleta árvore recursivamente (não modifica a referência para a raiz, cuidado!) */
void deleta (no * arvore)
{
  if (arvore == NULL)
    return;
  deleta(arvore->dir);
  deleta(arvore->esq);
  free(arvore);
  return;
}
