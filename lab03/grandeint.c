#include "grandeint.h"
#include "lista.h"
#include "balloc.h"
#include <stdlib.h>
#include <stdio.h>

#define malloc MALLOC
#define free FREE

struct grandeintS{
  lista digitos;
  char sinal;
};

grandeint iniciagi(void)
{
  grandeint n = (grandeint) malloc(sizeof(struct grandeintS));
  if (NULL == n)
    return n;
  if (NULL == (n->digitos = inicial()))
    {
      free(n);
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
	  free(n);
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
	  free(n);
	  return NULL;
	}
      string++;
    }
  return n;
}

grandeint giscan(void)
{
  grandeint n = iniciagi();
  char leitura;
  if (n == NULL)
    return NULL;
  leitura = getchar();
  switch (leitura)
    {
    case '-':
      n->sinal = -1;
    case '+':
      leitura = getchar();
    default:
      break;
    }
  while (leitura == '0')
    leitura = getchar();
  while (leitura >= '0' && leitura <= '9')
    {      
      if (insereEsq(n->digitos, leitura - '0'))
	{
	  libera(n->digitos);
	  free(n);
	  return NULL;
	}
      leitura = getchar();
    }
  return n;
}

void printgi(grandeint n)
{
  lista temp;
  if (n == NULL)
    return;
  temp = andaDir(n->digitos);
  if (n->sinal == -2)
    {
      printf("nan");
      return;
    }
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

grandeint mais(grandeint gi1, grandeint gi2)
{
  grandeint resultado = iniciagi();
  incrementa(resultado,gi1);
  incrementa(resultado,gi2);
  return resultado;
}

void incrementa(grandeint gi1, grandeint gi2)
{
  lista anda1 = andaEsq(gi1->digitos), anda2 = andaEsq(gi2->digitos);
  char parcial = 0;
  while (1)
    {
      if (anda1 != gi1->digitos)
	parcial += pega(anda1) * gi1->sinal;
      if (anda2 != gi2->digitos)
	{
	  parcial += pega(anda2) * gi2->sinal;
	  anda2 = andaEsq(anda2);
	}
      if (!parcial && anda1 == gi1->digitos && anda2 == gi2->digitos)
	break;
      if (anda1 == gi1->digitos)
	insereDir(anda1, parcial%10);
      else
	{
	  atribui(anda1, parcial%10);
	  anda1 = andaEsq(anda1);
	}
      parcial /= 10;
    }
  gi1->sinal = pega(andaDir(gi1->digitos)) < 0 ? -1 : 1;
  parcial = 0;
  anda1 = andaEsq(gi1->digitos);
  /* começa loop do mal */
  while (anda1 != gi1->digitos)
    {
      while (pega(anda1) * gi1->sinal < 0)
	{	  
	  atribui(anda1,pega(anda1) + 10 * gi1->sinal);
	  atribui(andaEsq(anda1),pega(andaEsq(anda1)) - gi1->sinal);
	}
      atribui(anda1,abs(pega(anda1)));
      anda1 = andaEsq(anda1);
    }
  /* termina loop do mal */
  while (pega(andaDir(gi1->digitos)) == 0)
    deleta(andaDir(gi1->digitos));
}

void liberagi(grandeint gi)
{
  libera(gi->digitos);
  free(gi);
}

grandeint vezes(grandeint gi1, grandeint gi2)
{
  grandeint resultado = iniciagi(), fator[10];
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
      incrementa(resultado,fator[(int) pega(anda)]);
    }
  for (i = 0; i < 10; i++)
    liberagi(fator[i]);
  resultado->sinal = gi1->sinal * gi2->sinal;  
  return resultado;
}

grandeint divisao(grandeint gi1, grandeint gi2)
{
  grandeint resultado = iniciagi(), resto, temp[8];
  lista ultimo;
  char parcial = 0;  
  int i;
  if (andaEsq(gi2->digitos) == gi2->digitos)
    {
      resultado->sinal = -2;
      return resultado;
    }
  resto = mais(resultado,gi1);
  temp[0] = mais(resultado,gi2);
  for (i = 1; i < 8; i++)
      temp[i] = mais(temp[i-1],gi2);
  ultimo = andaEsq(temp[0]->digitos);
  while (compara(resto, temp, 1) > 0)
    insereEsq(temp->digitos, 0);
  temp->sinal = -resto->sinal;
  while (1)
    {
      while (compara(resto, temp, 1) >= 0)
	{
	  incrementa (resto, temp);
	  parcial++;
	}
      if (parcial || andaEsq(resultado->digitos) != resultado->digitos)
	{
	  insereEsq(resultado->digitos, parcial);
	  parcial = 0;
	}
      if (andaEsq(temp->digitos) == ultimo)
	break;
      deleta(andaEsq(temp->digitos));
    }
  if (resultado->digitos != andaDir(resultado->digitos))
    resultado->sinal = gi1->sinal * gi2->sinal;
  liberagi(resto);
  liberagi(temp);
  return resultado;  
}

/* sign(compara(gi1,gi2)) == sign(gi1-gi2) */
int compara(grandeint gi1, grandeint gi2, int mod)
{
  lista anda1 = andaDir(gi1->digitos), anda2 = andaDir(gi2->digitos);
  char diff = 0;  
  if (gi1->sinal != gi2->sinal && !mod)
    return gi1->sinal == 1;
  while (anda1 != gi1->digitos && anda2 != gi2->digitos)
    {
      if (!diff)
	diff = pega(anda1) - pega(anda2);
      anda1 = andaDir(anda1);
      anda2 = andaDir(anda2);
    }
  if (anda1 == gi1->digitos && anda2 == gi2->digitos)
    return diff;
  if (anda1 != gi1->digitos)
    return 1;
  return -1;
}


/*******************************************************************************

COMEÇAM AS FUNÇÕES CHAMADAS EM principal.c

*******************************************************************************/

void soma (void)
{
  grandeint a, b, resultado;
  a = giscan();
  b = giscan();
  resultado = mais(a,b);
  printgi(resultado);
  putchar('\n');
  liberagi(a);
  liberagi(b);
  liberagi(resultado);
}

void multiplicacao (void)
{
  grandeint a, b, resultado;
  a = giscan();
  b = giscan();
  resultado = vezes(a,b);
  printgi(resultado);
  putchar('\n');
  liberagi(a);
  liberagi(b);
  liberagi(resultado);
}

/* void divide (void) */
/* { */
/*   grandeint a, b, resultado; */
/*   a = giscan(); */
/*   b = giscan(); */
/*   resultado = divisao(a,b); */
/*   printgi(resultado); */
/*   putchar('\n'); */
/*   liberagi(a); */
/*   liberagi(b); */
/*   liberagi(resultado); */
/* } */

void divide (void)
{
  return;
}

int primo[] = 
  { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281, 283, 293, 307, 311, 313, 317, 331, 337, 347, 349, 353, 359, 367, 373, 379, 383, 389, 397, 401, 409, 419, 421, 431, 433, 439, 443, 449, 457, 461, 463, 467, 479, 487, 491, 499, 503, 509, 521, 523, 541};

void godel (void)
{
  char leitura[101];
  grandeint resultado, temp, giprimo;
  int i, j;
  resultado = itogi(1);
  scanf("%s", leitura);
  for(i = 0; leitura[i] != '\0'; i++)
    {
      giprimo = itogi(primo[i]);
      j = 0;
      switch (leitura[i])
	{
	case ')':
	  j++;
	case '(':
	  j++;
	case '=':
	  j++;
	case '/':
	  j++;
	case '*':
	  j++;
	case '-':
	  j++;
	case '+':
	  j++;
	default:
	case '0':
	  break;
	}
      if (leitura[i] >= '1' && leitura[i] <= '9')
	j = leitura[i] - '0';
      else
	j += 10;
      while (j > 0)
	{
	  temp = vezes(resultado, giprimo);
	  liberagi(resultado);
	  resultado = temp;
	  j--;
	}
      liberagi(giprimo);
    }
  printgi(resultado);
  putchar('\n');
  liberagi(resultado);
  return;
}

/* void godel (void)  */
/* { */
/*   return;   */
/* } */

  
