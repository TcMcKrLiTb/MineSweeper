#pragma once

#include "framework.h"
#include "MineSweeper.h"

void MapPainting(HWND hwnd);
void InitNUMPADs();
void InitBLOCKs();
void Lclick(int x, int y);
void Rclick(int x, int y);
void GameOver(bool winorlose);
void ReSizeGameWnd(HWND hwnd);
void ReSizeFameWnd(HWND hwnd);
