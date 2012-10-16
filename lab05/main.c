#include "setcover.h"
#include "stdio.h"
#include <stdlib.h>
#include <string.h>

int main ()
{
  int i, conjuntos, retorno = 1, * entrada, tam;
  conjcob * problema;
  char leitura[10];  
  scanf (" %d", &i);
  problema = iniConjCob(i);
  entrada = malloc (sizeof(int)*i);
  scanf (" %d", &conjuntos);      
  i = tam = 0;	  
  while (i <= conjuntos)
    {
      if (scanf("%s", leitura) == EOF || !strcmp(leitura, "s"))
	{
	  if (tam)
	    addConj(problema, entrada, tam);
	  i++;
	  tam = 0;
	}
      else
	entrada[tam++] = atoi (leitura);
    }
  free (entrada);
  entrada = malloc(sizeof(int)*conjuntos);
  conjuntos = 0;      
  while (1)
    {
      retorno = cobre (problema);
      if (retorno < 0)
	break;
      entrada[conjuntos++] = retorno;
    }
  printf ("%d: ", conjuntos);
  if (conjuntos)
    printf("S%d", entrada[0]);
  for (i = 1; i < conjuntos; i++)
    printf (" U S%d", entrada[i]);
  if (retorno)
    printf (" :(\n");
  else
    printf (" :)\n");
  free(entrada);
  return 0;  
}

  
	  
	


	  
	    
	    
