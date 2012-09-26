#include<stdio.h>

/*******************************************************************************
Pedro Emílio Machado de Brito - RA 137264
25/09/2012 - MC202 turma B

lab04 - Sudoku

principal.c

Resolve um tabuleiro de sudoku, caso exista solução.
*******************************************************************************/


/*Funcao que imprime a matriz 9x9 que armazena o jogo de Sudoku (opcionalmente a matriz pode ser global e nao passada por parametro)*/
void imprime(int mat[9][9]){
	int i, j;
	for(i=0; i<9; i++){
		if(i%3 == 0)
			printf("--------------------------\n");
		for(j=0; j<9; j++){
			if(j%3 == 0)
				printf(" |");
			printf(" %d", mat[i][j]);
		}
		printf(" |\n");
	}
	printf("--------------------------\n");
	return;
}

int resolve(int mat[9][9], int i, int j)
{
  int percorre = 0, pilha[82][12] = {{0}}, pos = 0;
  while (pos >= 0 && pos < 81)
    {
      if (!pilha[pos][0])
	{
	  do
	    {
	      do
		{
		  if (!mat[pilha[pos][10]][pilha[pos][11]])
		    goto vazio;
		  pilha[pos][11]++;
		}
	      while ( pilha[pos][11] < 9);
	      pilha[pos][11] = 0;
	      pilha[pos][10]++;
	    }
	  while (pilha[pos][10] < 9);
	  if (pilha[pos][10] == 9)
	    return 1;
	vazio:
	  for (percorre = 1; percorre < 10; percorre++)
	    pilha[pos][percorre] = 0;
	  for (percorre = 0; percorre < 9; percorre++)
	    {
	      pilha[pos][mat[pilha[pos][10]][percorre]] = 1;
	      pilha[pos][mat[percorre][pilha[pos][11]]] = 1;
	      pilha[pos][mat[pilha[pos][10]/3*3+percorre/3][pilha[pos][11]/3*3+percorre%3]] = 1;
	    }
	}
      while ( pilha[pos][0] < 10 )
	{
	  if (!pilha[pos][pilha[pos][0]])
	    {
	      mat[pilha[pos][10]][pilha[pos][11]] = pilha[pos][0];
	      pilha[pos][0]++;
	      pos++;
	      break;
	    }
	  pilha[pos][0]++;
	}
      if (pilha[pos][0] == 10)
	{
	  mat[pilha[pos][10]][pilha[pos][11]] = pilha[pos][0] = 0;
	  pos--;
	}
    }
  if (pos < 0)
    return 0;
  else
    return 1;
}

int sudoku(int mat[9][9])
{
  int x,y, v, casas;
  /* loop de inicialização */
  for (scanf (" %d", &casas); casas > 0; casas--)
    {
      scanf(" %d %d %d", &x, &y, &v);
      mat[x-1][y-1] = v;
    }
  /* chamada inicia a recursão */
  return resolve(mat, 0, 0);
}

int main()
{
  /* matriz que guarda o tabuleiro */
  int tabuleiro[9][9] = {{0}};
  if (sudoku(tabuleiro))
    imprime(tabuleiro);
  else
    printf("Sem solucao\n");
  return 0;
}

