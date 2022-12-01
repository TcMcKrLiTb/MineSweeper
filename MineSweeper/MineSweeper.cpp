// 
// Design by TcMcKrLiTb
//

#include "framework.h"
#include "MineSweeper.h"
#include "Gaming.h"
#include "Themap.h"

#define MAX_LOADSTRING 100

HINSTANCE hInst;
WCHAR szTitle[MAX_LOADSTRING];
WCHAR szWindowClass[MAX_LOADSTRING];

ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    Setting(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	Rankboard(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	Congratulat(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
					 _In_opt_ HINSTANCE hPrevInstance,
					 _In_ LPWSTR    lpCmdLine,
					 _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_MINESWEEPER, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MINESWEEPER));

	MSG msg;

	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}


ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style          = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc    = WndProc;
	wcex.cbClsExtra     = 0;
	wcex.cbWndExtra     = 0;
	wcex.hInstance      = hInstance;
	wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MINESWEEPER));
	wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+6);
	wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_MINESWEEPER);
	wcex.lpszClassName  = szWindowClass;
	wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance;
   HMENU hmenu = LoadMenu(hInstance, MAKEINTRESOURCE(IDC_MINESWEEPER));

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME,
	  240, 100, 240, 500, nullptr, hmenu, hInstance, nullptr);

   if (!hWnd)
   {
	  return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HMENU hmenu = GetMenu(hWnd);
	switch (message)
	{
	case WM_CREATE:
		InitNUMPADs();
		InitBLOCKs();
		break;
	case WM_COMMAND:
		{
			int wmId = LOWORD(wParam);
			switch (wmId)
			{
			case IDM_ABOUT:
				DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
				break;
			case IDM_EXIT:
				DestroyWindow(hWnd);
				break;
			case IDM_NEWGAME:
				GameRestart();
				InvalidateRect(hWnd, NULL, TRUE);
				break;
			case IDM_RANKS:
				DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG2), hWnd, Rankboard);
				break;
			case IDM_BEGINNER:
				SetGame(10, 10, 10);
				GameRestart();
				//if (CheckMenuItem(hmenu, IDM_BEGINNER, MF_CHECKED | MF_BYPOSITION))
					//MessageBox(hWnd, _T("123"), _T("123"), MB_OK);
				//SetMenuItemInfoA(GetMenu(hWnd), IDM_BEGINNER, TRUE, MF_CHECKED);
				InvalidateRect(hWnd, NULL, TRUE);
				DrawMenuBar(hWnd);
				break;
			case IDM_MEDIATE:
				SetGame(16, 16, 40);
				GameRestart();
				InvalidateRect(hWnd, NULL, TRUE);
				EnableMenuItem(hmenu, IDM_MEDIATE, MF_DISABLED | MF_BYPOSITION);
				DrawMenuBar(hWnd);
				break;
			case IDM_EXPERT:
				SetGame(16, 30, 99);
				GameRestart();
				InvalidateRect(hWnd, NULL, TRUE);
				DrawMenuBar(hWnd);
				break;
			case IDM_CUSTOM:
				DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, Setting);
				GameRestart();
				InvalidateRect(hWnd, NULL, TRUE);
				EnableMenuItem(hmenu, IDM_MEDIATE, MF_DISABLED | MF_BYPOSITION);
				DrawMenuBar(hWnd);
				break;
			default:
				return DefWindowProc(hWnd, message, wParam, lParam);
			}
		}
		break;
	case WM_LBUTTONDOWN:
		{
			int x = 0, y = 0;
			if (wParam && MK_LBUTTON)
			{
				y = GET_X_LPARAM(lParam);
				x = GET_Y_LPARAM(lParam);
			}
			Lclick(x, y, hWnd);
			InvalidateRect(hWnd, NULL, TRUE);
			if (GetGame(4) == 2)
			{
				if (IfnewFirst(GetGame(5)))
				{
					DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG3), hWnd, Congratulat);
				}
			}
		}
		break;
	case WM_RBUTTONDOWN:
		{
			int x = 0, y = 0;
			if (wParam && MK_LBUTTON)
			{
				y = LOWORD(lParam);
				x = HIWORD(lParam);
			}
			Rclick(x, y, hWnd);
			MapPainting(hWnd);
			InvalidateRect(hWnd, NULL, TRUE); 
			if (GetGame(4) == 2)
			{
				if (IfnewFirst(GetGame(5)))
				{
					DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG3), hWnd, Congratulat);
				}
			}
		}
		break;
	case WM_PAINT:
		{
			ReSizeGameWnd(hWnd);
			MapPainting(hWnd);
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		if (LOWORD(wParam) == IDC_BUTTON1) {
			system("start https://github.com/TcMcKrLiTb/MineSweeper");
		}
		break;
	}
	return (INT_PTR)FALSE;
}

INT_PTR CALLBACK Congratulat(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) 
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		else if (LOWORD(wParam) == IDOK)
		{
			wchar_t* stri;
			stri = (wchar_t*)malloc(sizeof(wchar_t) * 20);
			if (stri != NULL)
				GetDlgItemTextW(hDlg, IDC_EDIT2, stri, 10);
			AddnewScore(GetGame(5), stri);
			EndDialog(hDlg, LOWORD(wParam));
		}
		break;
	}
	return (INT_PTR)FALSE;
}

INT_PTR CALLBACK Rankboard(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) 
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
	{
		_Ranker tmp = { 0, {0} };
		wchar_t* stri;
		stri = (wchar_t*)malloc(sizeof(wchar_t) * 5);
		if (stri != NULL)
			memset(stri, 0, sizeof(stri));
		for (int i = 1; i <= 3; i++)
		{
			for (int j = 1; j <= 3; j++)
			{
				tmp = GetRanker(i, j);
				if (tmp.usrtime != -1)
				{
					SetDlgItemTextW(hDlg, 1008 + (i - 1) * 6 + j, tmp.usrname);
					InttoStr(tmp.usrtime, stri);
					if (stri != NULL)
						SetDlgItemTextW(hDlg, 1008 + (i - 1) * 6 + j + 3, stri);
				}
			}
		}
		free(stri);
	}
		break;
	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

INT_PTR CALLBACK Setting(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) 
{

	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		wchar_t* stri;
		stri = (wchar_t*)malloc(sizeof(wchar_t) * 10);
		InttoStr(GetGame(1), stri);

		if (stri != NULL)
			memset(stri, 0, sizeof(stri));
		InttoStr(GetGame(1), stri);
		if (stri != NULL)
			SetDlgItemTextW(hDlg, IDC_EDIT1, stri);

		if (stri != NULL)
			memset(stri, 0, sizeof(stri));
		InttoStr(GetGame(2), stri);
		if (stri != NULL)
			SetDlgItemTextW(hDlg, IDC_EDIT2, stri);

		if (stri != NULL)
			memset(stri, 0, sizeof(stri));
		InttoStr(GetGame(3), stri);
		if (stri != NULL)
			SetDlgItemTextW(hDlg, IDC_EDIT3, stri);

		free(stri);
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		if (LOWORD(wParam) == IDOK) {

			wchar_t* stri;
			int x = 0;
			stri = (wchar_t*)malloc(sizeof(wchar_t) * 10);
			if (stri != NULL)
				GetDlgItemTextW(hDlg, IDC_EDIT1, stri, 10);
			StrtoInt(&x, stri);
			JudgeNum(&x, 1);
			SetGame(x, GetGame(2), GetGame(3));

			if (stri != NULL)
				GetDlgItemTextW(hDlg, IDC_EDIT2, stri, 10);
			StrtoInt(&x, stri);
			JudgeNum(&x, 2);
			SetGame(GetGame(1), x, GetGame(3));

			if (stri != NULL)
				GetDlgItemTextW(hDlg, IDC_EDIT3, stri, 10);
			StrtoInt(&x, stri);
			JudgeNum(&x, 3);
			SetGame(GetGame(1), GetGame(2), x);

			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}