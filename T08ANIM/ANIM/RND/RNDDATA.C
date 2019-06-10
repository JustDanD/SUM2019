#include "Z:/SUM2019/T08ANIM/DEF.H"
#include "RND.H"

DBL
  DP3_RndProjSize = 0.1,  /* Project plane fit square */
  DP3_RndProjDist = 0.1,  /* Distance to project plane from viewer (near) */
  DP3_RndProjFarClip = 300;  /* Distance to project far clip plane (far) */

MATR
  DP3_RndMatrView, /* View coordinate system matrix */
  DP3_RndMatrProj, /* Projection coordinate system matrix */
  DP3_RndMatrVP;   /* Stored (View * Proj) matrix */

HWND DP3_hWndRnd;
HDC DP3_hDCRndFrame;
HBITMAP DP3_hBmRndFrame;
INT DP3_RndFrameW, DP3_RndFrameH;

