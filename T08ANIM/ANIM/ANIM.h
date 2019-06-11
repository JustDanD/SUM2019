/*  *FILENAME: ANIM.h 
    *PROGRAMMER: Kiselev Igor
    *DATE: 11.06.2019 
    *PURPOSE: project*/
#ifndef __ANIM_H_
#define __ANIM_H_
#include "Z:/SUM2019/T08ANIM/DEF.H"
#include <windows.h>
#include <time.h>


#define DP3_MAX_UNITS 3000
//#define UNIT_BASE_FIELDS \
//  VOID (*Init)( UNIT *Uni, ANIM *Ani );      \
//  VOID (*Close)( UNIT *Uni, ANIM *Ani );     \
//  VOID (*Response)( UNIT *Uni, ANIM *Ani );  \
//  VOID (*Render)( UNIT *Uni, ANIM *Ani )


typedef struct tagDP3_UNIT DP3_UNIT;

typedef struct tagDP3_ANIM
{
  HWND hWnd;
  HDC hDC;
  INT W, H;
  DP3_UNIT *Units[DP3_MAX_UNITS];
  INT NumOfUnits;
} DP3_ANIM;

typedef struct tagDP3_UNIT
{
  VOID (*Init)( DP3_UNIT *Uni, DP3_ANIM *Ani );     
  VOID (*Close)( DP3_UNIT *Uni, DP3_ANIM *Ani );     
  VOID (*Response)( DP3_UNIT *Uni, DP3_ANIM *Ani );  
  VOID (*Render)( DP3_UNIT *Uni, DP3_ANIM *Ani );
};

typedef unsigned long long UINT64;
static UINT64
StartTime,    /* Start program time */
OldTime,      /* Previous frame time */
OldTimeFPS,   /* Old time FPS measurement */
PauseTime,    /* Time during pause period */
TimePerSec,   /* Timer resolution */
FrameCounter;

extern DOUBLE
GlobalTime, GlobalDeltaTime, /* Global time and interframe interval */
Time, DeltaTime,             /* Time with pause and interframe interval */
FPS;                         /* Frames per second value */
BOOL
IsPause;
VOID TimerResponse(VOID);
VOID TimerInit(VOID);
DP3_ANIM DP3_Anim;
#endif
/* End of "ANIM.h" function */