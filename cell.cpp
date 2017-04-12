#include "cell.h"

Cell::Cell(int x = 0, int y = 0) {
	this->posX = x;
	this->posY = y;
}

void Cell::insertConnection(Cell *cell) {
	/* Each cell stores a list of cells it is connected to. */
	this->connectedCells.push_back(cell);
}

void Cell::print() {
	/* Debug method. */
	std::cout << "[" << this->posX << "," << this->posY << "]";
}