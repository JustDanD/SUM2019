/* *FILE NAME: RNDPRIM.C
   *PRORAMMER: Danila Pimenov
   *DATE: 10.06.2019
   *PURPOSE: WinAPI
*/


#include <windows.h>

#include <time.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "RND.H"


BOOL DP3_RndPrimCreate( dp3PRIM *Pr, INT NoofV, INT NoofI )
{
  INT size;

  /* Set all primitive data fields to 0 */
  memset(Pr, 0, sizeof(dp3PRIM));


  /* Calculate memory size for primitive data */
  size = sizeof(dp3VERTEX) * NoofV + sizeof(INT) * NoofI;

  /* Allocate memory */
  Pr->V = malloc(size);
  if (Pr->V == NULL)
    return FALSE;

  /* Set index array pointer */
  Pr->I = (INT *)(Pr->V + NoofV);

  /* Fill all allocated memory by 0 */
  memset(Pr->V, 0, size);

  /* Store data sizes */
  Pr->NumOfV = NoofV;
  Pr->NumOfI = NoofI;

  /* Set default transform (identity) */
  Pr->Trans = MatrIdentity();

  return TRUE;
} /* End of 'DP3_RndPrimCreate' function */

VOID DP3_RndPrimFree( dp3PRIM *Pr )
{
  if (Pr->V != NULL)
    free(Pr->V);
  /* Set all primitive data fields to 0 */
  memset(Pr, 0, sizeof(dp3PRIM));
} /* End of 'DP3_RndPrimFree' function */

VOID DP3_RndPrimDraw( dp3PRIM *Pr, MATR World )
{
  INT i;
  POINT *pnts; /* vertex projections */
  MATR M = MatrMulMatr3(Pr->Trans, World, DP3_RndMatrVP);

  /* Allocate memory for projections */
  pnts = malloc(sizeof(POINT) * Pr->NumOfV);
  if (pnts == NULL)
    return;

  /* Project all vertices */
  for (i = 0; i < Pr->NumOfV; i++)
  {
    /* Convert from World to NDC */
    VEC p = VectorMulMatr(Pr->V[i].P, M);

    /* Convert NDC to frame (viewport) */
    pnts[i].x = (p.X + 1) * DP3_RndFrameW / 2;
    pnts[i].y = (-p.Y + 1) * DP3_RndFrameH / 2;
  }

  /* Draw all triangles */
  for (i = 0; i < Pr->NumOfI; i += 3)
  {
    POINT p[3];

    p[0] = pnts[Pr->I[i]];
    p[1] = pnts[Pr->I[i + 1]];
    p[2] = pnts[Pr->I[i + 2]];
    Polygon(DP3_hDCRndFrame, p, 3);
  }
  free(pnts);
} /* End of 'DP3_RndPrimDraw' function */


BOOL DP3_RndPrimLoad( dp3PRIM *Pr, CHAR *FileName )
{
  INT nv, nf;
  FILE *F;
  CHAR Buf[1000];

  /* Set all primitive data fields to 0 */
  memset(Pr, 0, sizeof(dp3PRIM));

  /* Open file */
  if ((F = fopen(FileName, "r")) == NULL)
    return FALSE;

  /* Count vertex and facet quantity */
  nv = nf = 0;
  while (fgets(Buf, sizeof(Buf) - 1, F) != NULL)
    if (Buf[0] == 'v' && Buf[1] == ' ')
      nv++;
    else if (Buf[0] == 'f' && Buf[1] == ' ')
      nf++;

  /* Create primitive */
  if (!DP3_RndPrimCreate(Pr, nv, nf * 3))
  {
    fclose(F);
    return FALSE;
  }

  /* Load primitive data */
  rewind(F);
  nv = nf = 0;
  while (fgets(Buf, sizeof(Buf) - 1, F) != NULL)
    if (Buf[0] == 'v' && Buf[1] == ' ')
    {
      DBL x, y, z;

      sscanf(Buf + 2, "%lf%lf%lf", &x, &y, &z);
      Pr->V[nv++].P = VecSet(x, y, z);
    }
    else if (Buf[0] == 'f' && Buf[1] == ' ')
    {
      INT n1, n2, n3;

      sscanf(Buf + 2, "%d/%*d/%*d %d/%*d/%*d %d/%*d/%*d", &n1, &n2, &n3) == 3 ||
        sscanf(Buf + 2, "%d//%*d %d%//%*d %d%//%*d", &n1, &n2, &n3) == 3 ||
        sscanf(Buf + 2, "%d/%*d %d/%*d %d/%*d", &n1, &n2, &n3) == 3 ||
        sscanf(Buf + 2, "%d %d %d", &n1, &n2, &n3);
      Pr->I[nf++] = n1 - 1;
      Pr->I[nf++] = n2 - 1;
      Pr->I[nf++] = n3 - 1;
    }
  fclose(F);
  return TRUE;
} /* End of 'DP3_RndPrimLoad' function */

