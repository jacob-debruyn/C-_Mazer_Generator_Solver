#pragma once

#include <chrono>
#include <random>
#include <thread>
#include <iostream>
#include <unordered_map>
#include <queue>

#include "grid.h"
#include "edge.h"
#include "cell.h"
#include "solver.h"


#include <list> 

	class BreadthFirst : public Solver
	{
		Grid *grid;

		public:
			BreadthFirst(std::unique_ptr<Grid>&);
			BreadthFirst(Grid & grid): grid(&grid) {};
			virtual void solveMaze() override;
	};

