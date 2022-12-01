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
_Blocks game_map;
std::vector <_Ranker> __Easy, __Normal, __Hard;
int allNums[7];
int __ROW__ = 10, __COL__ = 10, __MINE__ = 10;
//int step[8][2] = { {1, 1}, {1, -1}, {-1, 1},
//	{1, 0}, {0, 1}, {0, -1}, {-1, 0}, {-1, -1} };
void MapPainting(HWND hwnd)
{
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(hwnd, &ps);
	HDC hdcMem = CreateCompatibleDC(hdc);
	GetNums();
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

void InttoStr(int x, wchar_t* str)
{
	int i = 0;
	while (x)
	{
		str[i] = (x % 10) + '0';
		x /= 10;
		i++;
	}
	for (int j = 0; j < i / 2; j++)
	{
		wchar_t t = str[j];
		str[j] = str[i - j - 1];
		str[i - j - 1] = t;
	}
}

void StrtoInt(int* x, wchar_t* str)
{
	int len = 0;
	*x = 0;
	while (str[len++] != 0);
	for (int i = 0; i < len - 1; i++) {
		*x *= 10;
		*x += str[i] - '0';
	}
}

int GetMode()
{
	if (__MINE__ == 10 && __COL__ == 10 && __ROW__ == 10)
	{
		return 1;
	}
	else if (__MINE__ == 40 && __COL__ == 16 && __ROW__ == 16)
	{
		return 2;
	}
	else if (__MINE__ == 99 && __COL__ == 30 && __ROW__ == 16)
	{
		return 3;
	}
	return 0;
}

void AddnewScore(int utime, wchar_t* uname)
{
	_Ranker tmp = { utime, {0} };
	switch (GetMode())
	{
	case 1:
		memcpy(tmp.usrname, uname, sizeof(char) * 20);
		__Easy.push_back(tmp);
		std::sort(__Easy.begin(), __Easy.end());
		break;
	case 2:
		memcpy(tmp.usrname, uname, sizeof(char) * 20);
		__Normal.push_back(tmp);
		std::sort(__Normal.begin(), __Normal.end());
		break;
	case 3:
		memcpy(tmp.usrname, uname, sizeof(char) * 20);
		__Hard.push_back(tmp);
		std::sort(__Hard.begin(), __Hard.end());
		break;
	}
}

bool IfnewFirst(int utime)
{
	if (__MINE__ == 10 && __COL__ == 10 && __ROW__ == 10)
	{
		if (__Easy.empty() || __Easy.size() < 3)
			return true;
		else if (utime <= __Easy[2].usrtime)
			return true;
	}
	if (__MINE__ == 40 && __COL__ == 16 && __ROW__ == 16)
	{
		if (__Normal.empty() || __Normal.size() < 3)
			return true;
		else if (utime <= __Normal[2].usrtime)
			return true;
	}
	if (__MINE__ == 99 && __COL__ == 30 && __ROW__ == 16)
	{
		if (__Hard.empty() || __Hard.size() < 3)
			return true;
		else if (utime <= __Hard[2].usrtime)
			return true;
	}
	return false;
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
	game_map.InitBox(__ROW__, __COL__);
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
		for (int i = 1; i <= game_map.size_row; i++)
		{
			for (int j = 1; j <= game_map.size_col; j++)
			{
				if (game_map._Block[i][j] != -1 && game_map._vis[i][j] != true)
				{
					game_map._Block[i][j] = game_map.ComputNums(i, j);
					game_map._vis[i][j] = true;
				}
			}
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

void GameRestart()
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
	game_map.InitBox(__ROW__, __COL__);
	return;
}

void JudgeNum(int* x, int choose)
{
	switch (choose)
	{
	case 1:
		*x = *x < 1 ? 1 : *x;
		*x = *x > 34 ? 34 : *x;
		break;
	case 2:
		*x = *x < 4 ? 4 : *x;
		*x = *x > 60 ? 60 : *x;
		break;
	case 3:
		*x = *x < 1 ? 1 : *x;
		*x = *x > ((__ROW__ * __COL__) - 1) ? ((__ROW__ * __COL__) - 1) : *x;
		break;
	}
}

void GetNums()
{
	int num1 = game_map.Bombnum();
	int num2 = game_map.time_now;
	for (int i = 1; i <= 3; i++) {
		allNums[4 - i] = num1 % 10;
		allNums[7 - i] = num2 % 10;
		num1 /= 10, num2 /= 10;
	}
}

void SetGame(int row, int col, int mine)
{
	__ROW__ = row;
	__COL__ = col;
	__MINE__ = mine;
	return;
}

int GetGame(int choose)
{
	switch (choose)
	{
	case 1:
		return __ROW__;
		break;
	case 2:
		return __COL__;
		break;
	case 3:
		return __MINE__;
		break;
	case 4:
		return game_map.game_state;
		break;
	case 5:
		return game_map.time_now;
		break;
	}
	return 0;
}

_Ranker GetRanker(int opt, int rank)
{
	switch (opt) {
	case 1:
		if (__Easy.size() < rank)
		{
			return { -1, {0} };
		}
		return __Easy[static_cast<std::vector<_Ranker, std::allocator<_Ranker>>::size_type>(rank) - 1];
		break;
	case 2:
		if (__Normal.size() < rank)
		{
			return { -1, {0} };
		}
		return __Normal[static_cast<std::vector<_Ranker, std::allocator<_Ranker>>::size_type>(rank) - 1];
		break;
	case 3:
		if (__Hard.size() < rank)
		{
			return { -1, {0} };
		}
		return __Hard[static_cast<std::vector<_Ranker, std::allocator<_Ranker>>::size_type>(rank) - 1];
		break;
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
			game_map.RandomSetMines(x, y, __MINE__);
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
		if (game_map.JudgeisWin() == true) 
		{
			for (int i = 1; i <= game_map.size_row; i++)
			{
				for (int j = 1; j <= game_map.size_col; j++)
				{
					if (game_map._Block[i][j] == -1)
						game_map._flag[i][j] = true;
				}
			}
			GameOver(true);
		}
	}
	else
	{
		if (y > (10 + (25 * (game_map.size_col + 1))) / 2 - 23 && y < (10 + (25 * (game_map.size_col + 1))) / 2 + 22)
		{
			GameRestart();
		}
	}
}

void Rclick(int x, int y, HWND hwnd)
{
	if (game_map.game_state == 0)
		return;
	int step[8][2] = { {1, 1}, {1, -1}, {-1, 1},
		{1, 0}, {0, 1}, {0, -1}, {-1, 0}, {-1, -1} };
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
		else if (game_map._vis[x][y] == true)
		{
			if (game_map.ComputNums(x, y) <= game_map.ComputFlag(x, y)) 
			{
				for (int i = 0; i < 8; i++)
				{
					Lclick((x + step[i][0]) * 25 + 20, (y + step[i][1] - 1) * 25 + 8, hwnd);
					if (game_map.game_state != 1)
						return;
				}
			}
			else
			{
				;
			}
		}
		if (game_map.JudgeisWin() == true) {
			GameOver(true);
		}
	}
}
