#include "balloc.h"
#include <stdio.h>
/* Utilize as macros MALLOC e FREE para alocar e desalocar memória */

/* defines para utilizar as funções do balloc.h */
#define malloc MALLOC 
#define free FREE


typedef struct 
{
  int id;
  int tempoestampa;
  char tipo;
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
  Aeronave erro = {-1, -1, 'E'};
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

/* função de separagem em duas filas */

int enfileira(fila * aterrissagem, fila * decolagem, fila * entrada, int tempo, fila * saida)
{
  int impedidos = 0;
  while (tamanho(entrada) && pega(entrada).tempoestampa == tempo) 
    {
      if (pega(entrada).tipo == 'A')
	{
	  if (tamanho(aterrissagem) < 5)
	    {
	      printf ("%d entra na fila de aterrissagem\n", pega(entrada).id);
	      insere(aterrissagem, pega(entrada));
	    }
	  else
	    {
	      printf ("%d impedido de aterrissar\n", pega(entrada).id);
	      impedidos++;
	    }
	}
      else if (pega(entrada).tipo == 'D')
	{
	  if (tamanho(decolagem) < 5)
	    {
	      printf ("%d entra na fila de decolagem\n", pega(entrada).id);
	      insere(decolagem, pega(entrada));
	    }
	  else
	    {
	      printf ("%d impedido de decolar\n", pega(entrada).id);
	      impedidos++;
	    }
	}
      if (saida != NULL)
	insere(saida, pega(entrada));
      retira(entrada);
    }
  return impedidos;
}

/* função que gerencia o aeroporto */

void aeroporto (fila * entrada, fila * saida, int pistas)
{
  fila * decolagem = inicia(), * aterrissagem = inicia();
  int tempo = 0, decolagens = 0, aterrissagens = 0, impedidos = 0, pistaParada = 0, esperaAterrissagem = 0, esperaDecolagem = 0;
  for (; tamanho(entrada) || tamanho(decolagem) || tamanho(aterrissagem); tempo++)
    {
      printf("Tempo %d\n",tempo);
      impedidos += enfileira (aterrissagem, decolagem, entrada, tempo, saida);
      if (tamanho(aterrissagem))
	{
	  printf ("%d aterrissa\n",pega(aterrissagem).id);
	  aterrissagens++;
	  esperaAterrissagem += tempo - pega(aterrissagem).tempoestampa;
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
	  esperaDecolagem +=  tempo - pega(decolagem).tempoestampa;
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
  fila  * decolagem, * aterrissagem, *trafego, *temp;
  char leitura = 0;
  Aeronave entrada  = {1, 0};
  /* inicia as 4 filas que serão usadas */
  decolagem = inicia();
  aterrissagem = inicia();
  trafego = inicia();
  temp = inicia();
  int pistaParada = 0, esperaDecolagem = 0, esperaAterrissagem = 0, decolagens = 0, aterrissagens = 0, impedidos = 0;
  /* loop lê a entrada e gera elementos iniciais da fila */
  do 
    {
      scanf ("%c", &leitura);
      switch (leitura)
	{
	case 'A':
	case 'D':
	  entrada.tipo = leitura;
	  insere( trafego, entrada);
	  entrada.id++;
	  break;
	case 'T':
	  entrada.tempoestampa++;
	  break;
	default:
	  break;
	}
    } while (leitura != 'F');
  /*a partir de agora entrada.tempoestampa guarda o tempo atual*/
  entrada.tempoestampa = 0;
  
  /* trafego já tem nossa fila de aviões com os respectivos tempos */
  printf ("Aeroporto com uma pista\n\n");
  aeroporto (trafego, temp, 1);
  /* while (tamanho(trafego) || tamanho(decolagem) || tamanho(aterrissagem)) */
  /*   { */
  /*     printf("Tempo %d\n",entrada.tempoestampa); */
  /*     impedidos += enfileira (aterrissagem, decolagem, trafego, entrada.tempoestampa, temp); */
  /*     if (tamanho(aterrissagem) == 0) */
  /* 	{ */
  /* 	  if (tamanho(decolagem) == 0) */
  /* 	    { */
  /* 	      printf ("Pista parada\n"); */
  /* 	      pistaParada++; */
  /* 	    } */
  /* 	  else */
  /* 	    { */
  /* 	      printf ("%d decola\n",pega(decolagem).id); */
  /* 	      decolagens++; */
  /* 	      esperaDecolagem +=  entrada.tempoestampa - pega(decolagem).tempoestampa; */
  /* 	      retira(decolagem); */
  /* 	    } */
  /* 	} */
  /*     else */
  /* 	{ */
  /* 	  printf ("%d aterrissa\n",pega(aterrissagem).id); */
  /* 	  aterrissagens++; */
  /* 	  esperaAterrissagem += entrada.tempoestampa - pega(aterrissagem).tempoestampa; */
  /* 	  retira(aterrissagem); */
  /* 	} */
  /*     entrada.tempoestampa++; */
  /*   } */
  /* printf ("\nnumero de decolagens = %d\n", decolagens); */
  /* printf ("numero de aterrissagens = %d\n", aterrissagens); */
  /* printf ("avioes impedidos de usar o aeroporto = %d\n", impedidos); */
  /* printf ("tempo de pista parada = %d\n", pistaParada); */
  /* printf ("tempo medio de espera para aterrissar = %.2f\n", esperaAterrissagem/(float)aterrissagens); */
  /* printf ("tempo medio de espera para decolar = %.2f\n", esperaDecolagem/(float)decolagens); */
  libera(trafego);
  trafego = temp;
  decolagens = aterrissagens = impedidos = pistaParada = esperaAterrissagem = esperaDecolagem = entrada.tempoestampa = 0;
  /* duas pistas */
  printf ("\nAeroporto com duas pistas\n\n");
  aeroporto (trafego, NULL, 2);
  /* while (tamanho(trafego) || tamanho(decolagem) || tamanho(aterrissagem)) */
  /*   { */
  /*     printf("Tempo %d\n",entrada.tempoestampa); */
  /*     impedidos += enfileira (aterrissagem, decolagem, trafego, entrada.tempoestampa, NULL); */
  /*     if(tamanho(aterrissagem)) */
  /* 	{ */
  /* 	  printf ("%d aterrissa\n",pega(aterrissagem).id); */
  /* 	  aterrissagens++; */
  /* 	  esperaAterrissagem += entrada.tempoestampa - pega(aterrissagem).tempoestampa; */
  /* 	  retira(aterrissagem); */
  /* 	} */
  /*     else */
  /* 	{ */
  /* 	  printf ("Pista de aterrissagem parada\n"); */
  /* 	  pistaParada++; */
  /* 	} */
  /*     if(tamanho(decolagem)) */
  /* 	{ */
  /* 	  printf ("%d decola\n",pega(decolagem).id); */
  /* 	  decolagens++; */
  /* 	  esperaDecolagem +=  entrada.tempoestampa - pega(decolagem).tempoestampa; */
  /* 	  retira(decolagem); */
  /* 	} */
  /*     else */
  /* 	{ */
  /* 	  printf ("Pista de decolagem parada\n"); */
  /* 	  pistaParada++; */
  /* 	} */
  /*     entrada.tempoestampa++; */
  /*   } */
  /* printf ("\nnumero de decolagens = %d\n", decolagens); */
  /* printf ("numero de aterrissagens = %d\n", aterrissagens); */
  /* printf ("avioes impedidos de usar o aeroporto = %d\n", impedidos); */
  /* printf ("tempo de pista parada = %d\n", pistaParada); */
  /* printf ("tempo medio de espera para aterrissar = %.2f\n", esperaAterrissagem/(float)aterrissagens); */
  /* printf ("tempo medio de espera para decolar = %.2f\n", esperaDecolagem/(float)decolagens); */
  libera(trafego);
  libera(decolagem);
  libera(aterrissagem);
  bapply(bprint); /* não modifique esta linha */
  return 0;
}
