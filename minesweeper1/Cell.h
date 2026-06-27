#pragma once
#ifndef CELL_H
#define CELL_H
#include <iostream>
#include "windows.h"

class Cell {

public:
	int coordinates_X;
	int coordinates_Y;
	bool isFlagged = false;
	bool isOpened = false;
	bool isMine = false;
	char glyph = '_';
	int minesAround = 0;

	Cell(int x, int y, bool isNotSafe = false, bool isNotClosed = false);
	Cell() = default;

	/*void open(); */
};

#endif
