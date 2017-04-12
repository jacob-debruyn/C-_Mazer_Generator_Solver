#ifndef EDGE_H
#define EDGE_H

#include "cell.h"

/* Compiler errors occur if Cell is not defined here. Look into. */
class Cell;

class Edge {
	Cell *cellA, *cellB;

	public:
		Edge(Cell *, Cell *);
		Cell *getCellA() { return this->cellA; };
		Cell *getCellB() { return this->cellB; };
		Cell *getOpposite(Cell *);
};

#endif