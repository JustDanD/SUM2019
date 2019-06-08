#ifndef _HEADER_H_
#define _HEADER_H
#include <windows.h>
#endif


VOID GLOBE( void );
VOID DRAW (HDC hDC, INT w, INT h);

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
