#include "balloc.h"
#include <stdio.h>
/* Utilize as macros MALLOC e FREE para alocar e desalocar memória */

/* defines para utilizar as funções do balloc.h */
#define malloc MALLOC
#define free FREE

/* estrutura que define o aeroporto */

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
  /* caso de fila vazia */
  if (f->tamanho == 0)
      novo->prox = novo;
  /* caso de fila não vazia */
  else
    {
      novo->prox = f->final->prox;
      f->final->prox = novo;
    }
  /* move o ponteiro e incrementa tamanho */
  f->final = novo;
  f->tamanho++;
}
/* retorna o elemento na cabeça da fila, SEM RETIRÁ-LO */
/* NÃO USAR EM FILA VAZIA */
Aeronave pega (fila * f)
{
  return f->final->prox->aviao;
}

/* retorna no número de elementos atualmente */
int tamanho(fila * f)
{
  return f->tamanho;
}

/* apaga o elemento na cabeça da fila, retornando 0 em sucesso e -1 em caso de fila vazia */
int retira (fila * f)
{
  struct Fila_elemento * temp;
  if (!tamanho(f))
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

/* função que gerencia o aeroporto */

void aeroporto (char * entrada, int pistas)
{
  fila * decolagem = inicia(), * aterrissagem = inicia();
  int decolagens = 0, aterrissagens = 0, impedidos = 0, pistaParada = 0, esperaAterrissagem = 0, esperaDecolagem = 0;
  Aeronave temp = {1, 0};
  /* loop que avança os tempos */
  for (temp.tempoestampa = 0; *entrada != '\0' || tamanho(decolagem) || tamanho(aterrissagem) ; temp.tempoestampa++)
    {
      printf("Tempo %d\n",temp.tempoestampa);
      /* loop que lê as entradas do tempo correspondente */
      for (; *entrada != '\0'; entrada += 2) 
	{
	  /* novo tempo, avance para o próximo caractere da entrada e saia do loop */
	  if (*entrada == 'T')
	    {
	      entrada += 2;
	      break;
	    }
	  /* aterrissagem */
	  if (*entrada == 'A')
	    {
	      if (tamanho(aterrissagem) < 5)
		/* fila com espaço */
		{
		  printf ("%d entra na fila de aterrissagem\n", temp.id);
		  insere(aterrissagem, temp);
		}
	      else
		/* fila cheia */
		{
		  printf ("%d impedido de aterrissar\n", temp.id);
		  impedidos++;
		}
	    }
	  /* idem para o caso decolagem */
	  else 
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
	  /* avança o marcador de identificação do avião */
	  temp.id++;
	}
      /* caso haja avião esperando para aterrisar */
      if (tamanho(aterrissagem))
	{
	  printf ("%d aterrissa\n",pega(aterrissagem).id);
	  aterrissagens++;
	  esperaAterrissagem += temp.tempoestampa - pega(aterrissagem).tempoestampa;
	  retira(aterrissagem);
	  /* se há apenas uma pista, acaba por aqui */
	  if (pistas == 1)
	    continue;
	}
      else if (pistas == 2)
	{
	  printf ("Pista de aterrissagem parada\n");
	  pistaParada++;
	}
      /* caso haja avião esperando para decolar */
      if (tamanho(decolagem))
	{
	  printf ("%d decola\n",pega(decolagem).id);
	  decolagens++;
	  esperaDecolagem +=  temp.tempoestampa - pega(decolagem).tempoestampa;
	  retira(decolagem);
	}
      else
	{
	  /*caso contrário, imprime a mensagem adequada de acordo com o número de pistas */
	  printf ("Pista %sparada\n", pistas == 2 ? "de decolagem ": "");
	  pistaParada++;
	}
    }
  /* imprime mensagens de fim de simulação */
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
  char leitura[200] = "";
  /* o caractere 'F' é descartado, testa-se o caractere nulo pra verificar fim */
  scanf( " %[^F]", leitura);
  /* chama a função do aeroporto para os dois casos */
  printf ("Aeroporto com uma pista\n\n");
  aeroporto (leitura, 1);
  printf ("\nAeroporto com duas pistas\n\n");
  aeroporto (leitura, 2);
  bapply(bprint); /* não modifique esta linha */
  return 0;
}
