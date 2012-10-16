#include "setcover.h"
#include "stdio.h"
#include <stdlib.h>
#include <string.h>

int main ()
{
  int i, retorno = 1, * entrada, tam;
  conjcob * problema;
  char leitura[10];  
  scanf (" %d", &i);
  problema = iniConjCob(i);
  entrada = malloc (sizeof(int)*i);
  scanf (" %d", &i);      
  tam = 0;	  
  while (i >= 0)
    {
      if (scanf(" %s", leitura) == EOF || !strcmp(leitura, "s"))
	{
	  if (tam)
	    addConj(problema, entrada, tam);
	  i--;
	  tam = 0;
	}
      else
	entrada[tam++] = atoi (leitura);
    }
  free (entrada);
  i = 0;  
  while (1)
    {
      retorno = cobre (problema);
      if (retorno <= 0)
	break;
      if (!i)
	i=1;
      else
	printf (" U ");
      printf("S%d", retorno);
    }
  if (retorno)
    printf (" :(\n");
  else
    printf (" :)\n");
  return 0;  
}

  
	  
	


	  
	    
	    
