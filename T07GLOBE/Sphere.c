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
 *   (VEC) rotated vector value.
 */
VOID DRAW(HDC hDC, INT w, INT h)
{
  INT x, y, i, j, Xc = w / 2, Yc = h / 2;
  CHAR Buf[100];
  MATR m;
  m = MatrMulMatr(MatrRotateX(45 * Time), MatrRotateY(45 * Time));

  TimerResponse();
  TextOut(hDC, 8, 8, Buf, sprintf(Buf, "%.3f", FPS));
  SelectObject(hDC, GetStockObject(DC_PEN));
  SetDCPenColor(hDC, RGB(200, 225, 175));
  SelectObject(hDC, GetStockObject(DC_BRUSH));

  for (i = 0; i < K - 1; i++)
    for (j = 0; j < L - 1; j++)
    {
      VEC ps1[4];
      POINT ps[4];
      DOUBLE s = 0;

      ps1[0] = PointTransform(G[i][j], m);
      ps1[1] = PointTransform(G[i][j + 1], m);
      ps1[2] = PointTransform(G[i + 1][j + 1], m);
      ps1[3] = PointTransform(G[i + 1][j], m);

      ps[0].x = ps1[0].X + Xc, ps[0].y = ps1[0].Y + Yc;
      ps[1].x = ps1[1].X + Xc, ps[1].y = ps1[1].Y + Yc;
      ps[2].x = ps1[2].X + Xc, ps[2].y = ps1[2].Y + Yc;
      ps[3].x = ps1[3].X + Xc, ps[3].y = ps1[3].Y + Yc;
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