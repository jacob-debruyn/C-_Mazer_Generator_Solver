#pragma once

#include "grid.h"
#include <string>
#include <memory>


	class Generator
	{
		public:
			virtual std::unique_ptr<Grid> generateMaze() = 0;
			Generator() {};
			~Generator() {};

			
	};

