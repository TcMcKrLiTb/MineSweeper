#pragma once

#include "framework.h"
#include "MineSweeper.h"

void MapPainting(HWND hwnd);
void InitNUMPADs();
void InitBLOCKs();
void Lclick(int x, int y, HWND hwnd);
void Rclick(int x, int y, HWND hwnd);
void GetNums();
void SetGame(int row, int col, int mine);
void GameOver(bool winorlose);
void GameRestart();
void JudgeNum(int* x, int choose);
void GameStart(HWND hwnd);
void ReSizeGameWnd(HWND hwnd);
void InttoStr(int x, wchar_t* str);
void StrtoInt(int* x, wchar_t* str);
int GetGame(int choose);