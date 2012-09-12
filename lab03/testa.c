#include "lista.h"
#include "grandeint.h"
#include <stdio.h>

int main()
{
  grandeint zero, bigpos, bigneg, spos, sneg, temp;  
  zero = iniciagi();
  bigpos = atogi("27182818284590452353602874713526624977572470936999595749669676277240766303535475945713821785251664274274663919320030599218174135966290435729003342952605956307381323286279434907632338298807531952510190115738341879307021540891499348841675092447614606680822648001684774118537423454424371075390777449920695517027618386062613313845830007520449338265602976067371132007093287091274437470472306969772093101416928368190255151086574637721112523897844250569536967707854499699679468644549059879316368892300987931277361782154249992295763514822082698951936680331825288693984964651058209392398294887933203625094431173012381970684161403970198376793206832823764648042953118023287825098194558153017567173613320698112509961818815930416903515988885193458072738667385894228792284998920868058257492796104841984443634632449684875602336248270419786232090021609902353043699418491463140934317381436405462531520961836908887070167683964243781405927145635490613031072085103837505101157477041718986106873969655212671546889570350354");

  bigneg = atogi("31415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679821480865132823066470938446095505822317253594081284811174502841027019385211055596446229489549303819644288109756659334461284756482337867831652712019091456485669234603486104543266482133936072602491412737245870066063155881748815209209628292540917153643678925903600113305305488204665213841469519415116094330572703657595919530921861173819326117931051185480744623799627495673518857527248912279381830119491298336733624406566430860213949463952247371907021798609437027705392171762931767523846748184676694051320005681271452635608277857713427577896091736371787214684409012249534301465495853710507922796892589235420199561121290219608640344181598136297747713099605187072113499999983729780499510597317328160963185950244594553469083026425223082533446850352619311881710100031378387528865875332083814206171776691473035982534904287554687311595628638823537875937519577818577805321712268066130019278766111959092164201989");
  /* bigpos = itogi(1000); */
  /* bigneg = itogi(-1000); */
  spos = atogi("3");
  sneg = atogi("-2");
  temp = vezes(bigneg,bigpos);
  /* printgi(zero); printf (" + "); printgi(zero); printf (" = "); printgi(mais(zero,zero)); printf ("\n"); */
  /* printgi(spos); printf (" + "); printgi(zero); printf (" = "); printgi(mais(spos,zero)); printf ("\n"); */
  /* printgi(zero); printf (" + "); printgi(spos); printf (" = "); printgi(mais(zero,spos)); printf ("\n"); */
  /* printgi(sneg); printf (" + "); printgi(zero); printf (" = "); printgi(mais(sneg,zero)); printf ("\n"); */
  /* printgi(zero); printf (" + "); printgi(sneg); printf (" = "); printgi(mais(zero,sneg)); printf ("\n"); */
  /* printgi(sneg); printf (" * "); printgi(spos); printf (" = "); printgi(vezes(sneg,spos)); printf ("\n"); */
  /* printgi(spos); printf (" + "); printgi(sneg); printf (" = "); printgi(mais(spos,sneg)); printf ("\n"); */

  /* printgi(spos); printf (" + "); printgi(bigpos); printf (" = "); printgi(mais(spos,bigpos)); printf ("\n"); */
  /* printgi(bigpos); printf (" + "); printgi(spos); printf (" = "); printgi(mais(bigpos,spos)); printf ("\n"); */
  /* printgi(sneg); printf (" + "); printgi(bigneg); printf (" = "); printgi(mais(sneg,bigneg)); printf ("\n"); */
  /* printgi(bigneg); printf (" + "); printgi(sneg); printf (" = "); printgi(mais(bigneg,sneg)); printf ("\n"); */

  /* printgi(spos); printf (" + "); printgi(bigneg); printf (" = "); printgi(mais(spos,bigneg)); printf ("\n"); */
  /* printgi(bigneg); printf (" + "); printgi(spos); printf (" = "); printgi(mais(bigneg,spos)); printf ("\n"); */
  /* printgi(sneg); printf (" + "); printgi(bigpos); printf (" = "); printgi(mais(sneg,bigpos)); printf ("\n"); */
  /* printgi(bigpos); printf (" + "); printgi(sneg); printf (" = "); printgi(mais(bigpos,sneg)); printf ("\n"); */
  printgi(bigneg); printf (" * "); printgi(bigpos); printf (" = "); printgi(temp); printf ("\n");
  /* printgi(bigpos); printf (" + "); printgi(bigneg); printf (" = "); printgi(mais(bigpos,bigneg)); printf ("\n"); */
  /* printgi(zero); printf (" + "); printgi(zero); printf (" = "); printgi(mais(zero,zero)); printf ("\n"); */
  /* printgi(zero); printf (" + "); printgi(zero); printf (" = "); printgi(mais(zero,zero)); printf ("\n"); */
  /* printgi(zero); printf (" + "); printgi(zero); printf (" = "); printgi(mais(zero,zero)); printf ("\n"); */
  liberagi(zero);
  liberagi(bigpos);
  liberagi(bigneg);
  liberagi(spos);
  liberagi(sneg);
  liberagi(temp);
  return 0;
}
