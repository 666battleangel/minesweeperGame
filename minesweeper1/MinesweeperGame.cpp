#include "pch.h"
#include "MinesweeperGame.h"

MinesweeperGame::openResult MinesweeperGame::openCell(int x, int y)
{
	if (gameLost || gameWon)
	{
		return openResult::NoChange;
	}
	Cell& cell = map[x][y];
	if (cell.isFlagged || cell.isOpened)
	{
		return openResult::NoChange;
	}
	if (!firstMoveDone)
	{
		firstMoveDone = true;
		placeMines(x, y);
	}
	cell.isOpened = true;
	if (cell.minesAround = 0)
	{
		openEmptyCells(x, y);
	}
	if (cell.isMine)
	{
		gameLost = true;
		return openResult::Lost;
	}
	if (isGameWon())
	{
		gameWon = true;
		return openResult::Won;
	}
	return openResult::Opened;
};

bool MinesweeperGame::validInput(int w, int h, int mines)
{
	if (w < 0 || h < 0)
	{
		return false;
	}

	if (mines > (h * w) - 1 || mines <= 0)
	{
		return false;
	}
	return true;
};

bool MinesweeperGame::isGameLost()const
{
	return gameLost;
}

bool MinesweeperGame::isGameWon()const
{
	for (int x = 0; x < max_x; x++)
	{
		for (int y = 0; y < max_y; y++)
		{
			const Cell& cell = map[x][y];
			if (!cell.isMine && !cell.isOpened)
			{
				return false;
			}
		}
	}
	if (flagCount == 0) { return true; } 
	else { return false; }
};

bool MinesweeperGame::createNewGame(int w, int h, int mines)
{
	if (!validInput(w, h, mines))
	{
		return false;
	}

	max_x = w;
	max_y = h; 
	mineAmount = mines;
	flagCount = mines; 
	firstMoveDone = false;
	gameWon = false;
	gameLost = false;

	map.clear(); 

	for (int i = 0; i < max_y; i++)
	{
		std::vector<Cell> innerVector;
		for (int j = 0; j < max_x; j++)
		{
			Cell cell = Cell(j, i);
			innerVector.push_back(cell);
		}
		map.push_back(innerVector);
	}

	return true; 
};

int MinesweeperGame::getMax_x()const
{
	return max_x;
};

int MinesweeperGame::getMax_y()const
{
	return max_y;
};

int MinesweeperGame::getMineAmount()const
{
	return mineAmount;
};

int MinesweeperGame::getFlagCount()const
{
	return flagCount; 
};

const Cell& MinesweeperGame::getCell(int x, int y)const
{
	return map[x][y];
};


void MinesweeperGame::placeMines(int safeX, int safeY)
{
	int minesOnMap = 0;
	while (minesOnMap < mineAmount)
	{
		int mine_y = rand() % max_y;
		int mine_x = rand() % max_x;

		if (mine_x == safeX && mine_y == safeY)
		{
			continue;
		}
		if (!map[mine_x][mine_y].isMine)
		{
			map[mine_x][mine_y].isMine = true;
			minesOnMap++;
		}
	}
	countMinesAround();
};

void MinesweeperGame::countMinesAround()
{
	for (int i = 0; i < max_y; i++)
	{
		for (int j = 0; j < max_x; j++)
		{
			if (map[j][i].isMine == true)
			{
				if (j - 1 != -1)
				{
					if (i - 1 != -1)
					{
						map[j - 1][i - 1].minesAround++;
					}
					map[j - 1][i].minesAround++;
					if (i + 1 < max_y)
					{
						map[j - 1][i + 1].minesAround++;
					}
				}
				if (j + 1 < max_x)
				{
					if (i - 1 != -1)
					{
						map[j + 1][i - 1].minesAround++;

					}
					map[j + 1][i].minesAround++;
					if (i + 1 < max_y)
					{
						map[j + 1][i + 1].minesAround++;
					}
				}
				if (i - 1 != -1)
				{
					map[j][i - 1].minesAround++;
				}
				if (i + 1 < max_y)
				{
					map[j][i + 1].minesAround++;
				}
			}
		}
	}
};

void MinesweeperGame::openEmptyCells(int x, int y)
{
	if (map[x][y].minesAround == 0)
	{
		if (x - 1 != -1)
		{
			if (y - 1 != -1)
			{
				if (!map[x - 1][y - 1].isOpened)
				{
					map[x - 1][y - 1].isOpened = true;
					if (map[x - 1][y - 1].minesAround == 0)
					{
						openEmptyCells(x - 1, y - 1);
					}

				}
				if (!map[x - 1][y].isOpened)
				{
					map[x - 1][y].isOpened = true;
					if (map[x - 1][y].minesAround == 0)
					{
						openEmptyCells(x - 1, y);
					}
				}
				if (y + 1 < max_y)
				{
					if (!map[x - 1][y + 1].isOpened)
					{
						map[x - 1][y + 1].isOpened = true;
						if (map[x - 1][y + 1].minesAround == 0)
						{
							openEmptyCells(x - 1, y + 1);
						}
					}
				}
			}
			if (x + 1 < max_x)
			{
				if (y - 1 != -1)
				{
					if (!map[x + 1][y - 1].isOpened)
					{
						map[x + 1][y - 1].isOpened = true;
						if (map[x + 1][y - 1].minesAround == 0)
						{
							openEmptyCells(x + 1, y - 1);
						}
					}

				}
				if (!map[x + 1][y].isOpened)
				{
					map[x + 1][y].isOpened = true;
					if (map[x + 1][y].minesAround == 0)
					{
						openEmptyCells(x + 1, y);
					}
				}
				if (y + 1 < max_y)
				{
					if (!map[x + 1][y + 1].isOpened)
					{
						map[x + 1][y + 1].isOpened = true;
						if (map[x + 1][y + 1].minesAround == 0)
						{
							openEmptyCells(x + 1, y + 1);
						}
					}
				}
			}
			if (y - 1 != -1)
			{
				if (!map[x][y - 1].isOpened)
				{
					map[x][y - 1].isOpened = true;
					if (map[x][y - 1].minesAround == 0)
					{
						openEmptyCells(x, y - 1);
					}
				}
			}
			if (y + 1 < max_y)
			{
				if (!map[x][y + 1].isOpened)
				{
					map[x][y + 1].isOpened = true;
					if (map[x][y + 1].minesAround == 0)
					{
						openEmptyCells(x, y + 1);
					}
				}
			}
		}
	}
};

