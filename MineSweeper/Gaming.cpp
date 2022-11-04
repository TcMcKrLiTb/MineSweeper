#include "Gaming.h"
#include "Themap.h"
#include <windows.h>

void NumPainting(PAINTSTRUCT *ps, HDC *hdc, HDC *hdcMem, int pos,
	int n1, int n2, int n3, int n4, int n5, int n6);
void BloPainting(PAINTSTRUCT *ps, HDC *hdc, HDC *hdcMem);
void ButPainting(PAINTSTRUCT* ps, HDC* hdc, HDC* hdcMem, int state);

HBITMAP g_hbmNum[10] = { NULL };
HBITMAP g_hbmBlo[14] = { NULL };
HBITMAP g_hbmBut[4] = { NULL };
HANDLE hHandle = NULL;
HANDLE TimerID_1s = NULL;
int allNums[7];
_Blocks game_map;
void MapPainting(HWND hwnd)
{
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(hwnd, &ps);
	HDC hdcMem = CreateCompatibleDC(hdc);
	ButPainting(&ps, &hdc, &hdcMem, game_map.game_state);
	NumPainting(&ps, &hdc, &hdcMem, ((game_map.size_col) * 25) - 39, allNums[1], allNums[2], allNums[3], allNums[4], allNums[5], allNums[6]);
	//Sleep(1000);
	BloPainting(&ps, &hdc, &hdcMem);

	DeleteDC(hdc);
	DeleteDC(hdcMem);
	EndPaint(hwnd, &ps);
	ReleaseDC(hwnd, hdc);
	//InvalidateRect(hwnd, NULL, TRUE);
}

void BloPainting(PAINTSTRUCT *ps, HDC *hdc, HDC *hdcMem)
{
	BITMAP blo;
	HBITMAP hblo;
	int k = 0;
	for (int i = 1; i <= game_map.size_row; i++)
	{
		for (int j = 1; j <= game_map.size_col; j++)
		{
			k = game_map.GetBloID(i, j);
			wchar_t str[100];
			str[0] = k + '0';
			str[1] = '\0';
			//MessageBox(NULL, str, str, MB_OK);
			hblo = (HBITMAP)SelectObject(*hdcMem, g_hbmBlo[k]);
			GetObject(g_hbmBlo[k], sizeof(blo), &blo);
			BitBlt(*hdc, 8 + (j - 1) * 25, 40+ (i - 1) * 25, blo.bmWidth, blo.bmHeight, *hdcMem, 0, 0, SRCCOPY);
		}
	}
}

void ButPainting(PAINTSTRUCT* ps, HDC* hdc, HDC* hdcMem, int state)
{
	BITMAP but;
	HBITMAP hbut = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BLOCKS1));
	SelectObject(*hdcMem, hbut);
	GetObject(hbut, sizeof(but), &but);
	BitBlt(*hdc, (10 + (25 * (game_map.size_col + 1))) / 2 - 23, 0, but.bmWidth, but.bmHeight, *hdcMem, 0, 0, SRCCOPY);
	switch (state)
	{
	case 0:
	case 1:
		hbut = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(193));
		SelectObject(*hdcMem, hbut);
		GetObject(hbut, sizeof(but), &but);
		BitBlt(*hdc, (10 + (25 * (game_map.size_col + 1))) / 2 - 21, 2, but.bmWidth, but.bmHeight, *hdcMem, 0, 0, SRCCOPY);
		break;
	case 2:
		hbut = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(194));
		SelectObject(*hdcMem, hbut);
		GetObject(hbut, sizeof(but), &but);
		BitBlt(*hdc, (10 + (25 * (game_map.size_col + 1))) / 2 - 21, 2, but.bmWidth, but.bmHeight, *hdcMem, 0, 0, SRCCOPY);
		break;
	case 3:
		hbut = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(195));
		SelectObject(*hdcMem, hbut);
		GetObject(hbut, sizeof(but), &but);
		BitBlt(*hdc, (10 + (25 * (game_map.size_col + 1))) / 2 - 21, 2, but.bmWidth, but.bmHeight, *hdcMem, 0, 0, SRCCOPY);
		break;
	}
}


void NumPainting(PAINTSTRUCT *ps, HDC *hdc, HDC *hdcMem, int pos,
	int n1, int n2, int n3, int n4, int n5, int n6)
{
	BITMAP num1;
	HBITMAP hbmOld1 = (HBITMAP)SelectObject(*hdcMem, g_hbmNum[n1]);

	pos += 8;

	GetObject(g_hbmNum[n1], sizeof(num1), &num1);
	BitBlt(*hdc, 8, 0, num1.bmWidth, num1.bmHeight, *hdcMem, 0, 0, SRCCOPY);

	hbmOld1 = (HBITMAP)SelectObject(*hdcMem, g_hbmNum[n2]);
	GetObject(g_hbmNum[n2], sizeof(num1), &num1);

	BitBlt(*hdc, 21, 0, num1.bmWidth, num1.bmHeight, *hdcMem, 0, 0, SRCCOPY);

	
	
	hbmOld1 = (HBITMAP)SelectObject(*hdcMem, g_hbmNum[n3]);
	GetObject(g_hbmNum[n3], sizeof(num1), &num1);

	BitBlt(*hdc, 34, 0, num1.bmWidth, num1.bmHeight, *hdcMem, 0, 0, SRCCOPY);

	hbmOld1 = (HBITMAP)SelectObject(*hdcMem, g_hbmNum[n4]);
	GetObject(g_hbmNum[n4], sizeof(num1), &num1);

	BitBlt(*hdc, pos, 0, num1.bmWidth, num1.bmHeight, *hdcMem, 0, 0, SRCCOPY);

	hbmOld1 = (HBITMAP)SelectObject(*hdcMem, g_hbmNum[n5]);

	GetObject(g_hbmNum[n5], sizeof(num1), &num1);
	BitBlt(*hdc, pos + 13, 0, num1.bmWidth, num1.bmHeight, *hdcMem, 0, 0, SRCCOPY);

	hbmOld1 = (HBITMAP)SelectObject(*hdcMem, g_hbmNum[n6]);
	GetObject(g_hbmNum[n6], sizeof(num1), &num1);

	BitBlt(*hdc, pos + 26, 0, num1.bmWidth, num1.bmHeight, *hdcMem, 0, 0, SRCCOPY);
	
	//DeleteObject(hdcMem);
}

void ReSizeGameWnd(HWND hwnd)
{
	RECT rectWindow;

	GetWindowRect(hwnd, &rectWindow);
	MoveWindow(hwnd,
		rectWindow.left,
		rectWindow.top,
		10 + (25 * (game_map.size_col + 1)),
		10 + (25 * (game_map.size_row + 1)) + 74,
		TRUE);
}

void InitNUMPADs()
{
	g_hbmNum[0] = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(164));
	for (int i = 1; i <= 9; i++)
		g_hbmNum[i] = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE((int)(155 + i) - 1));
}

void InitBLOCKs()
{
	game_map.game_state = 0;
	game_map.InitBox(10, 10);
	for (int i = 1; i <= 13; i++)
		g_hbmBlo[i] = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE((int)(173 + i) - 1));
}

void GameOver(bool winorlose) {
	if (winorlose)
	{
		game_map.game_state = 2;
		BOOL Result = DeleteTimerQueueTimer(hHandle, TimerID_1s, NULL);
		if (Result) {
			;
		}

	}
	else
	{
		game_map.game_state = 3;
		BOOL Result = DeleteTimerQueueTimer(hHandle, TimerID_1s, NULL);
		if (Result) {
			;
		}
		for (int i = 1; i <= game_map.size_row; i++)
		{
			for (int j = 1; j <= game_map.size_col; j++)
			{
				if (game_map._Block[i][j] == -1)
				{
					game_map._vis[i][j] = true;
				}
			}
		}
	}
}

void GetNums() {
	int num1 = game_map.Bombnum();
	int num2 = game_map.time_now;
	for (int i = 1; i <= 3; i++) {
		allNums[4 - i] = num1 % 10;
		allNums[7 - i] = num2 % 10;
		num1 /= 10, num2 /= 10;
	}
}

VOID CALLBACK TimerRoutine(PVOID lpParam, BOOLEAN TimerOrWaitFired) {
	game_map.time_now++;
	GetNums();
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint((HWND)lpParam, &ps);
	HDC hdcMem = CreateCompatibleDC(hdc);
	RECT numClient;
	NumPainting(&ps, &hdc, &hdcMem, ((game_map.size_col) * 25) - 39, allNums[1], allNums[2], allNums[3], allNums[4], allNums[5], allNums[6]);
	GetClientRect((HWND)lpParam, &numClient);
	SetRect(&numClient, numClient.left, numClient.top, numClient.right, 25);
	InvalidateRect((HWND)lpParam, &numClient, FALSE);
	DeleteDC(hdc);
	DeleteDC(hdcMem);
	EndPaint((HWND)lpParam, &ps);
	ReleaseDC((HWND)lpParam, hdc);
}

void GameStart(HWND hwnd)
{
	game_map.game_state = 1;
	game_map.time_now = 0;
	CreateTimerQueueTimer(&TimerID_1s, hHandle, TimerRoutine, hwnd, 1, 1000, WT_EXECUTEDEFAULT);
}

void Lclick(int x, int y, HWND hwnd)
{
	if (x > 40)
	{
		if (game_map.game_state != 1 && game_map.game_state != 0)
		{
			return;
		}
		x -= 8;
		y -= 8;
		x /= 25;
		y /= 25;
		y++;
		if (game_map.game_state == 0)
		{
			GameStart(hwnd);
			game_map.RandomSetMines(x, y, 10);
		}
		if (game_map._vis[x][y] == false)
		{
			if (game_map._flag[x][y] == true)
			{
				return;
			}
			else if (game_map._Block[x][y] == -1)
			{
				game_map._vis[x][y] = true;
				game_map._Block[x][y] = -3;
				GameOver(false);
			}
			else
			{
				game_map._Block[x][y] = game_map.ComputNums(x, y);
				if (game_map._Block[x][y] == 0)
				{
					game_map.SearchAD(x, y);
				}
				game_map._vis[x][y] = true;
			}
		}
		if (game_map.JudgeisWin() == true) {
			GameOver(true);
		}
	}
	else
	{
		if (y > (10 + (25 * (game_map.size_col + 1))) / 2 - 23 && y < (10 + (25 * (game_map.size_col + 1))) / 2 + 22)
		{
			if (TimerID_1s != NULL)
			{
				if (game_map.game_state == 1)
				{
					BOOL Result = DeleteTimerQueueTimer(hHandle, TimerID_1s, NULL);
					if (Result) {
						;
					}
				}
			}
			game_map.time_now = 0;
			GetNums();
			game_map.game_state = 0;
			game_map.InitBox(10, 10);

		}
	}
}

void Rclick(int x, int y, HWND hwnd)
{
	if (x > 40)
	{
		x -= 8;
		y -= 8;
		x /= 25;
		y /= 25;
		y++;
		if (game_map._vis[x][y] == false)
		{
			if (game_map._flag[x][y])
				game_map._flag[x][y] = false;
			else
			{
				if (game_map.Flagnum() < game_map.tot_bomb)
					game_map._flag[x][y] = true;
			}
		}
		if (game_map.JudgeisWin() == true) {
			GameOver(true);
		}
	}
}
