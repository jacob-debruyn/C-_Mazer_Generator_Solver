#include "edge.h"

Edge::Edge(Cell *cellA, Cell *cellB) {
	this->cellA = cellA;
	this->cellB = cellB;
}

Cell *Edge::getOpposite(Cell *cell) {
	/* Test if the cell exists within this object. */
	if (cell != this->cellA || cell != this->cellB) return nullptr;
	/* Return the opposite cell to what is parsed. */
	return (cell == this->cellA) ? this->cellA : this->cellB;
}