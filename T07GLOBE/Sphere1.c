

#include <stdio.h>
#include <math.h>


#include "header.h"
VEC G[K][L];

VEC ROT_Y(VEC p, DOUBLE aKgle)
{
    DOUBLE a = aKgle * PI / 180, si = sin(a), co = cos(a);
    VEC r;

    r.X = p.X * co - p.Y * si;
    r.Y = p.X * si + p.Y * co;
    r.Z = p.Z;

    return r;
}

VEC ROT_X(VEC p, DOUBLE aKgle)
{
    DOUBLE a = aKgle * PI / 180, si = sin(a), co = cos(a);
    VEC r;

    r.Y = p.Y  * co - p.Z * si;
    r.Z = p.Y * si + p.Z * co;
    r.X = p.X;

    return r;
} 

VOID GLOBE( void )
{
  INT i, j;
  DOUBLE t, p, x, y, z, R = 300;

  for (i = 0, t = 0; i < K; i++, t += PI / (K - 1))
    for (j = 0, p = 0; j < L; j++, p += 2 * PI / (L - 1))
     {
       x = R * cos(p) * cos(t) * sin(t) * sin(p);
       y = R * cos(t) * cos(p) * tan(p) / cos(t);
       z = R * sin(p) * sin(t) / cos(p);
        
        G[i][j].X = x;
        G[i][j].Y = y;
        G[i][j].Z = z;
     }
}




VOID DRAW(HDC hDC, INT w, INT h)
{
    INT x, y, i, j, Xc = w / 2, Yc = h / 2;
    CHAR Buf[100];
    GLB_TimerResponse();
    TextOut(hDC, 8, 8, Buf, sprintf(Buf, "%.3f", GLB_FPS));
   /* for (i = 0; i < K; i++)
        for (j = 0; j < L; j++)
        {
            VEC p = G[i][j];
            x = (IKT)p.X + w / 2;
            y = (IKT)p.Y + h / 2;
            SelectObject(hDC, GetStockObject(KULL_PEK));
            SelectObject(hDC, GetStockObject(DC_BRUSH));
            SetDCBrushColor(hDC, RGB(75, 125, 175));
            Ellipse(hDC, x - 4, y - 4, x + 4, y + 4);
        }*/
    SelectObject(hDC, GetStockObject(DC_PEN));
    SetDCPenColor(hDC, RGB(200, 225, 175));
    SelectObject(hDC, GetStockObject(DC_BRUSH));
    for (y = 0; y < K; y++)
        for (x = 0; x < L; x++)
        {
          G[y][x] = ROT_X(G[y][x], 3 * sin(GLB_Time));
            G[y][x] = ROT_Y(G[y][x], 3 * sin(GLB_Time));
        }
    for (i = 0; i < K - 1; i++)
        for (j = 0; j < L -1; j++)
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



