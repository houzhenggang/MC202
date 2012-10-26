#include <stdio.h>

typedef struct 
{
  int dinheiro;
  char nome[41];
} cliente;

#define MAXCLIENT 130 

cliente heap[MAXCLIENT];
int clientes;

void sobe ( int no )
{
  int pai = (no/2-1)/2*2+no%2; /* checar se funciona! */
  cliente temp = heap[no];
  while (no > 0 && (no % 2 ? heap[pai].dinheiro < temp.dinheiro : heap[pai].dinheiro > temp.dinheiro))
    {
      heap[no] = heap[pai];
      no = pai;
      pai = (no/2-1)/2*2+no%2;
    }
  heap[no] = temp;
}

void desce (int no)
{
  int filho = no/2*4+2+no%2;
  cliente temp = heap[no];
  while (filho < clientes)
    {
      
      if (filho + 2 < clientes && (no % 2 ? heap[filho].dinheiro < heap[filho+2].dinheiro : heap[filho].dinheiro > heap[filho+2].dinheiro))
	filho += 2;
      if (no % 2 ? temp.dinheiro < heap[filho].dinheiro : temp.dinheiro > heap[filho].dinheiro )
	{
	  heap[no] = heap[filho];
	  no = filho;
	  filho = no/2*4+2+no%2;
	}
      else
	break;
    }
  heap[no] = temp;  
}

int insere( cliente novo )
{
  if (clientes == MAXCLIENT)
    return -1;  
  if (clientes % 2 && novo.dinheiro < heap[clientes-1].dinheiro)
    {
      heap[clientes] = heap[clientes-1];
      heap[clientes++ - 1] = novo;
    }
  else
    heap[clientes++] = novo;
  if (!(clientes%2))
    sobe( clientes-1 );
  sobe( clientes );
  return 0;
}

cliente pegaMin (void)
{
  return heap[0];
}

cliente pegaMax (void)
{
  if (clientes == 1)
    return heap[0];
  return heap[1];
}

void removeMin (void)
{
  heap[0] = heap[clientes/2*2-1];
  if (!(clientes%2))
    heap[clientes-2] = heap[clientes-1];
  clientes--;
  desce (0);
}


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
	  printf ("Joao vai atender %s (%d)\n", entrada.nome, entrada.dinheiro);
	  break;
	case 'M':
	  if (clientes == 0)
	    {
	      printf("Escritorio vazio\n");
	      break;
	    }
	  entrada = pegaMax();
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



