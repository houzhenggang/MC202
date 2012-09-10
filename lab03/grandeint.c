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
      if (insereDir(n->digitos, init%10))
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
      if (insereEsq(n->digitos, *string - '0'))
	{
	  libera(n->digitos);
	  FREE(n);
	  return NULL;
	}
      string++;
    }
  return n;
}


void printgi(grandeint n)
{
  lista temp;
  if (n == NULL)
    return;
  temp = andaDir(n->digitos);
  if (n->sinal == -1)
    putchar('-');
  if (temp == n->digitos)
    putchar('0');
  while(temp != n->digitos)
    {
      putchar(pega(temp) + '0');
      temp = andaDir(temp);
    }
}

/* funciona só pra positivos */
grandeint mais(grandeint gi1, grandeint gi2)
{
  grandeint resultado = iniciagi();
  lista anda1 = andaEsq(gi1->digitos), anda2 = andaEsq(gi2->digitos);
  char parcial = 0;
  while ( parcial || anda1 != gi1->digitos || anda2 != gi2->digitos)
    {
      if (anda1 != gi1->digitos)
	{
	  parcial += pega(anda1);
	  anda1 = andaEsq(anda1);
	}
      if (anda2 != gi2->digitos)
	{
	  parcial += pega(anda2);
	  anda2 = andaEsq(anda2);
	}
      insereDir(resultado->digitos, parcial%10);
      parcial /= 10;
    }
  return resultado;
}

void liberagi(grandeint gi)
{
  libera(gi->digitos);
  FREE(gi);
};


grandeint vezes(grandeint gi1, grandeint gi2)
{
  grandeint resultado = iniciagi(), fator[10], temp;
  lista anda;
  int i;
  if (andaDir(gi1->digitos) == gi1->digitos || gi2->digitos == andaDir(gi2->digitos))
    return resultado;  
  fator[0] = iniciagi();
  for (i = 1; i < 10; i++)
    fator[i] = mais(fator[i-1],gi1);
  for (anda = andaDir(gi2->digitos); anda != gi2->digitos; anda = andaDir(anda))
    {
      insereEsq(resultado->digitos,0);
      temp = mais(resultado,fator[(int) pega(anda)]);
      liberagi(resultado);
      resultado = temp;
    }
  for (i = 0; i < 10; i++)
    liberagi(fator[i]);
  resultado->sinal = gi1->sinal * gi2->sinal;  
  return resultado;
}
