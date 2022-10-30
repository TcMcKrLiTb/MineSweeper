#include "Gaming.h"
#include "Themap.h"
#include <windows.h>

void NumPainting(PAINTSTRUCT *ps, HDC *hdc, HDC *hdcMem, int pos,
	int n1, int n2, int n3, int n4, int n5, int n6);
void BloPainting(PAINTSTRUCT ps, HDC hdc, HDC hdcMem);

HBITMAP g_hbmNum[10] = { NULL };
HBITMAP g_hbmBlo[14] = { NULL };
int allNums[7];
_Blocks game_map;
void MapPainting(HWND hwnd)
{
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(hwnd, &ps);
	HDC hdcMem = CreateCompatibleDC(hdc);
	NumPainting(&ps, &hdc, &hdcMem, ((game_map.size_col) * 25) - 39, allNums[1], allNums[2], allNums[3], allNums[4], allNums[5], allNums[6]);
	//Sleep(1000);
	BloPainting(ps, hdc, hdcMem);

	DeleteDC(hdc);
	DeleteDC(hdcMem);
	EndPaint(hwnd, &ps);
	ReleaseDC(hwnd, hdc);
}

void BloPainting(PAINTSTRUCT ps, HDC hdc, HDC hdcMem)
{
	for (int i = 1; i <= game_map.size_row; i++)
	{
		for (int j = 1; j <= game_map.size_col; j++)
		{
			int k = 0;
			if (game_map._vis[i][j] == true)
			{
				switch (game_map._Block[i][j])
				{
				case -1:
					k = 11;
					break;
				case 0:
					k = 10;
					break;
				case 1:
					k = 1;
					break;
				case 2:
					k = 2;
					break;
				case 3:
					k = 3;
					break;
				case 4:
					k = 4;
					break;
				case 5:
					k = 5;
					break;
				case 6:
					k = 6;
					break;
				case 7:
					k = 7;
					break;
				case 8:
					k = 8;
					break;
				}
			}
			else {
				switch (game_map._Block[i][j])
				{
				case 0:
					k = 9;
					break;
				}
			}
			BITMAP blo;
			HBITMAP hblo = (HBITMAP)SelectObject(hdcMem, g_hbmBlo[k]);

			GetObject(g_hbmBlo[k], sizeof(blo), &blo);
			BitBlt(hdc, 8 + (i - 1) * 25, 40+ (j - 1) * 25, blo.bmWidth, blo.bmHeight, hdcMem, 0, 0, SRCCOPY);

		}
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
		g_hbmNum[i] = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(155 + i - 1));
}

void InitBLOCKs()
{
	game_map.InitBox(10, 10);
	for (int i = 1; i <= 12; i++)
		g_hbmBlo[i] = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(173 + i - 1));
}

void GameOver(bool winorlose) {
	;
}

void Lclick(int x, int y)
{
	int t = x;
	x = y;
	y = t;
	if (game_map.tot_bomb == 0)
	{
		game_map.RandomSetMines(x, y, 10);
		game_map.tot_bomb = 10;
	}
	if (game_map._vis[x][y] == false)
	{
		game_map._vis[x][y] = true;
		if (game_map._Block[x][y] == -1)
		{
			GameOver(false);
		}
		else 
		{
			game_map._Block[x][y] = game_map.ComputNums(x, y);
			if (game_map._Block[x][y] == 0)
			{
				game_map.SearchAD(x, y);
			}
		}
	}
	//for (int i = 1; i <= game_map.size_row; i++)
		//for (int j = 1; j <= game_map.size_col; j++)
	//game_map._vis[y][x] = 1, game_map._Block[y][x] = 1;
}

void Rclick(int x, int y)
{
	int t = x;
	x = y;
	y = t;
	if (game_map._vis[x][y] == false)
	{
		game_map._Block[x][y] = -2;
	}
}
