#include "setcover.h"
#include "stdio.h"
#include <stdlib.h>
#include <string.h>

#define MALLOC malloc
#define FREE free

int main ()
{
  int instancias, i, conjuntos, retorno = 1, * entrada, tam;
  conjcob * problema;
  char leitura[10];  
  scanf(" %d", &instancias);
  while (instancias-- > 0)
    {
      scanf (" %d", &i);
      problema = iniConjCob(i);
      entrada = MALLOC (sizeof(int)*i);
      scanf (" %d", &conjuntos);      
      i = tam = 0;
      while (i <= conjuntos)
	{
	  scanf(" %s", leitura);
	  if (!strcmp(leitura, "s") || !strcmp(leitura, "-"))
	    {
	      if (tam)
		  addConj(problema, entrada, tam);
	      i++;
	      tam = 0;
	    }
	  else
	    entrada[tam++] = atoi (leitura);
	}
      FREE (entrada);
      entrada  = MALLOC(sizeof(int)*conjuntos);
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
	printf (" :(");
      else
	printf (" :)");
      FREE(entrada);
    }
  return 0;  
}

  
	  
	


	  
	    
	    
