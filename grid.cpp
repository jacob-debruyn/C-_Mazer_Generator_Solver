#include "grid.h"
#include <iostream>

	Grid::Grid(int height = 0, int width = 0) {
		this->height = height;
		this->width = width;

		/* Create complete grid of cells. */
		/* TODO (bug) free up memory! */
		for (int i = 0; i < height; i++) {
			/* Create an inner row to build a grid of cells row by row. */
			std::vector <Cell *> inner;

			for (int j = 0; j < width; j++) {
				/* Allocate memory for new cell at current position. */
				Cell *temp = new Cell(i, j);
				/* Insert new cell into inner row of vector. */
				inner.push_back(temp);
				
			}
			/* Insert inner row into outer cells vector. */
			this->cells.push_back(inner);
		}
	}

	Cell *Grid::findCell(int x, int y) {
		/* Range check. */
		bool validX = (x < this->height && x > -1);
		bool validY = (y < this->width && y > -1);

		/* Returns a valid cell or null. */
		return (validX && validY) ? this->cells[x][y] : nullptr;
	}

	bool Grid::insertEdge(Cell *cellA, Cell *cellB) {
		if (cellA == nullptr || cellB == nullptr) {
			std::cerr << "Invalid cells detected during edge insertion. Caution errors." << std::endl;
			return false;
		}

		/* Create a new edge between the two cells. */
		Edge *edge = new Edge(cellA, cellB);
		/* Update cell info to create a link between the two cells. */
		cellA->insertConnection(cellB);
		cellB->insertConnection(cellA);
		/* Insert the new edge into existing list of edges. */
		edges.push_back(edge);
		return true;
	}

	void Grid::printGrid() {
		/* Debug print method. */
		std::cout << "Height: " << this->height << std::endl;
		std::cout << "Width: " << this->width << std::endl;

		for (int i = 0; i < this->width; i++) {
			for (int j = 0; j < this->height; j++) {
				cells[i][j]->print();
			}
			std::cout << std::endl;
		}
	}
