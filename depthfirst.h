#pragma once

#include <chrono>
#include <random>
#include <thread>
#include <iostream>
#include <stack>
#include "grid.h"
#include "edge.h"
#include "cell.h"
#include "solver.h"


#include <list> 

	class DepthFirst : public Solver
	{
		Grid *grid;

		public:
			DepthFirst(std::unique_ptr<Grid>&);
			DepthFirst(Grid & grid): grid(&grid) {};
			virtual void solveMaze() override;
	};

