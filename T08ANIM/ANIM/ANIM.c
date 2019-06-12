/*  *FILENAME: ANIM.c 
    *PROGRAMMER: Pimenov Danila
    *DATE: 11.06.2019 
    *PURPOSE: project*/
#include "Z:/SUM2019/T08ANIM/DEF.H"
#include <windows.h>

#include <time.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "ANIM.h"
#include "RND/RND.H"


dp3ANIM DP3_ANIM;

VOID DP3_AnimInit( HWND hWnd )
{
  INT i;
  TimerInit();
  DP3_RndInit(hWnd);
  DP3_ANIM.hWnd = hWnd;
  DP3_ANIM.hDC = DP3_hDCRndFrame;
}

VOID DP3_AnimClose( VOID )
{
  INT i;

  for (i = 0; i < DP3_ANIM.NumOfUnits; i++)
  {
    DP3_ANIM.Units[i]->Close(DP3_ANIM.Units[i], &DP3_ANIM);
    free(DP3_ANIM.Units[i]);
    DP3_ANIM.Units[i] = NULL;
  }
  DP3_ANIM.NumOfUnits = 0;
  DP3_RndClose();
}

VOID DP3_AnimRender( VOID )
{
  INT i;

  for (i = 0; i < DP3_ANIM.NumOfUnits; i++)
    DP3_ANIM.Units[i]->Init(DP3_ANIM.Units[i], &DP3_ANIM);
  for (i = 0; i < DP3_ANIM.NumOfUnits; i++)
    DP3_ANIM.Units[i]->Response(DP3_ANIM.Units[i], &DP3_ANIM);

  DP3_RndStart();
  for (i = 0; i < DP3_ANIM.NumOfUnits; i++)
    DP3_ANIM.Units[i]->Render(DP3_ANIM.Units[i], &DP3_ANIM);
  //DP3_RndEnd();
}

VOID DP3_AnimResize( INT W, INT H)
{
  DP3_RndResize(W, H);
  DP3_ANIM.W = DP3_RndFrameW;
  DP3_ANIM.H = DP3_RndFrameH;
}

VOID DP3_AnimCopyFrame( HDC hDC )
{
  DP3_RndCopyFrame(hDC);
}

VOID DP3_AnimAddUnit( dp3UNIT *Uni )
{
  if (DP3_ANIM.NumOfUnits < DP3_MAX_UNITS)
    DP3_ANIM.Units[DP3_ANIM.NumOfUnits++] = Uni, Uni->Init(Uni, &DP3_ANIM);
}



/* End of "ANIM.c" function */