/*******************************************************************************
Pedro Emílio Machado de Brito - RA 137264
10/11/2012 - MC202 turma B

lab07 - Árvore B

arvoreb.c

Implementa inserção, busca e impressão com árvore B.
*******************************************************************************/


#include "arvoreb.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef enum  
  {
    FALSE, TRUE
  } bool;

typedef struct pagina
{
  int chaves;  
  aluno * chave;
  bool folha;
  struct pagina ** filho;
} pagina;

typedef struct arvoreb
{
  int ordem;
  pagina * raiz;
} arvoreb;

typedef struct
{
  aluno promovido;
  pagina * esq, * dir;
} promocao;

arvoreb * criaArvoreB (int ordemMinima)
{
  arvoreb * nova = malloc(sizeof (arvoreb));
  /* cria uma página vazia */
  nova->raiz = (pagina *) malloc (sizeof (pagina));
  nova->raiz->chave = NULL;
  nova->raiz->chaves = 0;
  nova->raiz->folha = TRUE;
  /* campo ordem armazena a ordem máxima */
  nova->ordem = 2*ordemMinima;  
  return nova;  
}

int buscaBinaria ( aluno * vetor, int tamanho, int ra)
{
  /* tem a propriedade muito útil de retornar índice ou do filho certo para descer,
     ou da chave certa se estiver lá */
  int esq = 0;
  while (tamanho > 0)
    {
      if (ra > vetor[tamanho/2 + esq].ra)
	  esq += tamanho--/2 + 1;
      tamanho /= 2;
    }
  return esq;
}

aluno * consultaRA (arvoreb * arvore, int ra)
{
  int indice;
  pagina * atual = arvore->raiz;
  while (1)
    {
      /* busca na página */
      indice = buscaBinaria( atual->chave, atual->chaves, ra);
      if (indice < atual->chaves && atual->chave[indice].ra == ra)
	/* encontrou o registro */
	return atual->chave + indice;
      if (!atual->folha)
	/* desce para o filho certo */
	atual = (atual->filho)[indice];
      else
	/* não achou */
	return NULL;
    }
}

static int ordem;

promocao * insereRecursivo (pagina * atual, aluno * novo)
{
  int indice;
  promocao * promo, * propaga = NULL;
  if (!atual->folha)
    {
      /* não sendo folha, chame a recursão e no retorno lide com eventual promoção de registro */
      indice = buscaBinaria( atual->chave, atual->chaves, novo->ra);
      propaga = insereRecursivo( atual->filho[indice], novo);
      if (propaga == NULL)
	return NULL;      
      novo = &(propaga->promovido);
    }
  /* se for necessário quebrar a página */
  if (atual->chaves >= ordem -1)
    {
      promo = (promocao *) malloc(sizeof(promocao));
      promo->esq = atual;
      /* copia registro a ser promovido */
      promo->promovido = atual->chave[atual->chaves/2];
      /* copia registros que vão pra nova página */
      promo->dir = (pagina *) malloc (sizeof(pagina));
      promo->dir->chave = malloc (sizeof(aluno)*atual->chaves/2);
      promo->dir->chaves = atual->chaves/2;
      memcpy(promo->dir->chave, atual->chave + atual->chaves/2 + 1, promo->dir->chaves*sizeof(aluno));
      /* copia status de folha, e ponteiros se necessário */
      promo->dir->folha = atual->folha;
      if (!atual->folha)
	{
	  promo->dir->filho = (pagina **) malloc (sizeof(pagina *)*(atual->chaves/2+1));
	  memcpy(promo->dir->filho, atual->filho + atual->chaves/2+1, (promo->dir->chaves+1)*sizeof(pagina *));
	}
      /* ajusta tamanho dos vetores */
      atual->chaves /= 2;
      atual->chave = realloc (atual->chave, atual->chaves*sizeof(aluno));
      if (!atual->folha)
	  atual->filho = realloc (atual->filho, (atual->chaves+1)*sizeof(pagina *));
      /* troca de página se for preciso */
      if (novo->ra > promo->promovido.ra)
	atual = promo->dir;
    }
  else
    /* marca a promoção como desnecessária */
    promo = NULL;
  /* encontra a posicao do novo elemento na página */
  indice = buscaBinaria( atual->chave, atual->chaves, novo->ra);
  /* redimensiona o vetor e desloca para a direita */
  atual->chave = realloc(atual->chave, (atual->chaves+1)*sizeof(aluno));
  memmove(atual->chave + indice + 1, atual->chave+indice, (atual->chaves++ - indice)*sizeof(aluno));
  /* coloca registro na posição */
  atual->chave[indice] = *novo;
  if (!atual->folha)
    {
      /* redimensiona o vetor de ponteiros e desloca para a direita */
      atual->filho = realloc(atual->filho, (atual->chaves+1)*sizeof(pagina *));
      memmove(atual->filho + indice + 2, atual->filho+indice+1, (atual->chaves - (indice+1))*sizeof(pagina *));
      /* coloca referências para as páginas resultantes da quebra */
      atual->filho[indice] = propaga->esq;
      atual->filho[indice + 1] = propaga->dir;
    }
  free (propaga);
  return promo;      
}

void insereAluno (arvoreb * arvore, aluno * novo)
{
  ordem = arvore->ordem;  
  promocao * novaraiz = insereRecursivo(arvore->raiz, novo);
  if (novaraiz == NULL)
    return;
  /* constrói nova raiz */
  arvore->raiz = (pagina *) malloc (sizeof(pagina));
  arvore->raiz->chave = (aluno *) malloc (sizeof (aluno));
  arvore->raiz->chave[0] = novaraiz->promovido;
  arvore->raiz->chaves = 1;
  arvore->raiz->filho = (pagina **) malloc(sizeof(pagina *)*2);
  arvore->raiz->filho[0] = novaraiz->esq;
  arvore->raiz->filho[1] = novaraiz->dir;
  arvore->raiz->folha = FALSE;
  free(novaraiz);  
}

void imprimeNivel( pagina * pagina, int nivel)
{
  int i;
  if (nivel)
    for (i = 0; i < pagina->chaves+1; i++)
      imprimeNivel (pagina->filho[i], nivel-1);
  else
    {
      putchar('{');
      for(i = 0; i < pagina->chaves; i++)
	printf (" %d", pagina->chave[i].ra);
      printf(" }");
    }
}
	
void imprimeArvoreB(arvoreb * arvore)
{
  int altura;
  pagina * anda = arvore->raiz;
  for (altura = 0; !anda->folha ; altura++)
    {
      imprimeNivel(arvore->raiz, altura);
      putchar('\n');
      anda = *(anda->filho);
    }
  imprimeNivel(arvore->raiz,altura);
  putchar('\n');
}

void liberaPagina (pagina * p)
{
  int i;
  /* libera as chaves */
  free (p->chave);
  if (!p->folha)
    {
      for (i = 0; i <= p->chaves; i++)
	/* libera filhos recursivamente */
	liberaPagina(p->filho[i]);
      free (p->filho);
    }
  free (p);
}

void deletaArvoreB (arvoreb * a)
{
  liberaPagina (a->raiz);
  free (a);
}

  
			  
