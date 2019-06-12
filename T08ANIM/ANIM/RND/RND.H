/*  *FILENAME: ANIM.h 
    *PROGRAMMER: Pimenov Danila
    *DATE: 11.06.2019 
    *PURPOSE: project*/

#ifndef _RND_H_
#define _RND_H_



#include "../../DEF.H"





typedef struct tagdp3VERTEX
{
  VEC P;  /* Vertex position */
} dp3VERTEX;


typedef struct tagdp3PRIM
{
  dp3VERTEX *V; /* Vertex attributes array */
  INT NumOfV;   /* Number of vertices */

  INT *I;       /* Index array (for trimesh - by 3 ones) */
  INT NumOfI;   /* Number of indices */

  MATR Trans;   /* Additional transformation matrix */
} dp3PRIM;


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

VOID DP3_RndInit( HWND hWnd );
VOID DP3_RndProjSet( VOID );
VOID DP3_RndCamSet( VEC Loc, VEC At, VEC Up1 );
VOID DP3_RndCopyFrame( HDC hDC );
VOID DP3_RndStart( VOID );
VOID DP3_RndResize( INT W, INT H );
VOID DP3_RndClose( VOID );
BOOL DP3_RndPrimLoad( dp3PRIM *Pr, CHAR *FileName );
VOID DP3_RndPrimDraw( dp3PRIM *Pr, MATR World );
VOID DP3_RndPrimFree( dp3PRIM *Pr );
BOOL DP3_RndPrimCreate( dp3PRIM *Pr, INT NoofV, INT NoofI );
#endif 