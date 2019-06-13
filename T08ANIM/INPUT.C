#include <windows.h>
#include <mmsystem.h>

#include "DEF.H"
#include "anim/anim.h"

#pragma comment(lib, "winmm")

#define VG4_GET_JOYSTIC_AXIS(A) \
   (2.0 * (ji.dw ## A ## pos - jc.w ## A ## min) / (jc.w ## A ## max - jc.w ## A ## min) - 1)


BYTE KeysOld[256],JButOld[32];

static VOID DP3_JoystickRespons( VOID );
static VOID KeyboardRespons( VOID );   

/*-------------------------------*/

VOID KeyboardInit( VOID )
{
  memset(DP3_Anim.Keys, 0, 256);
  memset(KeysOld, 0, 256);
  memset(DP3_Anim.KeysClick, 0, 256);
}

/*------------------------------*/

VOID MouseInit( VOID )
{
  DP3_Anim.Mx = 0;
  DP3_Anim.My = 0;
  DP3_Anim.Mz = 0;
  DP3_Anim.Mdx = 0;
  DP3_Anim.Mdy = 0; 
  DP3_Anim.Mdz = 0;
}

/*---------------------------*/

VOID DP3_InputInit( VOID )
{
  MouseInit();
  KeyboardInit();
  //JoystickInit();
}  

/*=========================*/

VOID DP3_InputRespons( VOID )
{
  DP3_JoystickRespons();
  KeyboardRespons();
  //JoystickInit();
}

/*===========================*/

static VOID KeyboardRespons( VOID )
{
  INT i;

  GetKeyboardState(DP3_Anim.Keys);
  for (i = 0; i < 256; i++)
  {                                                                
    DP3_Anim.Keys[i] >>= 7;
    DP3_Anim.KeysClick[i] = DP3_Anim.Keys[i] && !KeysOld[i];  
  }
  memcpy(KeysOld, DP3_Anim.Keys, 256);
}

/*==================================*/
static VOID DP3_JoystickRespons( VOID )
{
  INT i;
  if (joyGetNumDevs() > 0)
  {
    JOYCAPS jc;

    /* Get joystick info */
    if (joyGetDevCaps(JOYSTICKID1, &jc, sizeof(jc)) == JOYERR_NOERROR)
    {
      JOYINFOEX ji;

      ji.dwSize = sizeof(JOYINFOEX);
      ji.dwFlags = JOY_RETURNALL;
      if (joyGetPosEx(JOYSTICKID1, &ji) == JOYERR_NOERROR)
      {
        /* Buttons */
        for (i = 0; i < 32; i++)
        {
          DP3_Anim.JBut[i] = (ji.dwButtons >> i) & 1;
          DP3_Anim.JButClick[i] = DP3_Anim.JBut[i] && !JButOld[i];
          JButOld[i] = DP3_Anim.JBut[i];
        }

        /* Axes */
        DP3_Anim.JX = VG4_GET_JOYSTIC_AXIS(X);
        DP3_Anim.JY = VG4_GET_JOYSTIC_AXIS(Y);
        DP3_Anim.JZ = VG4_GET_JOYSTIC_AXIS(Z);
        DP3_Anim.JR = VG4_GET_JOYSTIC_AXIS(R);

        /* Point of view */
        DP3_Anim.JPov = ji.dwPOV == 0xFFFF ? -1 : ji.dwPOV / 4500;
      }
    }
  }
}
/*=========================================*/


