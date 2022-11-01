#pragma once

#include "framework.h"
#include "MineSweeper.h"

void MapPainting(HWND hwnd);
void InitNUMPADs();
void InitBLOCKs();
void Lclick(int x, int y, HWND hwnd);
void Rclick(int x, int y, HWND hwnd);
void GetNums();
void GameOver(bool winorlose);
void GameStart(HWND hwnd);
void ReSizeGameWnd(HWND hwnd);
void ReSizeFameWnd(HWND hwnd);
