/*  *FILENAME: ANIM.h 
    *PROGRAMMER: Pimenov Danila
    *DATE: 11.06.2019 
    *PURPOSE: project*/
#ifndef __ANIM_H_
#define __ANIM_H_
#include "Z:/SUM2019/T08ANIM/DEF.H"

 #include <windows.h>

#include <time.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define DP3_MAX_UNITS 3000
//#define UNIT_BASE_FIELDS \
//  VOID (*Init)( UNIT *Uni, ANIM *Ani );      \
//  VOID (*Close)( UNIT *Uni, ANIM *Ani );     \
//  VOID (*Response)( UNIT *Uni, ANIM *Ani );  \
//  VOID (*Render)( UNIT *Uni, ANIM *Ani )



typedef struct tagDP3_UNIT dp3UNIT;

typedef struct tagdp3ANIM
{
  HWND hWnd;
  HDC hDC;
  INT W, H;
  dp3UNIT *Units[DP3_MAX_UNITS];
  INT NumOfUnits;

  INT Mx, My, Mz, Mdx, Mdy, Mdz;

  DBL
  GlobalTime, GlobalDeltaTime, /* Global time and interframe interval */
  Time, DeltaTime,             /* Time with pause and interframe interval */
  FPS;                         /* Frames per second value */
  BOOL
  IsPause;

  BYTE Keys[256];      
     
  BYTE KeysClick[256]; 

  BYTE
    JBut[32], JButClick[32]; /* Joystick button states */
  INT JPov;                               /* Joystick point-of-view control [-1,0..7] */
  DBL
    JX, JY, JZ, JR;                       /* Joystick axes */
} dp3ANIM;

#define UNIT_BASE \
    VOID (*Init)( dp3UNIT *Uni, dp3ANIM *Ani ); \
    VOID (*Close)( dp3UNIT *Uni, dp3ANIM *Ani ); \
    VOID (*Response)( dp3UNIT *Uni, dp3ANIM *Ani ); \
    VOID (*Render)( dp3UNIT *Uni, dp3ANIM *Ani )

typedef struct tagDP3_UNIT
{
  UNIT_BASE;
};


VOID TimerResponse(VOID);
VOID TimerInit(VOID);
extern dp3ANIM DP3_Anim;
VOID DP3_AnimInit( HWND hWnd );
VOID DP3_AnimClose( VOID );
VOID DP3_AnimRender( VOID );
VOID DP3_AnimResize( INT W, INT H);
VOID DP3_AnimCopyFrame( HDC hDC );
VOID DP3_AnimAddUnit( dp3UNIT *Uni );
VOID DP3_AnimFlipFullScreen(HWND hWnd);
#endif

/* End of "ANIM.h" function */