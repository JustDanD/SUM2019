/* *FILE NAME: MAIN.C
   *PRORAMMER: Danila Pimenov
   *DATE: 10.06.2019
   *PURPOSE: WinAPI
*/

#define WND_CLASS_NAME "My window class"

#include <windows.h>

#include <time.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


#include "Z:/SUM2019/T08ANIM/DEF.H"
#include "ANIM/ANIM.h"

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
  
  TimerInit();

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
  DP3_AnimAddUnit(DP3_ANIMUnitCowCreate());
  //DP3_AnimAddUnit(DP3_ANIMUnitIronCreate());

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
/* End of 'FlipFullScreen' function */

LRESULT CALLBACK MyWindowFunc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
  HDC hDC;
  BYTE Keys[256];
  PAINTSTRUCT ps; 
    INT w, h;

  switch (Msg)
  {
  case WM_CREATE:
    DP3_AnimInit(hWnd);
    SetTimer(hWnd, 47, 2, NULL); 
    return 0;
  case WM_SIZE:
    w = LOWORD(lParam);
    h = HIWORD(lParam);
    DP3_AnimResize(w, h);
    SendMessage(hWnd, WM_TIMER, 47, 0);
    return 0;
  case WM_TIMER:
    DP3_AnimRender();
    hDC = GetDC(hWnd);  
    DP3_AnimCopyFrame(hDC);
    ReleaseDC(hWnd, hDC);
    return 0;
  case WM_ERASEBKGND:
    return 1;
  case WM_PAINT:
    hDC = BeginPaint(hWnd, &ps);
    DP3_AnimCopyFrame(hDC);
    EndPaint(hWnd, &ps);
    return 0;
  case WM_KEYDOWN:

    return 0;
  case WM_DESTROY:
    DP3_AnimClose();
    KillTimer(hWnd, 47);
    return 0;
  }
  return DefWindowProc(hWnd, Msg, wParam, lParam);
}