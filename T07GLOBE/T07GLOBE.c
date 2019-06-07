#include "header.h"
#include <windows.h>
#define WND_CLASS_NAME "My window class"
#include <math.h>
#include <stdlib.h>
#include <time.h>
extern VEC G[N][M];


LRESULT CALLBACK MyWindowFunc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam );

INT WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, CHAR *CmdLine, INT ShawCmd )
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

  if (!RegisterClass(&wc))
  {
    MessageBox(NULL, "Oh no", "ERROR", MB_OK);
    return 0;
  }
  hWnd = CreateWindow(WND_CLASS_NAME, "OKNO", WS_OVERLAPPEDWINDOW,
    CW_USEDEFAULT, CW_USEDEFAULT, 
    CW_USEDEFAULT, CW_USEDEFAULT,
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
VOID FlipFullScreen( HWND hWnd )
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


LRESULT CALLBACK MyWindowFunc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam )
{
  HDC hDc;
  BYTE Keys[256];
  static int w, h;
  static HDC hMemDC;
  static HBITMAP hBm;
  MSG msg;
  SYSTEMTIME st;
  PAINTSTRUCT ps;
  INT x, y;

  switch (Msg)
  {
  case WM_CREATE:
    SetTimer(hWnd, 47, 1000, NULL);
    hDc = GetDC(hWnd);
    hMemDC = CreateCompatibleDC(hDc);
    ReleaseDC(hWnd, hDc);
    
    GLOBE();
    return 0;

  case WM_LBUTTONDBLCLK:
    FlipFullScreen(hWnd);
    return 0;
  case WM_SIZE:
    w = LOWORD(lParam);
    h = HIWORD(lParam);

    if (hBm != NULL)
      DeleteObject(hBm);
    hDc = GetDC(hWnd);
    hBm = CreateCompatibleBitmap(hDc, w, h);
    SelectObject(hMemDC, hBm);
    
    return 0;
  case WM_TIMER:
    GetLocalTime(&st);

    hDc = GetDC(hWnd);
    SelectObject(hMemDC, hBm);
    SelectObject(hMemDC, GetStockObject(WHITE_BRUSH));
    Rectangle(hMemDC, 0, 0, w, h);

    DRAW(hMemDC, w, h);
    BitBlt(hDc, 0, 0, w , h, hMemDC, 0, 0, SRCCOPY);
    ReleaseDC(hWnd, hDc);
    return 0;
case WM_KEYDOWN:
    GetKeyboardState(Keys);
    if (Keys['F'] & 0x80
      )
      FlipFullScreen(hWnd);
  return 0;
  
  case WM_CLOSE:    
     
    if (MessageBox(NULL, "Are you sure?", "Quit", MB_YESNO) == IDYES)
    {
      DeleteObject(hBm);
    DeleteDC(hMemDC);
    KillTimer(hWnd, 47);
    PostQuitMessage(0);
      return 0;
    }   
    else 
      Msg = WM_ACTIVATE;
  }
  
  return DefWindowProc(hWnd, Msg, wParam, lParam);
}