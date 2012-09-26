#include<stdio.h>
#include<string.h>

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

int resolve2(int mat[9][9], int whatever_a, int whatever_b)
{
  int percorre, pilha[81][12] = {{0}}, pos = 0, max, i, j;
  for (i = 0; i < 9; i++)
    {
      for (j = 0; j < 9; j++)
	{
	  if (mat[i][j])
	    continue;
	  pilha[pos][10] = i;
	  pilha[pos][11] = j;
	  pos++;
	}
    }
  max = pos;
  pos = 0;
  while (pos >= 0 && pos < max)
    {
      i = pilha[pos][10];
      j = pilha[pos][11];
      if (!pilha[pos][0])
	{
	  for (percorre = 0; percorre < 9; percorre++)
	    {
	      pilha[pos][mat[i][percorre]] = 1;
	      pilha[pos][mat[percorre][j]] = 1;
	      pilha[pos][mat[i-(i%3)+percorre/3][j-(j%3)+percorre%3]] = 1;
	    }
	}
      while ( 1 )
	{
	  if (!pilha[pos][pilha[pos][0]])
	    {
	      pilha[pos][pilha[pos][0]] = 1;
	      mat[i][j] = pilha[pos++][0];
	      break;
	    }
	  pilha[pos][0]++;
	  if (pilha[pos][0] >= 10)
	    {
	      mat[i][j] = 0;
	      memset(pilha[pos],0,10*sizeof(int));
	      pos--;
	      break;
	    }
	}
    }
  if (pos == max)
    return 1;
  return 0;
}

int resolve(int mat[9][9], int i, int j)
{
  int percorre = 0, usado[10] = {0};
  do
    {
      do
	{
	  if (!mat[i][j])
	    {
	      percorre = 1;
	      break;
	    }
	  j++;
	}
      while ( j < 9);
      if (percorre)
	break;
      j = 0;
      i++;
    }
  while (i < 9);
  if (i == 9)
    return 1;
  for (percorre = 0; percorre < 9; percorre++)
    {
      usado[mat[i][percorre]] = 1;
      usado[mat[percorre][j]] = 1;
      usado[mat[i/3*3+percorre/3][j/3*3+percorre%3]] = 1;
    }
  for (percorre = 1; percorre < 10; percorre++)
    {
      if (!usado[percorre])
	{
	  mat[i][j] = percorre;
	  if (resolve(mat, i, j))
	    return 1;
	}
    }
  mat[i][j] = 0;
  return 0;
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
  return resolve2(mat, 0, 0);
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

