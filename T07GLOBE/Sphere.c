

#include <stdio.h>
#include <math.h>
#include "header.h"
#include "MTH.h"

#define K 32
#define L 40
VEC G[K][L];


VOID GLOBE( void )
{
  INT i, j;
  DOUBLE t, p, x, y, z, R = 300;

  for (i = 0, t = 0; i < K; i++, t += PI / (K - 1))
    for (j = 0, p = 0; j < L; j++, p += 2 * PI / (L - 1))
     {
       x = R * cos(p) * sin(t) /** sin(t) * sin(p)*/;
       y = R * cos(t) /** cos(p) * tan(p) / cos(t)*/;
       z = R * sin(p) * sin(t) /*/ cos(p)*/;
        
        G[i][j].X = x;
        G[i][j].Y = y;
        G[i][j].Z = z;
     }
}




VOID DRAW(HDC hDC, INT w, INT h)
{
    INT x, y, i, j, Xc = w / 2, Yc = h / 2;
    CHAR Buf[100];
    MATR m;
    m = MatrMulMatr(MatrRotateY(45 * sin(GLB_Time)), MatrRotateZ(45 * sin(GLB_Time)));
    GLB_TimerResponse();
    TextOut(hDC, 8, 8, Buf, sprintf(Buf, "%.3f", GLB_FPS));
    
  /* for (i = 0; i < K; i++)
        for (j = 0; j < L; j++)
        {
          VEC p = VecMulMatr(G[i][j], MatrRotateY(45 * sin(GLB_Time)));

            x = (INT)(-p.X + w / 2);
            y = (INT)(-p.Y + h / 2);
            
            SelectObject(hDC, GetStockObject(DC_PEN));   
            SetDCPenColor(hDC, RGB(111, 221, 50));
            SelectObject(hDC, GetStockObject(DC_BRUSH));
            SetDCBrushColor(hDC, RGB(75, 125, 175));
            Ellipse(hDC, x - 4, y - 4, x + 4, y + 4);
        }
    SelectObject(hDC, GetStockObject(DC_PEN));
    SetDCPenColor(hDC, RGB(200, 225, 175));
    SelectObject(hDC, GetStockObject(DC_BRUSH));
    */
   for (i = 0; i < L - 1; i++)
        for (j = 0; j < K -1; j++)
        {
            POINTS ps[4];
            DOUBLE s = 0;
            ps[0] = PointTransform((G[i][j]), m);
            ps[1] = PointTransform((G[i][j + 1]), m);
            ps[2] = PointTransform((G[i + 1][j + 1]), m);
            ps[3] = PointTransform((G[i + 1][j]), m);

           
            
            if ((ps[0].X - ps[1].X) * (ps[0].Y + ps[1].Y) +
                (ps[1].X - ps[2].X) * (ps[1].Y + ps[2].Y) +
                (ps[2].X - ps[3].X) * (ps[2].Y + ps[3].Y) +
                (ps[3].X - ps[0].X) * (ps[3].Y + ps[0].Y) 
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



