/*******************************************************************************
Pedro Emílio Machado de Brito - RA 137264
16/10/2012 - MC202 turma B

lab04 - Árvore Balanceada

main.c

Resolve um problema de cobertura de conjuntos.
*******************************************************************************/

#include "setcover.h"
#include <stdio.h>
/* #include <stdlib.h> */
#include "balloc.h"
#include <string.h>

int main ()
{
  int i, retorno = 1, * entrada, tam;
  conjcob * problema;
  char leitura[10];  
  scanf (" %d", &i);
  /* inicializa com tamanho do universo */
  problema = iniConjCob(i);
  /* vetor para guardar os elementos do conjunto da entrada */
  entrada = MALLOC (sizeof(int)*i);
  scanf (" %d", &i);      
  tam = 0;
  /* retorno é flag para não armazenar um conjunto vazio no primeiro s */
  retorno = 0;
  while (i >= 0)
    {
      /* quando terminar a entrada */
      if (scanf(" %s", leitura) == EOF || !strcmp(leitura, "s"))
	{
	  if (retorno)
	    addConj(problema, entrada, tam);
	  retorno = 1;
	  /* decrementa conjunto */
	  i--;
	  tam = 0;
	}
      else
	/* armazena entrada num vetor dinâmico */
	entrada[tam++] = atoi (leitura);
    }
  FREE (entrada);
  /* i é flag para não imprimir 'U' antes do primeiro conjunto */
  i = 0;
  while (1)
    {
      /* chama a função de cobertura de conjunto */
      retorno = cobre (problema);
      /* terminou o algoritmo */
      if (retorno < 1)
	break;
      if (!i)
      	i = 1;
      else
	printf (" U ");
      printf("S%d", retorno);
    }
  /* não conseguiu cobrir */
  if (retorno)
    printf (" :(\n");
  else
    /* cobriu */
    printf (" :)\n");
  /* libera memória */
  delConjCob(problema);  
  bapply(bprint);
  
  return 0;  
}

  
	  
	


	  
	    
	    
