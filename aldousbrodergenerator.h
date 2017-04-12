#pragma once

#include <chrono>
#include <random>
#include <thread>
#include <iostream>
#include "grid.h"
#include "edge.h"
#include "cell.h"
#include "generator.h"



	class AldousBroderGenerator : public Generator
	{
		unsigned height, width, _seed;

		public:
			AldousBroderGenerator(unsigned height1, unsigned width1, unsigned seed1):height(height1), width(width1), _seed(seed1) {};
			std::unique_ptr<Grid> generateMaze() override;
			//Cell *randomDirection(std::unique_ptr<Grid> grid, Cell *, int);
			//std::mt19937 seedGenerator(int);
	};

