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
  int percorre = 0, usado[10] = {0};
  /* loop que procura o próximo dígito a ser determinado */
  do
    {
      do
	{
	  /* achou dígito zerado */
	  if (!mat[i][j])
	    {
	      /* usa "percorre" como flag pra sair do loop aninhado */
	      percorre = 1;
	      break;
	    }
	  /* avança coluna */
	  (j)++;
	}
      while ( j < 9);
      if (percorre)
	break;
      /* reseta coluna e avança linha */
      j = 0;
      i++;
    }
  while (i < 9);
  /* se chegamos ao fim do tabuleiro (caso básico), uma solução foi encontrada */
  if (i == 9)
    return 1;
  /* elimina os dígitos já usados na linha, coluna e quadrado 3x3 */
  for (percorre = 0; percorre < 9; percorre++)
    {
      /* percorre linha */
      usado[mat[i][percorre]] = 1;
      /* percorre coluna */
      usado[mat[percorre][j]] = 1;
      /* percorre quadrado 3x3 */
      usado[mat[i/3*3+percorre/3][j/3*3+percorre%3]] = 1;
    }
  /* agora usado[x] == 0 se x é um dígito válido para essa posição */
  /* loop testa cada um dos dígitos e chama a recursão para o restante do tabuleiro */
  for (percorre = 1; percorre < 10; percorre++)
    {
      if (!usado[percorre])
	{
	  /* põe o dígito na posição */
	  mat[i][j] = percorre;
	  /* chama a recursão para o restante do tabuleiro */
	  if (resolve(mat, i, j))
	    /* se é solução retorna imediatamente */
	    return 1;
	}
    }
  /* se chegamos aqui, não há solução para o estado atual do tabuleiro */
  /* a posição atual do tabuleiro volta ao valor inicial e retorna falha */
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

