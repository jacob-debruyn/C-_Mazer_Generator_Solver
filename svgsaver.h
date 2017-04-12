#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <memory>
#include <list>
#include "grid.h"
#include "filesaver.h"

#define BORDER_SIZE 2
#define CELL_SIZING 21
#define CELL_WIDTH 40
#define CELL_HEIGHT 40






	class SVGSaver : public FileSaver
	{
		Grid * grid;
		std::string fileName;
		std::list<Cell*> * pathWay;

		public:
			SVGSaver(std::unique_ptr<Grid>&, std::string&, std::list<Cell*>&);
			
			SVGSaver(Grid & grid, std::string & fileName, std::list<Cell*> * pathWay)
			: grid(&grid), fileName(fileName), pathWay(pathWay) {};
			virtual void saveMaze() override;
	};

