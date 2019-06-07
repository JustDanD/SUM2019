#include "header.h"
#include <math.h>

VEC G[N][M];

VOID GLOBE( void )
{
  INT i, j;
  DOUBLE t, p, x, y, z, R = 300;

  for (i = 0, t = 0; i < N; i++, t += PI / (N - 1))
    for (j = 0, p = 0; j < M; j++, p += 2 * PI / (M - 1))
     {
        x = R * cos(p) * sin(t);
        y = R * cos(t);
        z = R * sin(p) * sin(t);
        
        G[i][j].X = x;
        G[i][j].Y = y;
        G[i][j].Z = z;
     }
}




VOID DRAW(HDC hDC, INT w, INT h)
{
    INT x, y, i, j, Xc = w / 2, Yc = h / 2;

    /*for (i = 0; i < N; i++)
        for (j = 0; j < M; j++)
        {
            VEC p = G[i][j];
            x = (INT)p.X + w / 2;
            y = (INT)p.Y + h / 2;
            SelectObject(hDC, GetStockObject(NULL_PEN));
            SelectObject(hDC, GetStockObject(DC_BRUSH));
            SetDCBrushColor(hDC, RGB(75, 125, 175));
            Ellipse(hDC, x - 4, y - 4, x + 4, y + 4);
        }*/
    SelectObject(hDC, GetStockObject(DC_PEN));
    SetDCPenColor(hDC, RGB(200, 225, 175));
    SelectObject(hDC, GetStockObject(DC_BRUSH));
    for (i = 0; i < N - 1; i++)
        for (j = 0; j < M -1; j++)
        {
            POINT ps[4];
            DOUBLE s = 0;
            ps[0].x = G[i][j].X + Xc, ps[0].y = G[i][j].Y  + Yc;
            ps[1].x = G[i][j + 1].X + Xc, ps[1].y = G[i][j + 1].Y + Yc;
            ps[2].x = G[i + 1][j + 1].X + Xc, ps[2].y = G[i + 1][j + 1].Y + Yc;
            ps[3].x = G[i + 1][j].X + Xc, ps[3].y = G[i + 1][j].Y + Yc;
            for (x = 0; x < 4; x++)
              s += (ps[x].x - ps[(x + 1) % 3].x) * (ps[x].y + ps[(x + 1) % 3].y);
            if ((ps[0].x - ps[1].x) * (ps[0].y + ps[1].y) +
                (ps[1].x - ps[2].x) * (ps[1].y + ps[2].y) +
                (ps[2].x - ps[3].x) * (ps[2].y + ps[3].y) +
                (ps[3].x - ps[0].x) * (ps[3].y + ps[0].y) 
                 >= 0)
            {
               SetDCBrushColor(hDC, RGB(0, 125, 221));
               Polygon(hDC, ps, 4);
            }
            else
            {
              SetDCBrushColor(hDC, RGB(0, 0, 0));
              Polygon(hDC, ps, 4);
            }
        }

    
}


VEC ROT_Y(VEC p, DOUBLE angle)
{
    DOUBLE a = angle * PI / 180, si = sin(a), co = cos(a);
    VEC r;

    r.X = p.X * co - p.Y * si;
    r.Y = p.X * si + p.Y * co;
    r.Z = p.Z;

    return r;
}

VEC ROT_X(VEC p, DOUBLE angle)
{
    DOUBLE a = angle * PI / 180, si = sin(a), co = cos(a);
    VEC r;

    r.Y = p.Y  * co - p.Z * si;
    r.Z = p.Y * si + p.Z * co;
    r.X = p.X;

    return r;
}

