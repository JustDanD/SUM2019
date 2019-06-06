/* *FILE NAME: T03CLOCK.C
   *PRORAMMER: Danila Pimenov
   *DATE: 03.0.6.2019
   *PURPOSE: Console
*/

#include <stdio.h>
#include <windows.h>

#define MAX 5

INT P[MAX];
BOOL IsParity = 1;

INT Store( VOID )
{
  FILE *F;
  INT i;

  if ((F = fopen("Perms.txt", "a")) == NULL)
    return 0;

  for (i = 0; i < MAX - 1; i++)
    fprintf(F, "%d,", P[i]);
  fprintf(F, "%d  Parity - %s\n", P[MAX - 1], IsParity ? "even" : "Odd");
  fclose(F);
  return 1;
}

VOID Swap(INT *A, INT *B)
{
   INT tmp = *A;
   *A = *B;
   *B = tmp;
}
VOID Go( INT POS)
{
  INT i;
  if (POS == MAX)
    Store();
  else 
  {
    for (i = POS; i < MAX; i++)
    {
       Swap(&P[POS], &P[i]);
       if (IsParity == 1 && i != POS)
         IsParity = 0;
       else if (IsParity == 0 && i != POS)
         IsParity = 1;
       Go(POS + 1);
        if (IsParity == 1 && i != POS)
         IsParity = 0;
       else if (IsParity == 0 && i != POS)
         IsParity = 1;
       Swap(&P[POS], &P[i]);
    }
  }
}

VOID GOALP( INT POS)
{
  INT i, x;
  BOOL save_parity;
  if (POS == MAX)
    Store();
  else 
  {
    save_parity = IsParity;
    GOALP(POS + 1);
    for (i = POS + 1; i < MAX; i++)
    {
       Swap(&P[POS], &P[i]);
       if (IsParity == 1 && i != POS)
         IsParity = 0;
       else if (IsParity == 0 && i != POS)
         IsParity = 1;
       GOALP(POS + 1);
    }
    x = P[POS];
    for (i = POS + 1; i < MAX; i++)
      P[i - 1] = P[i];
    P[MAX - 1] = x;
    IsParity = save_parity;
  }
}


VOID main( VOID )
{
   int i;

   for (i = 1; i < MAX + 1; i++)
     P[i] = i;
   GOALP(0);
}