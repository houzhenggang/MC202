#include "grandeint.h"
#include "lista.h"
#include "balloc.h"
#include <stdlib.h>
#include <stdio.h>

#define malloc MALLOC
#define free FREE

grandeint iniciagi(void)
{
  grandeint n = (grandeint) malloc(sizeof(struct grandeintS));
  n->digitos = inicial();

  /* 
     a convenção de sinal é:
     1 para número não-negativo
     -1 para número negativo
     -2 para nan
  */

  n->sinal = 1;
  return n;
}

grandeint itogi(int init)
{
  grandeint n = iniciagi();  
  /* atribui o sinal */
  if (init < 0)
    {
      init *= -1;
      n->sinal = -1;
    }
  /* itera sobre o int */
  while (init)
    { 
      insereDir(n->digitos, init%10); 
      init = init/10;
    }
  return n;
}

grandeint giscan(void)
{
  grandeint n = iniciagi();
  char leitura;
  /* loop que ajusta o sinal e descarta zeros até encontrar dígitos significativos */
  do {
    leitura = getchar();
    switch (leitura)
      {
      case '-':
	n->sinal = -1;
      case '+':
      default:
	break;
      }
    if (leitura == '\n')
      break;
  }
  while (leitura < '1' || leitura > '9');
  /* loop que efetua a leitura dos dígitos */
  while (leitura >= '0' && leitura <= '9')
    {      
      insereEsq(n->digitos, leitura - '0');
      leitura = getchar();
    }
  return n;
}

void printgi(grandeint n)
{
  lista temp;
  temp = n->digitos->dir;
  /* se houve divisão por zero */
  if (n->sinal == -2)
    {
      printf("nan");
      return;
    }
  /* imprime sinal caso necessário */
  if (n->sinal == -1)
    putchar('-');
  /* se o número é 0 precisamos imprimir */
  if (temp == n->digitos)
    putchar('0');
  /* imprime até acabarem os dígitos */
  while(temp != n->digitos)
    {
      putchar(temp->digito + '0');
      temp = temp->dir;
    }
}

grandeint mais(grandeint gi1, grandeint gi2)
{
  /* inicia grandeint 0 e o incrementa de ambos inteiros */
  grandeint resultado = iniciagi();
  incrementa(resultado,gi1);
  incrementa(resultado,gi2);
  return resultado;
}

void incrementa(grandeint gi1, grandeint gi2)
{
  lista anda1 = gi1->digitos->esq, anda2 = gi2->digitos->esq;
  char parcial = 0;
  while (1)
    {
      if (anda1 != gi1->digitos)
	parcial += anda1->digito * gi1->sinal;
      if (anda2 != gi2->digitos)
	{
	  parcial += anda2->digito * gi2->sinal;
	  anda2 = anda2->esq;
	}
      if (!parcial && anda1 == gi1->digitos && anda2 == gi2->digitos)
	break;
      if (anda1 == gi1->digitos)
	insereDir(anda1, parcial%10);
      else
	{
	  anda1->digito =  parcial%10;
	  anda1 = anda1->esq;
	}
      parcial /= 10;
    }
  for (anda1 = gi1->digitos->dir; !anda1->digito && anda1->dir != gi1->digitos; anda1 = anda1->dir);
  gi1->sinal = anda1->digito < 0 ? -1 : 1;
  parcial = 0;
  anda1 = gi1->digitos->esq;
  /* começa loop do mal */
  while (anda1 != gi1->digitos)
    {
      while (anda1->digito * gi1->sinal < 0)
	{	  
	  anda1->digito += 10 * gi1->sinal;
	  anda1->esq->digito -= gi1->sinal;
	}
      anda1->digito = abs(anda1->digito);
      anda1 = anda1->esq;
    }
  /* termina loop do mal */
  while (gi1->digitos->dir->digito == 0)
    deleta(gi1->digitos->dir);
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
  if (gi1->digitos->dir == gi1->digitos || gi2->digitos == gi2->digitos->dir)
    return resultado;  
  fator[0] = iniciagi();
  for (i = 1; i < 10; i++)
    fator[i] = mais(fator[i-1],gi1);
  for (anda = gi2->digitos->dir; anda != gi2->digitos; anda = anda->dir)
    {
      insereEsq(resultado->digitos,0);
      incrementa(resultado,fator[(int) anda->digito]);
    }
  for (i = 0; i < 10; i++)
    liberagi(fator[i]);
  resultado->sinal = gi1->sinal * gi2->sinal;  
  return resultado;
}

grandeint divisao(grandeint gi1, grandeint gi2)
{
  grandeint resultado = iniciagi(), resto, temp[9];
  lista ultimo;
  int i;
  if (gi2->digitos->esq == gi2->digitos)
    {
      resultado->sinal = -2;
      return resultado;
    }
  resto = mais(resultado,gi1);
  temp[0] = mais(resultado,gi2);
  for (i = 1; i < 9; i++)
      temp[i] = mais(temp[i-1],gi2);
  ultimo = temp[0]->digitos->esq;
  while (compara(resto, temp[8], 1) > 0)
    for(i = 0; i < 9; i++)
      insereEsq(temp[i]->digitos, 0);
  for(i = 0; i < 9; i++)
    temp[i]->sinal = -resto->sinal;
  while (1)
    {
      for (i = 8; i >= 0; i--)
	if (compara(resto, temp[i], 1) >= 0)
	  {
	    incrementa (resto, temp[i]);
	    break;
	  }
      if (i != -1 || resultado->digitos->esq != resultado->digitos)
	  insereEsq(resultado->digitos, i+1);
      if (temp[0]->digitos->esq == ultimo)
	break;
      for (i = 0; i < 9; i++)
	deleta(temp[i]->digitos->esq);
    }
  if (resultado->digitos != resultado->digitos->dir)
    resultado->sinal = gi1->sinal * gi2->sinal;
  liberagi(resto);
  for (i = 0; i < 9; i++)
    liberagi(temp[i]);
  return resultado;  
}

/* sign(compara(gi1,gi2)) == sign(gi1-gi2) */
int compara(grandeint gi1, grandeint gi2, int mod)
{
  lista anda1 = gi1->digitos->dir, anda2 = gi2->digitos->dir;
  char diff = 0;  
  if (gi1->sinal != gi2->sinal && !mod)
    return gi1->sinal == 1;
  while (anda1 != gi1->digitos && anda2 != gi2->digitos)
    {
      if (!diff)
	diff = anda1->digito - anda2->digito;
      anda1 = anda1->dir;
      anda2 = anda2->dir;
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

void divide (void)
{
  grandeint a, b, resultado;
  a = giscan();
  b = giscan();
  resultado = divisao(a,b);
  printgi(resultado);
  putchar('\n');
  liberagi(a);
  liberagi(b);
  liberagi(resultado);
}

int primo[] = 
  { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29};


void godel (void)
{
  char leitura[11];
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
  
