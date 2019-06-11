/* *FILE NAME: MAIN.C
   *PRORAMMER: Danila Pimenov
   *DATE: 10.06.2019
   *PURPOSE: WinAPI
*/



#include <windows.h>
#define WND_CLASS_NAME "My window class"
#include <math.h>
#include <stdlib.h>
#include "Z:/SUM2019/T08ANIM/DEF.H"
#include "ANIM/RND/RND.H" 
#include "MTH/MTH.h"
#include <time.h>
LRESULT CALLBACK MyWindowFunc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, CHAR *CmdLine, INT ShawCmd)
{
  WNDCLASS wc;
  HWND hWnd;
  MSG msg;
 

  wc.cbClsExtra = 0;
  wc.cbWndExtra = 0;
  wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
  wc.hCursor = LoadCursor(NULL, IDI_ERROR);
  wc.hIcon = LoadIcon(NULL, IDI_SHIELD);
  wc.hInstance = hInstance;
  wc.lpfnWndProc = MyWindowFunc;
  wc.lpszClassName = WND_CLASS_NAME;
  wc.lpszMenuName = NULL;
  wc.style = CS_VREDRAW | CS_HREDRAW | CS_DBLCLKS;
  
  //TimerInit();

  if (!RegisterClass(&wc))
  {
    MessageBox(NULL, "Oh no", "ERROR", MB_OK);
    return 0;
  }
  hWnd = CreateWindow(WND_CLASS_NAME, "OKNO", WS_OVERLAPPEDWINDOW,
    0, 0,
    900, 900,
    NULL, NULL, hInstance, NULL);
  ShowWindow(hWnd, SW_SHOWNORMAL);
  UpdateWindow(hWnd);

  while (TRUE)
    if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
    {
      if (msg.message == WM_QUIT)
        break;
      DispatchMessage(&msg);
    }
    else
      SendMessage(hWnd, WM_TIMER, 47, 0);
  return msg.wParam;
}
VOID FlipFullScreen(HWND hWnd)
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
} /* End of 'FlipFullScreen' function */

LRESULT CALLBACK MyWindowFunc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
  HDC hDC;
  BYTE Keys[256];
  PAINTSTRUCT ps;
  static dp3PRIM Pr; 

  switch (Msg)
  {
  case WM_CREATE:
    DP3_RndInit(hWnd);
    SetTimer(hWnd, 47, 2, NULL);
    DP3_RndPrimLoad(&Pr, "IronMan.obj"); 
    return 0;
  case WM_SIZE:
    DP3_RndResize(LOWORD(lParam), HIWORD(lParam));
    SendMessage(hWnd, WM_TIMER, 47, 0);
    return 0;
  case WM_TIMER:
    DP3_RndStart();
    //DP3_RndEnd();
    DP3_RndCamSet(VecSet(10, 20, 50), VecSet(0, 0, 0), VecSet(0, 1, 0));
    
    Pr.Trans = MatrMulMatr(Pr.Trans, MatrRotateY(10));
    //Pr.Trans = MatrMulMatr(Pr.Trans, MatrTranslate(VecSet(10 * sin(clock()/1000), 0, 0)));
    DP3_RndPrimDraw(&Pr, Pr.Trans);
    hDC = GetDC(hWnd);  
    DP3_RndCopyFrame(hDC);
    ReleaseDC(hWnd, hDC);
    return 0;
  case WM_ERASEBKGND:
    return 1;
  case WM_PAINT:
    hDC = BeginPaint(hWnd, &ps);
    DP3_RndCopyFrame(hDC);
    EndPaint(hWnd, &ps);
    return 0;
  case WM_KEYDOWN:
    GetKeyboardState(Keys);
    if (Keys['F'] & 0x80)
      FlipFullScreen(hWnd);
    return 0;
  case WM_DESTROY:
    DP3_RndClose();
    KillTimer(hWnd, 47);
    return 0;
  }
  return DefWindowProc(hWnd, Msg, wParam, lParam);
}