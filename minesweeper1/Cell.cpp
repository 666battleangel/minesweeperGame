#include "pch.h"
#include <iostream>
#include <vector>
#include "Cell.h"

Cell::Cell(int x, int y, bool isNotSafe, bool isNotClosed)
{
	coordinates_X = x;
	coordinates_Y = y;
	isMine = isNotSafe;
	isOpened = isNotClosed;
};
