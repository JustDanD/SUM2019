/* *FILE NAME: SPHERE.C
   *PRORAMMER: Danila Pimenov
   *DATE: 09.06.2019
   *PURPOSE: WinAPI
*/

#include <stdio.h>
#include <math.h>
#include "TIMER.h"
#include "header.h"
#include "MTH.h"

#define K 32
#define L 40
VEC G[K][L];

/* Sphere genereation function.
 * ARGUMENTS:
 *   None
 * RETURNS:
 *   None
 */
VOID GLOBE(void)
{
  INT i, j;
  DOUBLE t, p, x, y, z, R = 300;

  for (i = 0, t = 0; i < K; i++, t += PI / (K - 1))
    for (j = 0, p = 0; j < L; j++, p += 2 * PI / (L - 1))
    {
      x = R * cos(p) * sin(t);
      y = R * cos(t);
      z = R * sin(p) * sin(t);

      G[i][j].X = x;
      G[i][j].Y = y;
      G[i][j].Z = z;
    }
}

/* Sphere draw function.
 * ARGUMENTS:
 *   - Screen descriptor:
 *       HDC hDC;
 *   - height and width:
 *   INT w, INT h;
 * RETURNS:
 *   None
 */
VOID DRAW(HDC hDC, INT w, INT h)
{
  INT x, y, i, j, Xc = w / 2, Yc = h / 2, ProjDist;
  CHAR Buf[100];
  MATR m, p;
  m = MatrMulMatr(MatrRotateX(45 * Time), MatrRotateY(45 * Time));
  m = MatrMulMatr(m, MatrTranslate(VecMulNum(VecSet(-150, 0, 0), sin(Time))));
  //p = MatrMulMatr(MatrFrustum(), MatrRotateY(45 * Time));
  TimerResponse();
  TextOut(hDC, 8, 8, Buf, sprintf(Buf, "%.3f", FPS));
  SelectObject(hDC, GetStockObject(DC_PEN));
  SetDCPenColor(hDC, RGB(200, 225, 175));
  SelectObject(hDC, GetStockObject(DC_BRUSH));

  for (i = 0; i < K - 1; i++)
    for (j = 0; j < L - 1; j++)
    {
      POINT ps[4];
      DOUBLE s = 0;

      ps[0].x = PointTransform(G[i][j], m).X + Xc, ps[0].y = PointTransform(G[i][j], m).Y + Yc;
      ps[1].x = PointTransform(G[i][j + 1], m).X + Xc, ps[1].y = PointTransform(G[i][j + 1], m).Y + Yc;
      ps[2].x = PointTransform(G[i + 1][j + 1], m).X + Xc, ps[2].y = PointTransform(G[i + 1][j + 1], m).Y + Yc;
      ps[3].x = PointTransform(G[i + 1][j], m).X + Xc, ps[3].y = PointTransform(G[i + 1][j], m).Y + Yc;
      /*for (x = 0; x < 4; x++)
        s += (ps[x].x - ps[(x + 1) % 3].x) * (ps[x].y + ps[(x + 1) % 3].y);*/
      if ((ps[0].x - ps[1].x) * (ps[0].y + ps[1].y) +
        (ps[1].x - ps[2].x) * (ps[1].y + ps[2].y) +
        (ps[2].x - ps[3].x) * (ps[2].y + ps[3].y) +
        (ps[3].x - ps[0].x) * (ps[3].y + ps[0].y)
        >= 0)
      {
        SetDCBrushColor(hDC, RGB(0, 125, 221));
        Polygon(hDC, ps, 4);
      }/*
      else
      {
        SetDCBrushColor(hDC, RGB(0, 0, 0));
        Polygon(hDC, ps, 4);
      }*/
    }
}


