/* *FILE NAME: RNDBASE.H
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

VOID DP3_RndInit( HWND hWnd )
{
  HDC hDC;
  SetTimer(hWnd, 47, 1000, NULL);
  hDC = GetDC(hWnd);
  DP3_hDCRndFrame = CreateCompatibleDC(hDC);
  ReleaseDC(hWnd, hDC);
}
VOID DP3_RndClose( VOID )
{
  DeleteObject(DP3_hBmRndFrame);
  DeleteDC(DP3_hDCRndFrame);
  KillTimer(DP3_hWndRnd, 47);
  PostQuitMessage(0);
  return 0;

}
VOID DP3_RndResize( INT W, INT H )
{
  HDC hDC;

  if (DP3_hBmRndFrame != NULL)
    DeleteObject(DP3_hBmRndFrame);

  hDC = GetDC(DP3_hWndRnd);
  DP3_hBmRndFrame = CreateCompatibleBitmap(hDC, W, H);
  ReleaseDC(DP3_hWndRnd, hDC);
  SelectObject(DP3_hDCRndFrame, DP3_hBmRndFrame);

  DP3_RndFrameW = W;
  DP3_RndFrameH = H;
  DP3_RndProjSet();
}

VOID DP3_RndStart( VOID )
{
  SelectObject(DP3_hDCRndFrame, DP3_hBmRndFrame);
  SelectObject(DP3_hDCRndFrame, GetStockObject(WHITE_BRUSH));
  Rectangle(DP3_hDCRndFrame, 0, 0, DP3_RndFrameW, DP3_RndFrameW);


  SelectObject(DP3_hDCRndFrame, GetStockObject(NULL_BRUSH));
   SelectObject(DP3_hDCRndFrame, GetStockObject(BLACK_PEN));
}

/*VOID DP3_RndEnd( VOID )
{

}       */

VOID DP3_RndCopyFrame( HDC hDC )
{
  BitBlt(hDC, 0, 0, DP3_RndFrameW, DP3_RndFrameH,
         DP3_hDCRndFrame, 0, 0, SRCCOPY);
}  

VOID DP3_RndProjSet( VOID )
{
  DBL ratio_x, ratio_y;

  ratio_x = ratio_y = DP3_RndProjSize / 2;
  if (DP3_RndFrameW >= DP3_RndFrameH)
    ratio_x *= (DBL)DP3_RndFrameW / DP3_RndFrameH;
  else
    ratio_y *= (DBL)DP3_RndFrameH / DP3_RndFrameW;
  DP3_RndMatrProj = MatrFrustum(-ratio_x, ratio_x, -ratio_y, ratio_y,
                                DP3_RndProjDist, DP3_RndProjFarClip);
  DP3_RndMatrVP = MatrMulMatr(DP3_RndMatrView, DP3_RndMatrProj);
}

VOID DP3_RndCamSet( VEC Loc, VEC At, VEC Up1 )
{
  DP3_RndMatrView = MatrView(Loc, At, Up1);
  DP3_RndMatrVP = MatrMulMatr(DP3_RndMatrView, DP3_RndMatrProj);
}

