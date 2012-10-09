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
  for(i=0; i<9; i++)
    {
      for(j=0; j<9; j++)
	  printf("%d", mat[i][j]);
      putchar('\n');
    }
  return;
}

int resolve(int mat[9][9])
{
  short testa, pilha[81][2] = {{0}}, linha[9][10] = {{0}}, coluna[9][10] = {{0}}, quadrado[3][3][10] = {{{0}}}, pos = 0, max, i, j;
  for (i = 0; i < 9; i++)
    {
      for (j = 0; j < 9; j++)
	{
	  if (mat[i][j])
	    {
	      linha[i][mat[i][j]] = 1;
	      coluna[j][mat[i][j]] = 1;
	      quadrado[i/3][j/3][mat[i][j]] = 1;
	    }
	  else
	    {
	      pilha[pos][0] = i;
	      pilha[pos][1] = j;
	      pos++;
	    }
	}
    }
  max = pos;
  pos = 0;
  while (pos >= 0 && pos < max)
    {
      i = pilha[pos][0];
      j = pilha[pos][1];
      testa = mat[i][j];
       if (testa) 
	  linha[i][mat[i][j]] = coluna[j][mat[i][j]] = quadrado[i/3][j/3][mat[i][j]] = 0;
      while (testa < 9)
	{
	  testa++;
	  if (!(linha[i][testa] || coluna[j][testa] || quadrado[i/3][j/3][testa]))
	    {
	      linha[i][testa] = coluna[j][testa] = quadrado[i/3][j/3][testa] = 1;
	      mat[i][j] = testa;
	      pos++;	      
	      goto stack;	      
	    }
	}
      mat[i][j] = 0;      
      pos--;
    stack:;
    }
  if (pos == max)
    return 1;
  return 0;
}


int main()
{
  int mat[9][9], x, y, v, casos;
  for (scanf ("%d", &casos); casos > 0; casos--)
    {
      for (x = 0; x < 9; x++)
	for (y = 0; y < 9; y++)
	  {
	    scanf(" %1d",&v);
	    mat[x][y] = v;
	  }
      resolve(mat);
      imprime(mat);
    }
  return 0;
}

