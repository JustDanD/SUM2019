/**/
#include <stdlib.h>
#include <windows.h>
#include <math.h>
#include <time.h>

#define WND_CLASS_NAME "My class"

LRESULT CALLBACK MyWindowFunc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam );


void DrawEye( HDC hDC, INT x, INT y, INT r, INT r1, INT mx, INT my)
{
  HBRUSH hbr, hrbold;
  DOUBLE t;
  INT dx, dy;
  SelectObject(hDC, GetStockObject(GRAY_BRUSH));
  Ellipse(hDC, x - (r + 50), y + (r + 50), x + (r + 50), y - (r + 50));
  SelectObject(hDC, GetStockObject(DC_BRUSH));
  SetDCBrushColor(hDC, RGB(155, 123, 55));
  Ellipse(hDC, x - r, y + r, x + r, y - r);
  SelectObject(hDC, GetStockObject(BLACK_BRUSH));
  t = (r - r1) / sqrt((mx - x) * (mx - x) + (my - y) * (my - y));
  dx = (int)(mx - x) * t + x;
  dy = (int)(my - y) * t + y; 
  if (sqrt((mx - x) * (mx - x) + (my - y) * (my - y)) + r1 < r)
  {
    SelectObject(hDC, GetStockObject(BLACK_BRUSH));
    Ellipse(hDC, mx - r1, my + r1,  mx + r1, my - r1);
  }
  else
  {
    SelectObject(hDC, GetStockObject(BLACK_BRUSH));
    Ellipse(hDC, dx - r1, dy - r1,  dx + r1, dy + r1);
  }

}
INT WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, CHAR *CmdLine, INT showCmd )
{
  WNDCLASS wc;
  HWND hWnd;
  MSG msg;

  wc.style =  CS_DROPSHADOW;
  wc.cbClsExtra = 0;
  wc.cbWndExtra = 0;
  wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
  wc.hCursor = LoadCursor(NULL, IDC_HAND);
  wc.hIcon = LoadIcon(NULL, IDI_ERROR);
  wc.lpszClassName = WND_CLASS_NAME;
  wc.lpszMenuName = NULL;
  wc.hInstance = hInstance;
  wc.lpfnWndProc = MyWindowFunc;
  
  if (!RegisterClass(&wc))
  {
    MessageBox(NULL, "Error", "ERROR", MB_OK);
    return 0;
  }

  hWnd = CreateWindow( WND_CLASS_NAME, "Zoka", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);

  ShowWindow(hWnd, SW_SHOWNORMAL);
  UpdateWindow(hWnd);

  while (GetMessage(&msg, NULL, 0, 0))
  {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }
  return msg.wParam;
}

LRESULT CALLBACK MyWindowFunc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam )
{   
  HDC hDC;
  static HDC hMemDC;
  static HBITMAP hBm;
  POINT pt;
  INT i;
  static INT w, h;
  switch (Msg)
  {
  case WM_CREATE: 
   SetTimer(hWnd, 47, 30, NULL);
   hDC = GetDC(hWnd);
   hMemDC = CreateCompatibleDC(hDC);
   ReleaseDC(hWnd, hDC);
   return 0;
  case WM_SIZE:
    w = LOWORD(lParam);
    h = HIWORD(lParam);
    if (hBm != NULL)
      DeleteObject(hBm);
    hDC = GetDC(hWnd);
    hBm = CreateCompatibleBitmap(hDC, w, h);
    SelectObject(hMemDC, hBm);
    ReleaseDC(hWnd, hDC);
  return 0;
  case WM_TIMER:
    hDC = GetDC(hWnd);
    srand(30);
    Rectangle(hMemDC, 0, 0, w, h);
    GetCursorPos(&pt);
    ScreenToClient(hWnd, &pt);
    for (i = 0; i < 30; i++)
    {
      DrawEye(hMemDC, rand() % 1920  + sin((double)(clock() / 100.0) + i) * 40, rand() % 1080  + sin(2 * ((double)(clock() / 100.0 + i))) * 40, 50, 10, pt.x, pt.y);
    }
    BitBlt(hDC, 0, 0, w, h, hMemDC, 0, 0, SRCCOPY);
    ReleaseDC(hWnd,hDC);
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