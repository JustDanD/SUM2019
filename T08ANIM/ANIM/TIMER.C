#include <windows.h>
#include <time.h>

#include "anim.h"


LARGE_INTEGER t;

static UINT64
StartTime,    /* Start program time */
OldTime,      /* Previous frame time */
OldTimeFPS,   /* Old time FPS measurement */
PauseTime,    /* Time during pause period */
TimePerSec,   /* Timer resolution */
FrameCounter;

DOUBLE
GlobalTime, GlobalDeltaTime, /* Global time and interframe interval */
Time, DeltaTime,             /* Time with pause and interframe interval */
FPS;                         /* Frames per second value */
BOOL
IsPause;

VOID TimerInit(VOID) //Timer initialization 
{
  LARGE_INTEGER t;

  QueryPerformanceFrequency(&t);
  TimePerSec = t.QuadPart;
  QueryPerformanceCounter(&t);
  StartTime = OldTime = OldTimeFPS = t.QuadPart;
  FrameCounter = 0;
  DP3_Anim.IsPause = FALSE;
  DP3_Anim.FPS = 30.0;
  PauseTime = 0;
}

VOID TimerResponse(VOID) // Timer update
{
  LARGE_INTEGER t;

  QueryPerformanceCounter(&t);
  /* Global time */
  DP3_Anim.GlobalTime = (DOUBLE)(t.QuadPart - StartTime) / TimePerSec;
  DP3_Anim.GlobalDeltaTime = (DOUBLE)(t.QuadPart - OldTime) / TimePerSec;

  /* Time with pause */
  if (IsPause)
  {
    DP3_Anim.DeltaTime = 0;
    PauseTime += t.QuadPart - OldTime;
  }
  else
  {
    DP3_Anim.DeltaTime = DP3_Anim.GlobalDeltaTime;
    DP3_Anim.Time = (DOUBLE)(t.QuadPart - PauseTime - StartTime) / TimePerSec;
  }
  /* FPS */
  FrameCounter++;
  if (t.QuadPart - OldTimeFPS > TimePerSec)
  {
    DP3_Anim.FPS = FrameCounter * TimePerSec / (DOUBLE)(t.QuadPart - OldTimeFPS);
    OldTimeFPS = t.QuadPart;
    FrameCounter = 0;
  }
  OldTime = t.QuadPart;
}