#include "balloc.h"
#include <stdio.h>
/* Utilize as macros MALLOC e FREE para alocar e desalocar memória */

/* #define malloc MALLOC */
/* #define free FREE */
#define DUASPISTAS

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
  fila  * decolagem, * aterrissagem, *trafego, *temp;
  char leitura = 0;
  Aeronave entrada  = {1, 0};
  decolagem = inicia();
  aterrissagem = inicia();
  trafego = inicia();
  temp = inicia();
  int pistaParada = 0, esperaDecolagem = 0, esperaAterrissagem = 0, decolagens = 0, aterrissagens = 0, impedidos = 0;
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
  entrada.tipo = 'F';
  insere(trafego, entrada);
  entrada.tempoestampa = 0;
  
  /* trafego já tem nossa fila de aviões com os respectivos tempos */
  printf ("Aeroporto com uma pista\n\n");
  while (tamanho(trafego) || tamanho(decolagem) || tamanho(aterrissagem))
    {
      printf("Tempo %d\n",entrada.tempoestampa);
      while ( pega(trafego).tempoestampa == entrada.tempoestampa) 
	{
	    if (pega(trafego).tipo == 'A')
	      {
		if (tamanho(aterrissagem) < 5)
		  {
		    printf ("%d entra na fila de aterrissagem\n", pega(trafego).id);
		    insere(aterrissagem, pega(trafego));
		  }
		else
		  {
		    printf ("%d impedido de aterrissar\n", pega(trafego).id);
		    impedidos++;
		  }
	      }
	    else if (pega(trafego).tipo == 'D')
	      {
		if (tamanho(decolagem) < 5)
		  {
		    printf ("%d entra na fila de decolagem\n", pega(trafego).id);
		    insere(decolagem, pega(trafego));
		  }
		else
		  {
		    printf ("%d impedido de decolar\n", pega(trafego).id);
		    impedidos++;
		  }
	      }
	    insere(temp, entrada = pega(trafego));
	    retira(trafego);
	}
      if (tamanho(aterrissagem) == 0)
	{
	  if (tamanho(decolagem) == 0)
	    {
	      printf ("Pista parada\n");
	      pistaParada++;
	    }
	  else
	    {
	      printf ("%d decola\n",pega(decolagem).id);
	      decolagens++;
	      esperaDecolagem +=  entrada.tempoestampa - pega(decolagem).tempoestampa;
	      retira(decolagem);
	    }
	}
      else
	{
	  printf ("%d aterrissa\n",pega(aterrissagem).id);
	  aterrissagens++;
	  esperaAterrissagem += entrada.tempoestampa - pega(aterrissagem).tempoestampa;
	  retira(aterrissagem);
	}
      entrada.tempoestampa++;
    }
  printf ("\nnumero de decolagens = %d\n", decolagens);
  printf ("numero de aterrissagens = %d\n", aterrissagens);
  printf ("avioes impedidos de usar o aeroporto = %d\n", impedidos);
  printf ("tempo de pista parada = %d\n", pistaParada);
  printf ("tempo medio de espera para aterrissar = %.2f\n", esperaAterrissagem/(float)aterrissagens);
  printf ("tempo medio de espera para decolar = %.2f\n", esperaDecolagem/(float)decolagens);
  libera(trafego);
  trafego = temp;
  decolagens = aterrissagens = impedidos = pistaParada = esperaAterrissagem = esperaDecolagem = entrada.tempoestampa = 0;
  /* duas pistas */
  #ifdef DUASPISTAS
  printf ("\nAeroporto com duas pistas\n\n");
  while (tamanho(trafego) || tamanho(decolagem) || tamanho(aterrissagem))
    {
      printf("Tempo %d\n",entrada.tempoestampa);
      while ( pega(trafego).tempoestampa == entrada.tempoestampa) 
	{
	    if (pega(trafego).tipo == 'A')
	      {
		if (tamanho(aterrissagem) < 5)
		  {
		    printf ("%d entra na fila de aterrissagem\n", pega(trafego).id);
		    insere(aterrissagem, pega(trafego));
		  }
		else
		  {
		    printf ("%d impedido de aterrissar\n", pega(trafego).id);
		    impedidos++;
		  }
	      }
	    else if (pega(trafego).tipo == 'D')
	      {
		if (tamanho(decolagem) < 5)
		  {
		    printf ("%d entra na fila de decolagem\n", pega(trafego).id);
		    insere(decolagem, pega(trafego));
		  }
		else
		  {
		    printf ("%d impedido de decolar\n", pega(trafego).id);
		    impedidos++;
		  }
	      }
	    retira(trafego);
	}
      if(tamanho(aterrissagem))
	{
	  printf ("%d aterrissa\n",pega(aterrissagem).id);
	  aterrissagens++;
	  esperaAterrissagem += entrada.tempoestampa - pega(aterrissagem).tempoestampa;
	  retira(aterrissagem);
	}
      else
	{
	  printf ("Pista de aterrissagem parada\n");
	  pistaParada++;
	}
      if(tamanho(decolagem))
	{
	  printf ("%d decola\n",pega(decolagem).id);
	  decolagens++;
	  esperaDecolagem +=  entrada.tempoestampa - pega(decolagem).tempoestampa;
	  retira(decolagem);
	}
      else
	{
	  printf ("Pista de decolagem parada\n");
	  pistaParada++;
	}
      entrada.tempoestampa++;
    }
  printf ("\nnumero de decolagens = %d\n", decolagens);
  printf ("numero de aterrissagens = %d\n", aterrissagens);
  printf ("avioes impedidos de usar o aeroporto = %d\n", impedidos);
  printf ("tempo de pista parada = %d\n", pistaParada);
  printf ("tempo medio de espera para aterrissar = %.2f\n", esperaAterrissagem/(float)aterrissagens);
  printf ("tempo medio de espera para decolar = %.2f\n", esperaDecolagem/(float)decolagens);
  libera(trafego);
#endif
  libera(decolagem);
  libera(aterrissagem);
  bapply(bprint); //não modifique esta linha
  return 0;
}
