#include "Themap.h"
int step[8][2] = { {1, 1}, {1, -1}, {-1, 1},
	{1, 0}, {0, 1}, {0, -1}, {-1, 0}, {-1, -1} };

bool _blocks::JudgeisWin()
{
	int cnt1 = 0, cnt2 = 0, flag = 1;
	for (int i = 1; i <= size_row; i++)
	{
		for (int j = 1; j <= size_col; j++)
		{
			if (_vis[i][j] == true)
			{
				cnt1++;
			}
			else if (_flag[i][j] == true)
			{
				cnt2++;
			}
			if (_Block[i][j] == -1 && _flag[i][j] == false)
			{
				flag = false;
			}
		}
	}
	if ((cnt1 + cnt2) == (size_col * size_row) || 
		(size_row * size_col - cnt1) == tot_bomb ||
		flag == true)
	{
		return true;
	}
	return false;
}

void _blocks::InitBox(int x, int y)
{
	tot_bomb = 0;
	size_row = x;
	size_col = y;
	tot_bomb = 0;
	for (int i = 1; i <= size_row; i++)
	{
		for (int j = 1; j <= size_col; j++)
		{
			_Block[i][j] = 0;
			_vis[i][j] = false;
			_flag[i][j] = false;
		}
	}
}

void _blocks::RandomSetMines(int x, int y, int tot)
{
	srand((unsigned)time(NULL));
	int _size = size_row * size_col;
	if (tot <= (_size * 6) / 10)
	{
		for (int i = 1; i <= tot; )
		{
			int a = rand() % size_row + 1;
			int b = rand() % size_col + 1;
			if (_Block[a][b] == 0 && a != x && b != y)
			{
				_Block[a][b] = -1;
				i++;
			}
		}
	}
	else
	{
		for (int i = 1; i <= size_row; i++)
		{
			for (int j = 1; j <= size_col; j++)
			{
				if (i != x || j != y)
					_Block[i][j] = -1;
			}
		}
		for (int i = 1; i <= _size - tot - 1; )
		{
			int a = rand() % size_row + 1;
			int b = rand() % size_col + 1;
			if (_Block[a][b] == -1)
			{
				_Block[a][b] = 0;
				i++;
			}
		}
	}
	tot_bomb = tot;
}

void _blocks::SearchAD(int x, int y)
{
	if (x > size_row || x < 1 || y > size_col || y < 1)
		return;
	if (ComputNums(x, y) != 0 || _vis[x][y] == true)
	{
		if (_Block[x][y] != -1 && _Block[x][y] != -2 && _Block[x][y] != -3) 
		{
			_vis[x][y] = true;
			_Block[x][y] = ComputNums(x, y);
		}
		return;
	}
	_vis[x][y] = true;
	for (int i = 0; i < 8; i++)
	{
		SearchAD(x + step[i][0], y + step[i][1]);
	}
}

int _blocks::GetBloID(int x, int y)
{
	int k = 0;
	if (_vis[x][y] == true)
	{
		switch (_Block[x][y])
		{
		case -1:
			k = 11;
			break;
		case 0:
			k = 10;
			break;
		case -3:
			k = 12;
			break;
		default:
			k = _Block[x][y];
			break;
		}
	}
	else if (_vis[x][y] == false)
	{
		if (_flag[x][y])
			k = 13;
		else 
		{
			switch (_Block[x][y])
			{
			case -1:
			case 0:
				k = 9;
				break;
			}
		}
	}
	return k;
}

int _blocks::ComputNums(int x, int y)
{
	int ans = 0;
	for (int i = 0; i < 8; i++) 
	{
		ans += (_Block[x + step[i][0]][y + step[i][1]] == -1);
	}
	return ans;
}

int _blocks::ComputFlag(int x, int y)
{
	int ans = 0;
	for (int i = 0; i < 8; i++)
	{
		ans += (_flag[x + step[i][0]][y + step[i][1]] == true);
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
			if (_flag[i][j] == true)
				ans++;
		}
	}
	return ans;
}

int _blocks::Bombnum()
{
	return tot_bomb - Flagnum();
}