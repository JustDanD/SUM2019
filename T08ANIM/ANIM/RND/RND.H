#ifndef _RND_H_
#define _RND_H_
#include "Z:/SUM2019/T08ANIM/DEF.H"

VOID DP3_RndInit( HWND hWnd );

extern DBL
  DP3_RndProjSize,  /* Project plane fit square */
  DP3_RndProjDist,  /* Distance to project plane from viewer (near) */
  DP3_RndProjFarClip;  /* Distance to project far clip plane (far) */

extern MATR
  DP3_RndMatrView, /* View coordinate system matrix */
  DP3_RndMatrProj, /* Projection coordinate system matrix */
  DP3_RndMatrVP;   /* Stored (View * Proj) matrix */

extern HWND DP3_hWndRnd;
extern HDC DP3_hDCRndFrame;
extern HBITMAP DP3_hBmRndFrame;
extern INT DP3_RndFrameW, DP3_RndFrameH;

VOID DP3_RndProjSet( VOID );
VOID DP3_RndCamSet( VEC Loc, VEC At, VEC Up1 );
VOID DP3_RndCopyFrame( HDC hDC );
VOID DP3_RndStart( VOID );
VOID DP3_RndResize( INT W, INT H );
VOID DP3_RndClose( VOID );
#endif 