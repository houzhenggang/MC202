#include "arvoreb.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


arvoreb * criaArvoreB (int ordemMinima)
{
  arvoreb * nova = malloc(sizeof (arvoreb));
  nova->raiz = (no *) malloc (sizeof (no));
  nova->raiz->chave = NULL;
  nova->raiz->chaves = nova->raiz->filhos = 0;
  nova->ordem = 2*ordemMinima;  
  return nova;  
}

int buscaBinaria ( aluno * vetor, int tamanho, int ra)
{
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
  no * atual = arvore->raiz;
  while (1)
    {
      indice = buscaBinaria( atual->chave, atual->chaves, ra);
      if (indice < atual->chaves && atual->chave[indice].ra == ra)
	return atual->chave + indice;
      if (indice < atual->filhos)
	atual = (atual->filho)[indice];
      else
	return NULL;
    }
}


promocao insereRecursivo (no * atual, aluno novo, int ordem)
{
  int indice;
  promocao promo;  
  indice = buscaBinaria( atual->chave, atual->chaves, novo.ra);
  if (atual->filhos)
    {
      promo = insereRecursivo( atual->filho[indice], novo, ordem);
      if (promo.esq == NULL)
	return promo;      
      novo = promo.promovido;
      indice = buscaBinaria( atual->chave, atual->chaves, novo.ra);
    }      
  if (atual->chaves < ordem -1)
    {
      atual->chave = realloc(atual->chave, (atual->chaves+1)*sizeof(aluno));
      memmove(atual->chave + indice + 1, atual->chave+indice, (atual->chaves++ - indice)*sizeof(aluno)); /* porra ineficiente do caralho */
      atual->chave[indice] = novo;
      if (atual->filhos)
	{
	 atual->filho = realloc(atual->filho, (atual->filhos+1)*sizeof(no *));
	 memmove(atual->filho + indice + 2, atual->filho+indice+1, (atual->filhos++ - (indice+1))*sizeof(no *));
	 atual->filho[indice] = promo.esq;
	 atual->filho[indice + 1] = promo.dir;
	}
      promo.esq = promo.dir = NULL;      
    }
  else
    {
      promo.esq = atual;
      promo.promovido = atual->chave[atual->chaves/2];
      promo.dir = (no *) malloc (sizeof(no));
      promo.dir->chave = malloc (sizeof(aluno)*atual->chaves/2);
      promo.dir->chaves = atual->chaves/2;      
      memcpy(promo.dir->chave, atual->chave + atual->chaves/2 + 1, promo.dir->chaves*sizeof(aluno));
      if (atual->filhos)
	{
	  promo.dir->filho = (no **) malloc (sizeof(no *)*(atual->chaves/2+1));
	  promo.dir->filhos = atual->chaves/2+1;	  
	  memcpy(promo.dir->filho, atual->filho + atual->chaves/2+1, promo.dir->filhos*sizeof(no *));
	}
      else
	{
	  promo.dir->filho = NULL;
	  promo.dir->filhos = 0;
	}
      atual->chaves /= 2;
      atual->chave = realloc (atual->chave, atual->chaves*sizeof(aluno));
      if (atual->filhos)
	{
	  atual->filhos = atual->chaves + 1;
	  atual->filho = realloc (atual->filho, atual->filhos*sizeof(no *));
	}
      if (novo.ra < promo.promovido.ra)
	insereRecursivo (promo.esq, novo, ordem);
      else
	insereRecursivo (promo.dir, novo, ordem);
    }
  return promo;      
}

void insereAluno (arvoreb * arvore, aluno novo)
{
  promocao novaraiz = insereRecursivo(arvore->raiz, novo, arvore->ordem);
  if (novaraiz.esq == NULL)
    return;
  /* constrói nova raiz */
  arvore->raiz = (no *)  malloc (sizeof(no));
  arvore->raiz->chave = (aluno *) malloc (sizeof (aluno));
  arvore->raiz->chave[0] = novaraiz.promovido;
  arvore->raiz->chaves = 1;
  arvore->raiz->filho = (no **) malloc(sizeof(no *)*2);
  arvore->raiz->filho[0] = novaraiz.esq;
  arvore->raiz->filho[1] = novaraiz.dir;
  arvore->raiz->filhos = 2;
}

void imprimeNivel( no * pagina, int nivel)
{
  int i;
  if (nivel)
    for (i = 0; i < pagina->filhos; i++)
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
  no * anda = arvore->raiz;
  for (altura = 0; anda->filhos > 0; altura++)
    {
      imprimeNivel(arvore->raiz, altura);
      putchar('\n');
      anda = *(anda->filho);
    }
  imprimeNivel(arvore->raiz,altura);
  putchar('\n');
}


  
		  
  
  
			  
