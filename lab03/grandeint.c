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


void * printgi(grandeint n)
{
  lista temp;
  if (n == NULL)
    return NULL;
  temp = andaDir(n->digitos);
  if (n->sinal == -1)
    putchar('-');
  if (temp == n->digitos)
    putchar('0');
  while(temp != n->digitos)
    {
      putchar(temp->digito + '0');
      temp = pegaDir(temp);
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
	  anda2 = pegaEsq(anda2);
	}
      insereDir(resultado, parcial%10);
      parcial /= 10;
    }
  return resultado;
}

void liberagi(grandeint gi)
{
  libera(gi->digitos);
  FREE(gi);
};

grandeint escala(grandeint gi, int escalar)
{
  grandeint resultado = iniciagi();
  if (escalar < 0)
    {
      resultado->sinal = -1;
      escalar = -escalar;
    }
  lista anda = andaEsq(gi->digitos); temp = inicia(temp);
  

grandeint vezes(grandeint gi1, grandeint gi2)
{
  grandeint resultado = iniciagi();
  lista anda1 = andaEsq(gi1->digitos), anda2 = andaDir(gi2->digitos),
    parcial = inicia(), parcialAnda = parcial, parcialAnda2;
  char temp = 0;
  while (parcial != parcialAnda || gi1->digitos != anda1 || gi2->digitos != anda2)
    {
      temp = pega(anda1) * pega(anda2);
      if (pegaEsq(parcialAnda) == parcial)
	insereEsq(parcialAnda,0);
      parcialAnda = pegaEsq(parcialAnda);
      while (temp)
	{
	  atribui(parcialAnda, temp%10);
	  temp /= 10;
	  temp += pega(parcialAnda);

      while (temp);
      
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
