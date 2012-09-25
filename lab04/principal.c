#include<stdio.h>

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
  int x = 0, usado[10] = {0};
  do
    {
      do
	{
	  if (!mat[i][j])
	    {
	      x = 1;
	      break;
	    }
	  (j)++;
	}
      while ( j < 9);
      if (x)
	break;
      j = 0;
      i++;
    }
  while (i < 9);
  if (i == 9)
    return 1;
  for (x = 0; x < 9; x++)
    {
      /* checa linha */
      usado[mat[i][x]] = 1;
      /* checa coluna */
      usado[mat[x][j]] = 1;
      /* (checa quadrado 3x3) */
      usado[mat[i/3*3+x/3][j/3*3+x%3]] = 1;
    }
  for (x = 1; x < 10; x++)
    {
      if (!usado[x])
	{
	  mat[i][j] = x;
	  if (resolve(mat, i, j))
	    return 1;
	}
    }
  mat[i][j] = 0;
  return 0;
}

int sudoku(int mat[9][9])
{
  int i,j, valor, casas;
  for (scanf (" %d", &casas); casas > 0; casas--)
    {
      scanf(" %d %d %d", &i, &j, &valor);
      mat[i-1][j-1] = valor;
    }
  return resolve(mat, 0, 0);
}

int main()
{
  int tabuleiro[9][9] = {{0}};  
  if (sudoku(tabuleiro))
    imprime(tabuleiro);
  else
    printf("Sem solucao\n");
  return 0;
}

