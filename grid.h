#ifndef GRID_H
#define GRID_H

#include <vector>
#include "cell.h"

	class Grid {
		int width, height;
		/* Vector of vector of Cells to store grid data. */
		std::vector <std::vector <Cell*>> cells;
		/* Store a list of edges, where each edge references the two cells it connects. */
		std::vector <Edge *> edges;

		public:
			Grid(int, int);
			Cell *findCell(int, int);
			bool insertEdge(Cell *, Cell *);
			std::vector <Edge *> getEveryEdge() { return this->edges; }
			int getHeight() { return this->height; }
			int getWidth() { return this->width; }
			void printGrid();
	};

#endif