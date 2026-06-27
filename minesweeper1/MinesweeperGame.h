#pragma once 
#ifndef MINESWEEPERGAME_H
#define MINESWEEPERGAME_H
#include "Cell.h"
#include <vector>

class MinesweeperGame {

private:
	int max_x = 0;
	int max_y = 0;
	int mineAmount = 0;
	int flagCount = 0; 
	bool firstMoveDone = false;
	bool gameWon = false;
	bool gameLost = false;
	bool validInput(int w, int h, int mines); 
	void placeMines(int safeX, int safeY); 
	void countMinesAround();
	void openEmptyCells(int x, int y);
	std::vector<std::vector<Cell>> map;

public:
	enum class openResult
	{
		NoChange, 
		Opened, 
		Lost, 
		Won
	};
	openResult openCell(int x, int y); 

	MinesweeperGame() = default; 
	bool createNewGame(int w, int h, int mines); 
	
	int getMax_x()const; 
	int getMax_y()const; 
	int getMineAmount()const; 
	int getFlagCount()const; 

	bool isGameWon()const; 
	bool isGameLost()const; 

	const Cell& getCell(int x, int y)const;
};
#endif