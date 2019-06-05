/* FILE NAME: T03CLOCK.C
   PRORAMMER: Daila Pimenov
   DATE: 03.0.6.2019
   PURPOSE: WinAPI
*/
#include <stdlib.h>
#include <windows.h>
#include <math.h>
#include <time.h>
#include <stdio.h>
#define PI 3.14159265358979323846

#define WND_CLASS_NAME "My class"

LRESULT CALLBACK MyWindowFunc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);


VOID FlipFullScreen(HWND hWnd)
{
	static BOOL IsFullScreen = FALSE; /* текущий режим */
	static RECT SaveRC;               /* сохраненный размер */

	if (!IsFullScreen)
	{
		RECT rc;
		HMONITOR hmon;
		MONITORINFOEX moninfo;

		/* сохраняем старый размер окна */
		GetWindowRect(hWnd, &SaveRC);

		/* определяем в каком мониторе находится окно */
		hmon = MonitorFromWindow(hWnd, MONITOR_DEFAULTTONEAREST);

		/* получаем информацию для монитора */
		moninfo.cbSize = sizeof(moninfo);
		GetMonitorInfo(hmon, (MONITORINFO *)&moninfo);

		/* переходим в полный экран */
		/* для одного монитора:
		rc.left = 0;
		rc.top = 0;
		rc.right = GetSystemMetrics(SM_CXSCREEN);
		rc.bottom = GetSystemMetrics(SM_CYSCREEN);
		*/
		rc = moninfo.rcMonitor;

		AdjustWindowRect(&rc, GetWindowLong(hWnd, GWL_STYLE), FALSE);

		SetWindowPos(hWnd, HWND_TOP, /* можно HWND_TOPMOST */
			rc.left, rc.top,
			rc.right - rc.left, rc.bottom - rc.top + 201,
			SWP_NOOWNERZORDER);
		IsFullScreen = TRUE;
	}
	else
	{
		/* восстанавливаем размер окна */
		SetWindowPos(hWnd, HWND_TOP,
			SaveRC.left, SaveRC.top,
			SaveRC.right - SaveRC.left, SaveRC.bottom - SaveRC.top,
			SWP_NOOWNERZORDER);
		IsFullScreen = FALSE;
	}
} /* End of 'FlipFullScreen' function */

void DrawEye(HDC hDC, INT x, INT y, INT r, INT r1, INT mx, INT my)
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
		Ellipse(hDC, mx - r1, my + r1, mx + r1, my - r1);
	}
	else
	{
		SelectObject(hDC, GetStockObject(BLACK_BRUSH));
		Ellipse(hDC, dx - r1, dy - r1, dx + r1, dy + r1);
	}

}
INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, CHAR *CmdLine, INT showCmd)
{
	WNDCLASS wc;
	HWND hWnd;
	MSG msg;

	wc.style = CS_DROPSHADOW;
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

	hWnd = CreateWindow(WND_CLASS_NAME, "Zoka", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);

	ShowWindow(hWnd, SW_SHOWNORMAL);
	UpdateWindow(hWnd);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

LRESULT CALLBACK MyWindowFunc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	HDC hDC;
	static HDC hMemDC, hMemDCClock;
	static HBITMAP hBm, hBmClock;
	HBRUSH hbr, hrbold;
	POINT points[4];
	POINT points4[4];
	POINT points1[4];
	POINT points2[4];
	HPEN hPen, hOldPen;
	POINT pt;
	BITMAP bm;
	INT i;
	SYSTEMTIME st;
	static INT w, h;
	BYTE Keys[256];

	switch (Msg)
	{
	case WM_CREATE:
		SetTimer(hWnd, 47, 30, NULL);
		hDC = GetDC(hWnd);
		hMemDC = CreateCompatibleDC(hDC);
		hMemDCClock = CreateCompatibleDC(hDC);

		ReleaseDC(hWnd, hDC);
		hBmClock = LoadImage(NULL, "faceclock.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		SelectObject(hMemDCClock, hBmClock);
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
		GetLocalTime(&st);
		hDC = GetDC(hWnd);
		GetObject(hBmClock, sizeof(bm), &bm);
		Rectangle(hMemDC, 0, 0, w, h);

		BitBlt(hMemDC, 0, 0, bm.bmWidth, bm.bmHeight, hMemDCClock, 0, 0, SRCCOPY);

		hPen = CreatePen(PS_SOLID, 4, RGB(121, 200, 30));
		hOldPen = SelectObject(hMemDC, hPen);


		SelectObject(hMemDC, hPen);
		SelectObject(hMemDC, GetStockObject(BLACK_BRUSH));
		points[1].x = 350;
		points[0].x = cos((((2 * PI) / 60) * (st.wSecond + st.wMilliseconds / 1000.0)) - (PI / 2) - PI / 45) * 160 + 350;
		points[2].x = cos((((2 * PI) / 60) * (st.wSecond + st.wMilliseconds / 1000.0)) - (PI / 2) + PI / 45) * 160 + 350;
		points[3].x = cos((((2 * PI) / 60) * (st.wSecond + st.wMilliseconds / 1000.0)) - (PI / 2)) *  (bm.bmWidth / 2) + 350;

		points[1].y = 350;
		points[0].y = sin((((2 * PI) / 60) * (st.wSecond + st.wMilliseconds / 1000.0)) - (PI / 2) - PI / 45) * 160 + 350;
		points[2].y = sin((((2 * PI) / 60) * (st.wSecond + st.wMilliseconds / 1000.0)) - (PI / 2) + PI / 45) * 160 + 350;
		points[3].y = sin((((2 * PI) / 60) * (st.wSecond + st.wMilliseconds / 1000.0)) - (PI / 2)) *  (bm.bmHeight / 2) + 350;

		points1[1].x = 350;
		points1[0].x = cos((((2 * PI) / 60) * (st.wMinute + st.wSecond / 60.0)) - (PI / 2) - PI / 45) * 160 + 350;
		points1[2].x = cos((((2 * PI) / 60) * (st.wMinute + st.wSecond / 60.0)) - (PI / 2) + PI / 45) * 160 + 350;
		points1[3].x = cos((((2 * PI) / 60) * (st.wMinute + st.wSecond / 60.0)) - (PI / 2)) *  (bm.bmWidth / 3) + 350;

		points1[1].y = 350;
		points1[0].y = sin((((2 * PI) / 60) * (st.wMinute + st.wSecond / 60.0)) - (PI / 2) - PI / 45) * 160 + 350;
		points1[2].y = sin((((2 * PI) / 60) * (st.wMinute + st.wSecond / 60.0)) - (PI / 2) + PI / 45) * 160 + 350;
		points1[3].y = sin((((2 * PI) / 60) * (st.wMinute + st.wSecond / 60.0)) - (PI / 2)) *  (bm.bmHeight / 3) + 350;

		points2[1].x = 350;
		points2[0].x = cos((((2 * PI) / 60) * (st.wHour % 12 + st.wMinute / 60.0 + 29)) - (PI / 2) - PI / 45) * 160 + 350;
		points2[2].x = cos((((2 * PI) / 60) * (st.wHour % 12 + st.wMinute / 60.0 + 29)) - (PI / 2) + PI / 45) * 160 + 350;
		points2[3].x = cos((((2 * PI) / 60) * (st.wHour % 12 + st.wMinute / 60.0 + 29)) - (PI / 2)) *  (bm.bmWidth / 4) + 350;

		points2[1].y = 350;
		points2[0].y = sin((((2 * PI) / 60) * (st.wHour % 12 + st.wMinute / 60.0 + 29)) - (PI / 2) - PI / 45) * 160 + 350;
		points2[2].y = sin((((2 * PI) / 60) * (st.wHour % 12 + st.wMinute / 60.0 + 29)) - (PI / 2) + PI / 45) * 160 + 350;
		points2[3].y = sin((((2 * PI) / 60) * (st.wHour % 12 + st.wMinute / 60.0 + 29)) - (PI / 2)) *  (bm.bmHeight / 4) + 350;
		/*for (i = 1; i < 3; i++)
		{
		  //points1[i].x = points4[i].x * cos((((2 * PI) / 60) * (st.wMinute + st.wSecond / 60.0)) - (PI / 2)) + points4[i].y * sin((((2 * PI) / 60) * (st.wMinute + st.wSecond / 60.0)) - (PI / 2));

		  points[i].x = cos((((2 * PI) / 60) * (st.wMinute + st.wSecond / 60.0)) - (PI / 2)) * (bm.bmWidth / 2);
		  points[i].y = sin((((2 * PI) / 60) * (st.wMinute + st.wSecond / 60.0)) - (PI / 2)) * (bm.bmWidth / 2);
		  //points2[i].x = points[i].x * cos((((2 * PI) / 12) * (st.wHour + st.wMinute / 60.0)) - (PI / 2)) + points2[i].y * sin((((2 * PI) / 12) * (st.wHour + st.wMinute / 60.0)) - (PI / 2));
		}
	   // Polygon(hMemDC, points1, 4);
	   // Polygon(hMemDC, points2, 4);
		*/


		Polygon(hMemDC, points, 4);
		Polygon(hMemDC, points1, 4);
		Polygon(hMemDC, points2, 4);

		/*
		 LineTo(hMemDC, cos((((2 * PI) / 60) * (st.wMinute + st.wSecond / 60.0)) - (PI / 2)) * (bm.bmWidth / 2) + w / 2,
						 sin((((2 * PI) / 60) * (st.wMinute + st.wSecond / 60.0)) - (PI / 2)) * (bm.bmWidth / 2) + h / 2);
		  MoveToEx(hMemDC,w / 2 , h / 2, NULL);
		  LineTo(hMemDC, cos((((2 * PI) / 12) * (st.wHour % 12 + st.wMinute / 60.0)) - (PI / 2)) * (bm.bmWidth / 2) + w / 2,
						 sin((((2 * PI) / 12) * (st.wHour % 12 + st.wMinute / 60.0)) - (PI / 2)) * (bm.bmWidth / 2) + h / 2);
		  */
		DeleteObject(hPen);
		BitBlt(hDC, 0, 0, w, h, hMemDC, 0, 0, SRCCOPY);
		ReleaseDC(hWnd, hDC);
		return 0;
	case WM_KEYDOWN:
		GetKeyboardState(Keys);
		if (Keys['F'] & 0x80)
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