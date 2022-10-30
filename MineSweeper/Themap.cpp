#include "Themap.h"


void _blocks::InitBox(int x, int y)
{
	size_row = x;
	size_col = y;
	tot_bomb = 0;
	for (int i = 1; i <= size_row; i++)
	{
		for (int j = 1; j <= size_col; j++)
		{
			_Block[i][j] = 0;
			_vis[i][j] = false;
		}
	}
}

void _blocks::RandomSetMines(int x, int y, int tot)
{
	int a, b;
	srand((unsigned)time(NULL));
	for (int i = 1; i <= tot; )
	{
		a = rand() % size_row + 1;
		b = rand() % size_col + 1;
		if (_Block[a][b] == 0 && a != x && b != y) 
		{
			_Block[a][b] = -1;
			i++;
		}
	}
}

void _blocks::SearchAD(int x, int y)
{
	;
}

int _blocks::ComputNums(int x, int y)
{
	int ans = 0;
	int step[8][2] = { {1, 1}, {1, -1}, {-1, 1},
	{1, 0}, {0, 1}, {0, -1}, {-1, 0}, {-1, -1} };
	for (int i = 0; i < 8; i++) 
	{
		ans += (_Block[x + step[i][0]][y + step[i][1]] == -1);
	}
	return ans;
}

int _blocks::Flagnum()
{
	int ans = 0;
	for (int i = 1; i <= size_row; i++)
	{
		for (int j = 1; j <= size_col; j++)
		{
			if (_Block[i][j] == -2)
				ans++;
		}
	}
	return ans;
}

int _blocks::Bombnum()
{
	return tot_bomb - Flagnum();
}