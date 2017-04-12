#pragma once

#include <chrono>
#include <random>
#include <vector>
#include <thread>
#include <iostream>
#include <unordered_map>
#include "grid.h"
#include "edge.h"
#include "cell.h"
#include "generator.h"

#define ARRAY_SIZE(x) (sizeof(x) / sizeof(*x))


class EllersGenerator : public Generator
{
	unsigned height, width, _seed;

	public:
		EllersGenerator(unsigned height1, unsigned width1, unsigned seed1):height(height1), width(width1), _seed(seed1) {};
		std::unique_ptr<Grid> generateMaze() override;
		//Cell *randomDirection(std::unique_ptr<Grid> grid, Cell *, int);
		//std::mt19937 seedGenerator(int);
};

