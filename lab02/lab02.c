#include "balloc.h"
#include <stdio.h>
/* Utilize as macros MALLOC e FREE para alocar e desalocar memória */

/* #define malloc MALLOC */
/* #define free FREE */

typedef struct 
{
  int id;
  int tempoestampa;
  char tipo;
} Aeronave;

/* Aeronave listavazia =  */
/*   { */
/*     -1; */
/*     -1; */
/*   } */
  

struct Fila_elemento
{
  Aeronave aviao;
  struct Fila_elemento * prox;
};

typedef struct
{
  int tamanho;
  struct Fila_elemento * final;
} fila;


/*******************************************************************************
Estrutura da fila: Ponteiro aponta para a entrada da fila, que aponta para a saída.
*******************************************************************************/

fila * inicia (void)
{
  fila * novo = malloc(sizeof(fila));
  novo->tamanho = 0;
  return novo;
}

void insere(fila * f, Aeronave a)
{
  struct Fila_elemento * novo = (struct Fila_elemento *) malloc(sizeof(struct Fila_elemento));
  novo->aviao = a;
  if (f->tamanho == 0)
      novo->prox = novo;
  else
    {
      novo->prox = f->final->prox;
      f->final->prox = novo;
    }
  f->final = novo;
  f->tamanho++;
}

Aeronave pega (fila * f)
{
  Aeronave erro = {-1, -1, 'E'};
  if (f->tamanho == 0)
     return erro;
  return f->final->prox->aviao;
}

int retira (fila * f)
{
  struct Fila_elemento * temp;
  if (f->tamanho == 0)
    return -1;
  temp = f->final->prox;
  f->final->prox = temp->prox;
  f->tamanho--;
  free(temp);
  return 0;
}

void libera(fila * f)
{
  while (!retira(f));
  free (f);
}

int tamanho(fila * f)
{
  return f->tamanho;
}


int main(){
  fila  * decolagem, * aterrisagem, *store, *duaspistas;
  char leitura = 0;
  Aeronave entrada  = {1, 0};
  float so;
  decolagem = inicia();
  aterrisagem = inicia();
  store = inicia();
  duaspistas = inicia();
  int pistaParada = 0, esperaDecolagem = 0, esperaAterrisagem = 0;
  do 
    {
      scanf ("%c", &leitura);
      switch (leitura)
	{
	case 'A':
	case 'D':
	  entrada.tipo = leitura;
	  insere( store, entrada);
	  entrada.id++;
	  break;
	case 'T':
	  entrada.tempoestampa++;
	  break;
	default:
	  break;
	}
    } while (leitura != 'F');
  entrada.tipo = 'F';
  insere(store, entrada);
  entrada.tempoestampa = 0;
  
  /* store já tem nossa fila de aviões com os respectivos tempos */
  printf ("Aeroporto com uma pista\n\n");
  while (tamanho(store) || tamanho(decolagem) || tamanho(aterrisagem))
    {
      printf("Tempo %d\n",entrada.tempoestampa);
      while ( pega(store).tempoestampa == entrada.tempoestampa) 
	{
	    if (pega(store).tipo == 'A')
	      {
		if (tamanho(aterrisagem) < 5)
		  {
		    printf ("%d entra na fila de aterrissagem\n", pega(store).id);
		    insere(aterrisagem, pega(store));
		  }
		else
		  printf ("%d impedido de aterrisar\n", pega(store).id);
	      }
	    else if (pega(store).tipo == 'D')
	      {
		if (tamanho(decolagem) < 5)
		  {
		    printf ("%d entra na fila de decolagem\n", pega(store).id);
		    insere(decolagem, pega(store));
		  }
	      else
		printf ("%d impedido de decolar\n", pega(store).id);
	      }
	    insere(duaspistas, entrada = pega(store));
	    retira(store);
	}
      if (tamanho(aterrisagem) == 0)
	{
	  if (tamanho(decolagem) == 0)
	    {
	      printf ("Pista parada\n");
	      pistaParada++;
	    }
	  else
	    {
	      printf ("%d decola\n",pega(decolagem).id);
	      esperaDecolagem += pega(decolagem).tempoestampa - entrada.tempoestampa;
	      retira(decolagem);
	    }
	}
      else
	{
	  printf ("%d aterrisa\n",pega(aterrisagem).id);
	  esperaAterrisagem += pega(aterrisagem).tempoestampa - entrada.tempoestampa;
	  retira(aterrisagem);
	}
      entrada.tempoestampa++;
    }
  libera(store);
  libera(decolagem);
  libera(aterrisagem);
  libera(duaspistas);
  bapply(bprint); //não modifique esta linha
  return 0;
}
