#include "lista.h"
#include "grandeint.h"
#include <stdio.h>
int main()
{
  grandeint zero, bigpos, bigneg, spos, sneg;  
  zero = iniciagi();
  bigpos = atogi("100000000");
  bigneg = atogi("-100000000");
  spos = atogi("1");
  sneg = atogi("-1");
  printf ("%s + %s = %s\n", gitoa(zero), gitoa(zero), gitoa(mais(zero,zero)));
  printf ("%s + %s = %s\n", gitoa(zero), gitoa(spos), gitoa(mais(zero,spos)));
  printf ("%s + %s = %s\n", gitoa(spos), gitoa(sneg), gitoa(mais(spos,sneg)));
  printf ("%s + %s = %s\n", gitoa(spos), gitoa(bigneg), gitoa(mais(spos,bigneg)));
  printf ("%s + %s = %s\n", gitoa(bigneg), gitoa(spos), gitoa(mais(bigneg,spos)));
  printf ("%s + %s = %s\n", gitoa(sneg), gitoa(bigpos), gitoa(mais(sneg,bigpos))); 
  printf ("%s + %s = %s\n", gitoa(bigpos), gitoa(sneg), gitoa(mais(bigpos,sneg))); 
  /* printf ("%d + %d = %d\n", ); */
  /* printf ("%d + %d = %d\n", ); */
  /* printf ("%d + %d = %d\n", ); */
  /* printf ("%d + %d = %d\n", ); */
  
  return 0;
}
