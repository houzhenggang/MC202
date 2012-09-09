#include "grandeint.h"
#include "lista.h"
#include "balloc.h"
#include <stdlib.h>

struct grandeintS{
  lista digitos;
  char sinal;
};

grandeint iniciagi(void)
{
  grandeint n = (grandeint) MALLOC(sizeof(struct grandeintS));
  if (NULL == n)
    return n;
  if (NULL == (n->digitos = inicia()))
    {
      FREE(n);
      return NULL;
    }
  n->sinal = 1;
  return n;
}

grandeint itogi(int init)
{
  grandeint n = iniciagi();  
    if (n == NULL)
      return NULL;
  if (init < 0)
    {
      init *= -1;
      n->sinal = -1;
    }
  while (init)
    {
      if (insere(n->digitos, (void *) (init%10), tamanho(n->digitos)))
	{
	  libera(n->digitos);
	  FREE(n);
	  return NULL;
	}
      init = init/10;
    }
  return n;
}

grandeint atogi(char * string)
{
  grandeint n = iniciagi();
  if (n == NULL)
    return NULL;
  switch (*string)
    {
    case '+':
      string++;
      break;
    case '-':
      n->sinal = -1;
      string++;
      break;
    default:
      break;
    }
  while (*string == '0')
    string++;
  while (*string != '\0')
    {      
      if (insere(n->digitos, (void *) (*string - '0'), 0))
	{
	  libera(n->digitos);
	  FREE(n);
	  return NULL;
	}
      string++;
    }
  return n;
}


char * gitoa(grandeint n)
{
  int tam;
  char * string , *anda;
  if (n == NULL)
    return NULL;
  tam = tamanho(n->digitos);
    anda = string = (char *) MALLOC(sizeof(char)*(1 + tam + !tamanho(n->digitos) + (n->sinal == -1)));
  if (n->sinal == -1)
    *(anda++) = '-';
  if (!tamanho(n->digitos))
    *(anda++) = '0';
  while(tam)
    *(anda++) = (char) pega(n->digitos,--tam) + '0';
  *anda = '\0';
  return string;
}

/* ints vão estourar seu burro */
grandeint mais(grandeint gi1, grandeint gi2)
{
  grandeint resultado = iniciagi();
  int parcial = 0, casa;
  /* if(gi1->sinal != gi2->sinal) */
  /*   return menos(gi1, gi2); */
  for (casa = 0;  parcial || tamanho(gi1->digitos) - casa > 0 || tamanho(gi2->digitos) - casa > 0; casa++ )
    {
      parcial += (int) pega(gi1->digitos,casa) + (int) pega(gi2->digitos,casa);
      insere(resultado->digitos,(void *) abs(parcial%10), tamanho(resultado->digitos));
      parcial /= 10;
    }
  resultado->sinal = gi1->sinal;  
  return resultado;
}

void liberagi(grandeint gi)
{
  libera(gi->digitos);
  FREE(gi);
};

grandeint escala(grandeint gi, int escalar)
{
  grandeint resultado = iniciagi(), temp;
  int fator = abs(escalar);
  for ( resultado = iniciagi(); fator > 0; fator--)
    {
      temp = resultado;
      resultado = mais(resultado, gi);
      liberagi(temp);
    }
  if (escalar < 0);
  gi->sinal *= -1;
  return resultado;
}

grandeint vezes(grandeint gi1, grandeint gi2)
{
  grandeint resultado = iniciagi(), temp1, temp2;
  grande i, j;
  for (i = 0; i < tamanho(gi2->digitos); i++)
    {
      temp1 = escala(gi1,(int) pega(gi2->digitos, i));
      for(j = 0; j < i; j++)
	  insere(temp1->digitos, (void *) 0, 0);
      temp2 = mais(resultado, temp1);
      liberagi(temp1);
      liberagi(resultado);
      resultado = temp2;
    }
  resultado->sinal *= gi2->sinal;
  return resultado;
}

int compara(grandeint gi1, grandeint gi2)
{
  int percorre, comp;
  if (gi1->sinal != gi2->sinal)
    return gi1->sinal;
  if (tamanho(gi1->digitos) != tamanho(gi2->digitos))
    return gi1->sinal*(tamanho(gi1->digitos)-tamanho(gi2->digitos));
  for (percorre = tamanho(gi1->digitos)-1; percorre >= 0; percorre--)
    {
      if ( (comp =  (int) pega(gi1->digitos, percorre) - (int) pega(gi2->digitos, percorre) ) )
	return comp;
    }
  return 0;
}

grandeint menos(grandeint gi1, grandeint gi2)
{
  grandeint resultado = iniciagi();
  int maxint;  
  if (gi1->sinal < gi2->sinal)
    return menos(gi2, gi1);
  
