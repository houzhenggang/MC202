/*******************************************************************************
Pedro Emílio Machado de Brito - RA 137264
30/10/2012 - MC202 turma B

lab06 - Heap de intervalos

principal.c

Implementa e utiliza um heap de intervalos.
*******************************************************************************/


#include <stdio.h>

typedef struct 
{
  int dinheiro;
  char nome[41];
} cliente;

#define MAXCLIENT 130 

cliente heap[MAXCLIENT];
int clientes;

/* 
   O heap foi implementado de forma a armazenar os extremos em valores consecutivos do vetor
   dessa forma, o extremo esquerdo do primeiro nó fica em heap[0], o extremo direito em heap[1],
   o extremo esquerdo do segundo nó em heap[2] e por aí vai. Se o último nó tiver apenas um
   elemento, ficará armazenado na posição de menor índice. "clientes" conta os itens na fila.
*/

void sobe ( int no )
{
  int pai = (no/2-1)/2*2+no%2;
  /* salva o nó que deve subir */
  cliente temp = heap[no];
  while (no > 1 && (no % 2 ? heap[pai].dinheiro < temp.dinheiro : heap[pai].dinheiro > temp.dinheiro))
    {
      /* desce nó */
      heap[no] = heap[pai];
      /* calcula próximo nó a descer*/
      no = pai;
      pai = (no/2-1)/2*2+no%2;
    }
  /* grava o nó pra subir na posição adequada */
  heap[no] = temp;
}

void desce (int no)
{
  int filho;  
  cliente temp = heap[no];
  /* salva o nó que deve descer */  
  while ((filho = no/2*4+2) < clientes)
    {
      /* trata os casos de ser extremo direito ou esquerdo */
      switch (no%2)
	{
	  /* se for extremo esquerdo (do heap de mínimo) */
	case 0:
	  /* passa para o outro filho caso este seja menor */
	  if (filho + 2 < clientes && heap[filho+2].dinheiro < heap[filho].dinheiro)
	    filho += 2;
	  break;
	  /* se for extremo direito (do heap de máximo) */
	case 1:
	  if (filho + 1 < clientes)
	    filho++;
	  /* caso só haja filho a esquerda com número de elementos ímpar */
	  else
	    break;
	  /* se houver filho a direita com número de elementos par */
	  if (filho + 2 < clientes) 
	    { 
	      /* se este for maior, passa pra ele */
	      if( heap[filho+2].dinheiro > heap[filho].dinheiro)
		filho += 2;
	      /* caso contrário saia */
	      else
		break;
	    }
	  /* há filho direito porém o número de elementos é ímpar, passe sendo maior */
	  else if (filho + 1 < clientes && heap[filho+1].dinheiro > heap[filho].dinheiro)
	    filho += 1;
	}
      /* se é preciso continuar */
      if (no % 2 ? temp.dinheiro < heap[filho].dinheiro : temp.dinheiro > heap[filho].dinheiro )
	{
	  /* sobe um elemento */
	  heap[no] = heap[filho];
	  no = filho;
	  /* caso seja preciso, inverte a ordem dos elementos no nó */
	  if (no%2 ? heap[no-1].dinheiro > temp.dinheiro : no+1 < clientes && temp.dinheiro > heap[no+1].dinheiro )
	    {
	      heap[no] = heap[no+(no%2 ? -1 : 1)];
	      heap[no+(no%2 ? -1 : 1)] = temp;
	      temp = heap[no];
	    }
	}
      else
	/* terminou de subir */
	break;
    }
  /* grava o elemento a descer */
  heap[no] = temp;  
}

int insere( cliente novo )
{
  int pai;  
  if (clientes == MAXCLIENT)
    return -1;
  /* se houver número ímpar */
  if (clientes % 2)
    {
      /* insere conforme a ordem no heap */
      if (novo.dinheiro < heap[clientes-1].dinheiro)
	{
	  heap[clientes] = heap[clientes-1];
	  heap[clientes-1] = novo;
	  sobe(++clientes-2);
	}
      else
	{
	  heap[clientes++] = novo;
	  sobe(clientes-1);
	}
    }
  /* número par de elementos */
  else
    {
      /* pega o pai */
      pai = ((clientes)/2-1)/2*2;
      /* se for menor que o extremo esquerdo */
      if (clientes && novo.dinheiro < heap[pai].dinheiro)
	{
	  heap[clientes++] = heap[pai];
	  heap[pai] = novo;
	  sobe(pai);
	}
      /* se for maior que o extremo esquerdo */
      else if ( clientes && novo.dinheiro > heap[pai+1].dinheiro)
	{
	  heap[clientes++] = heap[pai+1];
	  heap[pai+1] = novo;
	  sobe(pai+1);
	}
      /* caso contrário simplesmente insere */
      else
	 { 
	  heap[clientes++] = novo;
	  sobe(clientes-1); 
	 } 
    }
  return 0;
}

/* retorna mínimo */

cliente pegaMin (void)
{
  return heap[0];
}
/* retorna máximo, que pode estar em heap[0] se houver apenas um elemento */
cliente pegaMax (void)
{
  return heap[clientes != 1];
}

/* remove o menor elemento e atualiza o heap */
void removeMin (void)
{
  heap[0] = heap[--clientes/2*2];
  heap[clientes/2*2] = heap[clientes/2*2+1];
  desce (0);
}

/* remove o maior elemento e atualiza o heap */
void removeMax (void)
{
  heap[1] = heap[--clientes];
  desce(1);
}

int main()
{
  char c;
  cliente entrada;
  while (scanf (" %c", &c) != EOF)
    {
      switch (c)
	{
	case 'A':
	  scanf (" %d", &entrada.dinheiro);
	  scanf (" %[^\n]", entrada.nome);
	  if (insere(entrada))
	    printf("Escritorio cheio\n");
	  break;
	case 'J':
	  if (clientes == 0)
	    {
	      printf("Escritorio vazio\n");
	      break;
	    }
	  entrada = pegaMin();
	  removeMin();	  
	  printf ("Joao vai atender %s (%d)\n", entrada.nome, entrada.dinheiro);
	  break;
	case 'M':
	  if (clientes == 0)
	    {
	      printf("Escritorio vazio\n");
	      break;
	    }
	  entrada = pegaMax();
	  removeMax();	  
	  printf ("Maria vai atender %s (%d)\n", entrada.nome, entrada.dinheiro);
	  break;
	case '#':
	  printf ("Ha %d clientes\n", clientes);
	  break;
	default:;
	}
    }
  return 0;
}

