#include "balloc.h"
#include <stdio.h>
/* Utilize as macros MALLOC e FREE para alocar e desalocar memória */

/* defines para utilizar as funções do balloc.h */
/* #define malloc MALLOC  */
/* #define free FREE */

typedef struct 
{
  int id;
  int tempoestampa;
} Aeronave;

/*
Estrutura da fila: Ponteiro aponta para a entrada da fila, que aponta para a saída.
*/

/* estrutura que guarda cada nó da fila */
struct Fila_elemento
{
  Aeronave aviao;
  struct Fila_elemento * prox;
};

/* estrutura que guarda informação sobre o tamanho atual da fila e seu nó final */
typedef struct
{
  int tamanho;
  struct Fila_elemento * final;
} fila;

/* inicia uma fila */
fila * inicia (void)
{
  fila * novo = malloc(sizeof(fila));
  novo->tamanho = 0;
  return novo;
}

/*insere um elemento no fim da fila */
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
/* retorna o elemento na cabeça da fila, SEM RETIRÁ-LO */
Aeronave pega (fila * f)
{
  Aeronave erro = {-1, -1};
  if (f->tamanho == 0)
     return erro;
  return f->final->prox->aviao;
}

/* apaga o elemento na cabeça da fila, retornando 0 em sucesso e -1 em caso de fila vazia */
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

/* libera toda a memória alocada para uma fila */
void libera(fila * f)
{
  while (!retira(f));
  free (f);
}
/* retorna no número de elementos atualmente */
int tamanho(fila * f)
{
  return f->tamanho;
}

/* função que gerencia o aeroporto */

void aeroporto (char * entrada, int pistas)
{
  fila * decolagem = inicia(), * aterrissagem = inicia();
  int decolagens = 0, aterrissagens = 0, impedidos = 0, pistaParada = 0, esperaAterrissagem = 0, esperaDecolagem = 0;
  Aeronave temp;
  temp.id = 0;
  for (temp.tempoestampa = 0; *entrada != '\0' || tamanho(decolagem) || tamanho(aterrissagem); temp.tempoestampa++)
    {
      printf("Tempo %d\n",temp.tempoestampa);
      for (; *entrada != '\0'; entrada++) 
	{
	  if (*entrada == ' ')
	    continue;
	  if (*entrada == 'T')
	    {
	      entrada++;
	      break;
	    }
	  temp.id++;
	  if (*entrada == 'A')
	    {
	      if (tamanho(aterrissagem) < 5)
		{
		  printf ("%d entra na fila de aterrissagem\n", temp.id);
		  insere(aterrissagem, temp);
		}
	      else
		{
		  printf ("%d impedido de aterrissar\n", temp.id);
		  impedidos++;
		}
	    }
	  else if (*entrada == 'D')
	    {
	      if (tamanho(decolagem) < 5)
		{
		  printf ("%d entra na fila de decolagem\n", temp.id);
		  insere(decolagem, temp);
		}
	      else
		{
		  printf ("%d impedido de decolar\n", temp.id);
		  impedidos++;
		}
	    }
	}
      if (tamanho(aterrissagem))
	{
	  printf ("%d aterrissa\n",pega(aterrissagem).id);
	  aterrissagens++;
	  esperaAterrissagem += temp.tempoestampa - pega(aterrissagem).tempoestampa;
	  retira(aterrissagem);
	  if (pistas == 1)
	    continue;
	}
      else if (pistas == 2)
	{
	  printf ("Pista de aterrissagem parada\n");
	  pistaParada++;
	}
      if (tamanho(decolagem))
	{
	  printf ("%d decola\n",pega(decolagem).id);
	  decolagens++;
	  esperaDecolagem +=  temp.tempoestampa - pega(decolagem).tempoestampa;
	  retira(decolagem);
	}
      else
	{
	  printf ("Pista %sparada\n", pistas == 2 ? "de decolagem ": "");
	  pistaParada++;
	}
    }
  printf ("\nnumero de decolagens = %d\n", decolagens);
  printf ("numero de aterrissagens = %d\n", aterrissagens);
  printf ("avioes impedidos de usar o aeroporto = %d\n", impedidos);
  printf ("tempo de pista parada = %d\n", pistaParada);
  printf ("tempo medio de espera para aterrissar = %.2f\n", esperaAterrissagem/(float)aterrissagens);
  printf ("tempo medio de espera para decolar = %.2f\n", esperaDecolagem/(float)decolagens);
  libera(decolagem);
  libera(aterrissagem);
}

int main(){
  char * leitura;
  scanf( " %m[^F]", &leitura);
  printf ("Aeroporto com uma pista\n\n");
  aeroporto (leitura, 1);
  /* duas pistas */
  printf ("\nAeroporto com duas pistas\n\n");
  aeroporto (leitura, 2);
  free(leitura);
  bapply(bprint); /* não modifique esta linha */
  return 0;
}
