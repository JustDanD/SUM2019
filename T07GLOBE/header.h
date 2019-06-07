#define PI 3.14159265358979323846
#include <windows.h>
#define N 25
#define M 30


typedef struct
{
  DOUBLE X, Y, Z;
}VEC;

VOID GLOBE( void );
VOID DRAW (HDC hDC, INT w, INT h);
VEC ROT_X(VEC p, DOUBLE angle);
VEC ROT_Y(VEC p, DOUBLE angle);
VOID GLB_TimerInit( VOID );
VOID GLB_TimerResponse( VOID );

extern DOUBLE GLB_Time,      
      GLB_DeltaTime, 
      GLB_FPS;        
extern BOOL GLB_IsPause;   
extern LONG StartTime,     
       OldTime,       
       PauseTime,     
       OldFPSTime,    
       FrameCount;