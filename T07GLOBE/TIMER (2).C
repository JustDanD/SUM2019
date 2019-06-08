–еализуем таймер Ц абстракцию, необходимую дл€ организации синхронизации по времени. Ќеобходимые данные от таймера Ц врем€ работы системы (Total Time) и межкадрова€ временна€ задержка (Delta Time).

Old style: (классический вариант со стандартной библиотекой, <time.h>)

  #include <time.h>
  clock() -> tick -> CLOCKS_PER_SEC
  StartTime = clock();
 
на каждом шаге:
  long t = clock();

  GlobalTimeInSec = (t - StartTime) / (DBL)CLOCKS_PER_SEC;

High resolution timer: (вариант с таймеров высокого разрешени€, <windows.h>)

  static UINT64        /* переопределение: typedef unsigned long long UINT64; */
    StartTime,  /* Start program time */
    TimePerSec; /* Timer resolution */

на старте программы:
  LARGE_INTEGER t;

определить точность таймера (тики в секунду)
  QueryPerformanceFrequency(&t);
  TimePerSec = t.QuadPart;
определить врем€ начала
  QueryPerformanceCounter(&t);
  StartTime = t.QuadPart;

„то потребуетс€:
-- врем€ начала программы
   StartTime
-- общее врем€ работы - global time
     t - StartTime
-- межкадрова€ задержка времени (без учета паузы) - global delta time
     t Ц OldTime    (OldTime Ц врем€ прошлого кадра)
-- pause flag:
     IsPause
-- локальное врем€ (с учетом паузы) - local time
     t Ц PauseTime - StartTime
-- межкадрова€ задержка с учетом паузы - local delta time
     == global delta time  если !IsPause
     == 0                  если IsPause
дл€ вычислени€ PauseTime:
  если IsPause:
    PauseTime += t - OldTime
-- дл€ определени€ количества кадров в секунду - frames per second (FPS):
     1 time per second:
       FrameCounter Ц счетчик кадров
       OldTimeFPS   Ц врем€ прошлого замера FPS

–еализаци€
TIMER:
-- "внутренние" (вспомогательные) данные:
  static UINT64
    StartTime,    /* Start program time */
    OldTime,      /* Previous frame time */
    OldTimeFPS,   /* Old time FPS measurement */
    PauseTime,    /* Time during pause period */
    TimePerSec,   /* Timer resolution */
    FrameCounter; /* Frames counter */

-- данные дл€ пользовател€ (в структуре ANIM дл€ доступа из объектов анимации):
  DBL
    GlobalTime, GlobalDeltaTime, /* Global time and interframe interval */
    Time, DeltaTime,             /* Time with pause and interframe interval */
    FPS;                         /* Frames per second value */
  BOOL
    IsPause;                     /* Pause flag */
?
‘ункции:
TimerInit:    <-- при старте всей программы (или системы вывода/анимации)
  LARGE_INTEGER t;

  QueryPerformanceFrequency(&t);
  TimePerSec = t.QuadPart;
  QueryPerformanceCounter(&t);
  StartTime = OldTime = OldTimeFPS = t.QuadPart;
  FrameCounter = 0;
  IsPause = FALSE;
  FPS = 30.0;
  PauseTime = 0;

TimerResponse:<-- на каждом кадре, перед стартом вывода (начало построени€ кадра)
  LARGE_INTEGER t;

  QueryPerformanceCounter(&t);
  /* Global time */
  GlobalTime = (DBL)(t.QuadPart - StartTime) / TimePerSec;
  GlobalDeltaTime = (DBL)(t.QuadPart - OldTime) / TimePerSec;

  /* Time with pause */
  if (IsPause)
  {
    DeltaTime = 0;
    PauseTime += t.QuadPart Ц OldTime;
  }
  else
  {
    DeltaTime = GlobalDeltaTime;
    Time = (DBL)(t.QuadPart Ц PauseTime - StartTime) / TimePerSec;
  }
  /* FPS */
  FrameCounter++;
  if (t.QuadPart Ц OldTimeFPS > TimePerSec)
  {
    FPS = FrameCounter * TimePerSec / (DBL)(t.QuadPart Ц OldTimeFPS);
    OldTimeFPS = t.QuadPart;
    FrameCounter = 0;
  }
  OldTime = t.QuadPart;
