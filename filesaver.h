#pragma once

#include "grid.h"
#include <string>
#include <stdexcept>


	class FileSaver
	{
		public:
			virtual void saveMaze() = 0;
			FileSaver() {};
			~FileSaver() {};

	};


