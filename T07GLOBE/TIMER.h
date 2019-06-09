#ifndef _TIMER_H_
#include <Windows.h>
#define _TIMER_H_
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
#endif