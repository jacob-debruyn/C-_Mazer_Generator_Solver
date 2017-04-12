#pragma once

#include <chrono>
#include <random>
#include <thread>
#include <iostream>
#include <stack>
#include <queue>
#include <vector>
#include "grid.h"
#include "edge.h"
#include "cell.h"
#include "solver.h"
#include <limits>
#include <unordered_map>
#include <list> 
	typedef std::pair<int, Cell*> P;
	class DijkstraAlgorithm : public Solver
	{
		Grid *grid;

		public:
			DijkstraAlgorithm(std::unique_ptr<Grid>&);
			DijkstraAlgorithm(Grid & grid): grid(&grid) {};
			virtual void solveMaze() override;
	};

