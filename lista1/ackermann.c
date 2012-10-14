#include "../lab03/grandeint.h"

grandeint um;
grandeint menosum;

grandeint ackermann  (grandeint a, grandeint b)
{
  grandeint resultado, temp1, temp2, temp3; 
  if (a->digitos->dir == a->digitos)
      resultado = mais(um,b);
  else if (b->digitos->dir == b->digitos)
    {
      temp1 = mais(a,menosum);
      resultado = ackermann (temp1, um);
      liberagi(temp1);
    }
  else
    {
      temp1 = mais(menosum,b);
      temp2 = ackermann(a, temp1);
      liberagi(temp1);
      temp1 = mais(menosum,a);
      resultado = ackermann(temp1,temp2);
      liberagi(temp1);
      liberagi(temp2);
    }
  return resultado;
}

int main()
{
  grandeint tres = itogi(4), quatro = itogi(1), resultado;
  um = itogi(1);
  menosum = itogi(-1);
  resultado = ackermann(tres,quatro);
  printgi(resultado);
  putchar('\n');
  return 0;
}

  
