#include <stdio.h>
#include "arvoreb.h"

int main()
{
  int leitura;
  int i;
  aluno entrada;
  aluno * retorno;
  arvoreb * arvore;
  scanf (" %d", &leitura);
  arvore = criaArvoreB(leitura);
  scanf (" %d", &i);
  while (i-- > 0)
    {
      scanf (" %d %[^\n]s", &entrada.ra, entrada.nome);
      /* printf ("\nInseriu %d\n", entrada.ra); */
      insereAluno(arvore, entrada);
      /* imprimeArvoreB(arvore);        */
    }
  scanf (" %d", &i);
  if (!i) 
    imprimeArvoreB(arvore);
  while (i-- > 0)
    {
      scanf(" %d", &leitura);
      retorno = consultaRA(arvore, leitura);
      if (retorno != NULL)
	printf("%s\n",retorno->nome);
    }
  deletaArvoreB(arvore);  
  return 0;
}
