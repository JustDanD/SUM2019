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


dp3ANIM DP3_Anim;

/*------------------------------------*/

VOID DP3_AnimInit( HWND hWnd )
{
  INT i;
  TimerInit();
  DP3_RndInit(hWnd);
  DP3_Anim.hWnd = hWnd;
  DP3_Anim.hDC = DP3_hDCRndFrame;
  DP3_InputInit();
}
/*=============================*/


VOID DP3_AnimClose( VOID )
{
  INT i;

  for (i = 0; i < DP3_Anim.NumOfUnits; i++)
  {
    DP3_Anim.Units[i]->Close(DP3_Anim.Units[i], &DP3_Anim);
    free(DP3_Anim.Units[i]);
    DP3_Anim.Units[i] = NULL;
  }
  DP3_Anim.NumOfUnits = 0;
  DP3_RndClose();
}

/*------------------------------------*/

VOID DP3_AnimRender( VOID )
{
  INT i;

  for (i = 0; i < DP3_Anim.NumOfUnits; i++)
    DP3_Anim.Units[i]->Init(DP3_Anim.Units[i], &DP3_Anim);
  for (i = 0; i < DP3_Anim.NumOfUnits; i++)
    DP3_Anim.Units[i]->Response(DP3_Anim.Units[i], &DP3_Anim);

  DP3_RndStart();
  for (i = 0; i < DP3_Anim.NumOfUnits; i++)
    DP3_Anim.Units[i]->Render(DP3_Anim.Units[i], &DP3_Anim);
  //DP3_RndEnd();
}

/*----------------------------------*/

VOID DP3_AnimFlipFullScreen(HWND hWnd)
{
  static BOOL IsFullScreen = FALSE;
  static RECT SaveRC;

  if (!IsFullScreen)
  {
    RECT rc;
    HMONITOR hmon;
    MONITORINFOEX moninfo;

    GetWindowRect(hWnd, &SaveRC);

    hmon = MonitorFromWindow(hWnd, MONITOR_DEFAULTTONEAREST);

    moninfo.cbSize = sizeof(moninfo);
    GetMonitorInfo(hmon, (MONITORINFO *)&moninfo);

    rc = moninfo.rcMonitor;

    AdjustWindowRect(&rc, GetWindowLong(hWnd, GWL_STYLE), FALSE);

    SetWindowPos(hWnd, HWND_TOP,
      rc.left, rc.top,
      rc.right - rc.left, rc.bottom - rc.top + 201,
      SWP_NOOWNERZORDER);
    IsFullScreen = TRUE;
  }
  else
  {
    SetWindowPos(hWnd, HWND_TOP,
      SaveRC.left, SaveRC.top,
      SaveRC.right - SaveRC.left, SaveRC.bottom - SaveRC.top,
      SWP_NOOWNERZORDER);
    IsFullScreen = FALSE;
  }
} 

/*--------------------------------*/

VOID DP3_AnimResize( INT W, INT H)
{
  DP3_RndResize(W, H);
  DP3_Anim.W = DP3_RndFrameW;
  DP3_Anim.H = DP3_RndFrameH;
}

/* ----------------------------*/

VOID DP3_AnimCopyFrame( HDC hDC )
{
  DP3_RndCopyFrame(hDC);
}

/*-------------------------------------------*/

VOID DP3_AnimAddUnit( dp3UNIT *Uni )
{
  if (DP3_Anim.NumOfUnits < DP3_MAX_UNITS)
    DP3_Anim.Units[DP3_Anim.NumOfUnits++] = Uni, Uni->Init(Uni, &DP3_Anim);
}



/* End of "ANIM.c" function */