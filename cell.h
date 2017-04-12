#ifndef CELL_H
#define CELL_H

#include <vector>
#include <iostream>
#include <random>
#include "edge.h"

class Cell {
	/* Track cell position in grid. */
	int posX, posY;
	/* Store a list of edges within each cell. */
	std::vector <Cell *> connectedCells ;
	Cell * previousCell;
	/* Create a set used for Eller's algorithm. */
	std::vector <Cell *> *set;
	/* For generating mazes. */
	bool visited = false;
	bool right = false;
	bool down = true;
	// for searching
	bool sVisited = false;
	bool shortestPath = false;
	public:
		Cell(int, int);
		int getX() { return posX; }
		int getY() { return posY; }
		void insertConnection(Cell *);
		void print();
		void visit() { visited = true; }
		bool unvisited() { return !visited; }

		void sVisit() { sVisited = true; }
		bool getsVisited() { return sVisited; }
		
		void setPath () {shortestPath=true;}
		bool getShortestPath() {return shortestPath;}
		std::vector <Cell *> getConnectedCells(){return connectedCells;};
		
		void addPrevious(Cell * cell) {previousCell=cell;};
		Cell * getPrevious(){return previousCell;};
		
		void setSet( std::vector <Cell *> *s ) { set = s; };
		std::vector <Cell *> *getSet() { return set; };
/*
		std::vector <Cell *> getSet() { return set; };
		void setSet( std::vector <Cell *> s ) { set = s; };
		bool noSet() { return set.empty(); };
		*/
};


#endif