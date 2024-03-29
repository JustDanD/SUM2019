/* *FILE NAME: T03CLOCK.C
   *PRORAMMER: Danila Pimenov
   *DATE: 03.0.6.2019
   *PURPOSE: Console
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <math.h>

#define MAX 10 

INT P[MAX], N;
BOOL IsParity = 1;
DOUBLE MAT[MAX][MAX];
DOUBLE Det;



BOOL LoadMatrix(VOID)
{
	FILE *F;
	INT i, j;

	if ((F = fopen("in.txt", "r")) == NULL)
		return FALSE;
	fscanf(F, "%d", &N);
	for (i = 0; i < N; i++)
		P[i] = i;
	if (N < 0)
		N = 0;
	else if (N > MAX)
		N = MAX;
	for (i = 0; i < N; i++)
		for (j = 0; j < N; j++)
			fscanf(F, "%lf", &MAT[i][j]);
	fclose(F);
}
INT Store(VOID)
{

	INT i;
	DOUBLE prod;
	for (prod = 1, i = 0; i < N; i++)
		prod *= MAT[i][P[i]];
	Det += (IsParity ? 1 : -1) * prod;
	return 1;
}

VOID Swap(DOUBLE *A, DOUBLE *B)
{
	DOUBLE tmp = *A;
	*A = *B;
	*B = tmp;
}
VOID Go(INT POS)
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

VOID GOALP(INT POS)
{
	INT i, x;
	BOOL save_parity;
	if (POS == N)
		Store();
	else
	{
		save_parity = IsParity;
		GOALP(POS + 1);
		for (i = POS + 1; i < N; i++)
		{
			Swap(&P[POS], &P[i]);
			IsParity = !IsParity;
			GOALP(POS + 1);
		}
		x = P[POS];
		for (i = POS + 1; i < N; i++)
			P[i - 1] = P[i];
		P[N - 1] = x;
		IsParity = save_parity;
	}
}

VOID Meth(VOID)
{
	INT i, j, max_row, max_col, x, y, k;
	DOUBLE coef;

	Det = 1;
	for (i = 0; i < N; i++)
	{
            max_row = i, max_col = i;
		for (x = i; x < N; x++)
			for (y = i; y < N; y++)
				if (fabs(MAT[x][y]) > fabs(MAT[max_row][max_col]))
					max_col = x, max_row = y;
		if (MAT[max_row][max_col] == 0)
		{
			Det = 0;
			return;
		}
		if (max_row != i)
		{
			for (x = i; x < N; x++)
				Swap(&(MAT[i][x]), &(MAT[max_row][x]));
			Det = -Det;
		}
		if (max_col != i)
		{
			for (y = i; y < N; y++)
                          Swap(&MAT[y][i], &MAT[y][max_col]);
			Det = -Det;
		}
                for (x = i + 1; x < N; x++) 
                {
                  coef = MAT[x][i] / MAT[i][i];
		  MAT[x][i] = 0;
                
		  for (k = i + 1; k < N; k++)
			MAT[x][k] -= coef * MAT[i][k];
                }
                Det *= MAT[i][i];
	}

}

/*VOID mat(INT POSI, INT POSJ)
{
  INT i, j;
  for(i = 0; i < N; i++)
	for(j = 1; j < N; j++)

}   */
VOID main(VOID)
{
	INT i, j;
	LoadMatrix();
	Meth();
	//GOALP(0); 
	printf("%lf", Det);
	_getch();
}