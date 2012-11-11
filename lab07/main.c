/*******************************************************************************
Pedro Emílio Machado de Brito - RA 137264
10/11/2012 - MC202 turma B

lab07 - Árvore B

main.c

Trata a entrada e chama as funções de inserção, busca e impressão.
*******************************************************************************/

#include <stdio.h>
#include "arvoreb.h"

int main()
{
  int leitura;
  int i;
  aluno entrada;
  aluno * retorno;
  arvoreb * arvore;
  /* le ordem mínima e cria árvore */
  scanf (" %d", &leitura);
  arvore = criaArvoreB(leitura);
  scanf (" %d", &i);
  /* lê e insere alunos */
  while (i-- > 0)
    {
      scanf (" %d %m[^\n]s", &entrada.ra, &entrada.nome);
      insereAluno(arvore, &entrada);
    }
  scanf (" %d", &i);
  /* i == 0, chama a impressão da árvore */
  if (!i) 
    imprimeArvoreB(arvore);
  /* lê e pesquisa RAs */
  while (i-- > 0)
    {
      scanf(" %d", &leitura);
      retorno = consultaRA(arvore, leitura);
      /* se retorno == NULL não foi encontrado o registro */
      if (retorno != NULL)
	printf("%s\n",retorno->nome);
    }
  /* libera toda memória da árvore */
  deletaArvoreB(arvore);  
  return 0;
}
