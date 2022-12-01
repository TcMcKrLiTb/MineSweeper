#pragma once

#include "Themap.h"
#include "framework.h"
#include "MineSweeper.h"
#include <algorithm>
#include <vector>
#include <queue>
#include <stack>

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
void AddnewScore(int utime, wchar_t* uname);
bool IfnewFirst(int utime);
int GetGame(int choose);
_Ranker GetRanker(int opt, int rank);