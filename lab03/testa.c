#include "lista.h"
#include "grandeint.h"
#include <stdio.h>

int main()
{
  grandeint zero, bigpos, bigneg, spos, sneg;  
  zero = iniciagi();
  bigpos = atogi("1000");
  bigneg = atogi("-1000");
  spos = atogi("1");
  sneg = atogi("-1");
  printgi(zero); printf (" + "); printgi(zero); printf (" = "); printgi(mais(zero,zero)); printf ("\n");
  printgi(spos); printf (" + "); printgi(zero); printf (" = "); printgi(mais(spos,zero)); printf ("\n");
  printgi(zero); printf (" + "); printgi(spos); printf (" = "); printgi(mais(zero,spos)); printf ("\n");
  printgi(sneg); printf (" + "); printgi(zero); printf (" = "); printgi(mais(sneg,zero)); printf ("\n");
  printgi(zero); printf (" + "); printgi(sneg); printf (" = "); printgi(mais(zero,sneg)); printf ("\n");
  printgi(sneg); printf (" + "); printgi(spos); printf (" = "); printgi(mais(sneg,spos)); printf ("\n");
  printgi(spos); printf (" + "); printgi(sneg); printf (" = "); printgi(mais(spos,sneg)); printf ("\n");

  printgi(spos); printf (" + "); printgi(bigpos); printf (" = "); printgi(mais(spos,bigpos)); printf ("\n");
  printgi(bigpos); printf (" + "); printgi(spos); printf (" = "); printgi(mais(bigpos,spos)); printf ("\n");
  printgi(sneg); printf (" + "); printgi(bigneg); printf (" = "); printgi(mais(sneg,bigneg)); printf ("\n");
  printgi(bigneg); printf (" + "); printgi(sneg); printf (" = "); printgi(mais(bigneg,sneg)); printf ("\n");

  printgi(spos); printf (" + "); printgi(bigneg); printf (" = "); printgi(mais(spos,bigneg)); printf ("\n");
  printgi(bigneg); printf (" + "); printgi(spos); printf (" = "); printgi(mais(bigneg,spos)); printf ("\n");
  printgi(sneg); printf (" + "); printgi(bigpos); printf (" = "); printgi(mais(sneg,bigpos)); printf ("\n");
  printgi(bigpos); printf (" + "); printgi(sneg); printf (" = "); printgi(mais(bigpos,sneg)); printf ("\n");
  printgi(bigneg); printf (" + "); printgi(bigpos); printf (" = "); printgi(mais(bigneg,bigpos)); printf ("\n");
  printgi(bigpos); printf (" + "); printgi(bigneg); printf (" = "); printgi(mais(bigpos,bigneg)); printf ("\n");
  printgi(zero); printf (" + "); printgi(zero); printf (" = "); printgi(mais(zero,zero)); printf ("\n");
  printgi(zero); printf (" + "); printgi(zero); printf (" = "); printgi(mais(zero,zero)); printf ("\n");
  printgi(zero); printf (" + "); printgi(zero); printf (" = "); printgi(mais(zero,zero)); printf ("\n");
  /* printf ("%d + %d = %d\n", ); */
  /* printf ("%d + %d = %d\n", ); */
  /* printf ("%d + %d = %d\n", ); */
  /* printf ("%d + %d = %d\n", ); */
  
  return 0;
}
