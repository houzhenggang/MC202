/*******************************************************************************
Pedro Emílio Machado de Brito - RA 137264
31/08/2012 - MC202 turma B

lab02 - Aeroporto

O programa a seguir simula o funcionamento de um aeroporto, usando filas para
organizar a decolagem e aterrissagem de aviões.
*******************************************************************************/

#include "balloc.h"
#include <stdio.h>
/* Utilize as macros MALLOC e FREE para alocar e desalocar memória */

/* estrutura que define um avião */
typedef struct 
{
  int id;
  int tempoestampa;
} Aeronave;

/* estrutura da fila */
typedef struct
{
  #define MAX 5
  Aeronave aviao[MAX+1];
  int entrada;
  int saida;
} fila;

/* inicia uma fila */
fila * inicia (void)
{
  fila * novo = MALLOC(sizeof(fila));
  novo->entrada = novo->saida = 0;
  return novo;
}

/*insere um elemento no fim da fila, retorna 0 em sucesso, -1 em falha */
int insere(fila * f, Aeronave a)
{
  if ((f->entrada+1) % (MAX + 1) == f->saida)
    return -1;
  f->aviao[f->entrada] = a;
  f->entrada = (f->entrada + 1) % (MAX + 1);
  return 0;
}

/* retorna se a fila está vazia */
int vazia (fila * f)
{
  return f->entrada == f->saida;
}

/* retorna cópia para o elemento da ponta da fila */
Aeronave pega (fila * f)
{
  return f->aviao[f->saida];
}

/* apaga o elemento na cabeça da fila, retornando 0 em sucesso e -1 em caso de fila vazia */
int retira (fila * f)
{
  if (f->saida == f->entrada)
    return -1;
  f->saida = (f->saida + 1) % (MAX + 1);
  return 0;
}

/* libera a memória alocada para uma fila */
void libera(fila * f)
{
  FREE(f);
}

/* função que gerencia o aeroporto */
void aeroporto (char * entrada, int pistas)
{
  fila * decolagem = inicia(), * aterrissagem = inicia();
  int decolagens = 0, aterrissagens = 0, impedidos = 0, pistaParada = 0, esperaAterrissagem = 0, esperaDecolagem = 0;
  Aeronave temp = {1, 0};
  /* loop que avança os tempos */
  for (; *entrada != '\0' || !(vazia(decolagem) && vazia(aterrissagem)) ; temp.tempoestampa++)
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
	      if (insere(aterrissagem,temp))
		/* fila cheia */
		{
		  printf ("%d impedido de aterrissar\n", temp.id);
		  impedidos++;
		}
	      else
		/* fila com espaço */
		printf ("%d entra na fila de aterrissagem\n", temp.id);

	    }
	  /* idem para o caso decolagem */
	  else 
	    {
	      if (insere(decolagem, temp))
		{
		  printf ("%d impedido de decolar\n", temp.id);
		  impedidos++;
		}
	      else
		printf ("%d entra na fila de decolagem\n", temp.id);
	    }
	  /* avança o marcador de identificação do avião */
	  temp.id++;
	}
      /* caso haja avião esperando para aterrisar */
      if (!vazia(aterrissagem))
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
      if (!vazia(decolagem))
	{
	  printf ("%d decola\n",pega(decolagem).id);
	  decolagens++;
	  esperaDecolagem +=  temp.tempoestampa - pega(decolagem).tempoestampa;
	  retira(decolagem);
	}
      else
	{
	  /*imprime a mensagem adequada de acordo com o número de pistas */
	  printf ("Pista %sparada\n", pistas == 2 ? "de decolagem " : "");
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
  /* o caractere 'F' é descartado */
  scanf( " %[^F]", leitura);
  /* chama a função do aeroporto para os dois casos */
  printf ("Aeroporto com uma pista\n\n");
  aeroporto (leitura, 1);
  printf ("\nAeroporto com duas pistas\n\n");
  aeroporto (leitura, 2);
  bapply(bprint); /* não modifique esta linha */
  return 0;
}
