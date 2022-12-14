#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

typedef struct _blocks
{
	int _Block[100][100];
	bool _vis[100][100];
	bool _flag[100][100];
	int game_state;
	int size_col, size_row;
	int time_now;
	int tot_bomb;
	void InitBox(int x, int y);
	void RandomSetMines(int x, int y, int tot);
	void SearchAD(int x, int y);
	int GetBloID(int x, int y);
	int ComputNums(int x, int y);
	int ComputFlag(int x, int y);
	int Flagnum();
	int Bombnum();
	bool JudgeisWin();
}_Blocks, *_pBlocks;

typedef struct ranker
{
	int usrtime;
	wchar_t usrname[20];
	bool operator<(const ranker& y)const
	{
		return this->usrtime < y.usrtime;
	}
	bool operator>(const ranker& y)const
	{
		return this->usrtime > y.usrtime;
	}
}_Ranker, *_pRanker;