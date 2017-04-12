#include "ellersgenerator.h"


std::unique_ptr <Grid> EllersGenerator::generateMaze()
{
	std::unique_ptr<Grid> grid(new Grid(height, width));
	// grid->printGrid();
	//std::vector <Cell *> row;
	std::mt19937 seed (_seed);	
	int counter=1;
	
	std::unordered_map<Cell *, int> setMap;
	
	for (int col = 0; col < grid->getWidth(); col++) {
		//std::cout << "col " << col << std::endl;
	std::vector <Cell *> row;
		/* Create the first row with no cells being members of any set. */
		
		for (int i = 0; i < grid->getHeight(); i++) {
			Cell *cell = grid->findCell(i, col);
			if (cell != nullptr) row.push_back(cell);
		}

		/* Make unique sets for each cell. */
		for (Cell *cell : row) {
			if ( setMap.find(cell) == setMap.end())setMap[cell]=counter++;
		}

		Cell *right;	
		for (Cell *cell : row) {
			right = grid->findCell(cell->getX() + 1, col);

			if (right != nullptr) {
				int wall = seed() % 2;
				
				if (wall) {
					grid->insertEdge(right, cell);
					
					setMap[right]=setMap[cell];
				} else {
				}
			}
		}

		
		if(col<grid->getWidth()-1){
				Cell *bottom;
				Cell *lastCell;
				
				
				int prevSet = 0;
				bool bottomPath = false;
				for (Cell *cell : row) {
					
					
					if(prevSet==0){prevSet=setMap[cell];}
					if(prevSet!=setMap[cell]){//different set
						if(!bottomPath){
							grid->insertEdge(bottom, lastCell);
							
							setMap[bottom]=setMap[lastCell];
						}
						bottomPath = false;
					}
					
					bottom = grid->findCell(cell->getX(), cell->getY() + 1);

					if (bottom != nullptr) {
						int wall = seed() % 2;
						if (wall) {
							grid->insertEdge(bottom, cell);
							
							setMap[bottom]=setMap[cell];
							bottomPath = true;
							
						} else {
							
							
						}
					}
					prevSet=setMap[cell];
					lastCell=cell;
				}
				if(!bottomPath){
					grid->insertEdge(bottom, lastCell);
					
					setMap[bottom]=setMap[lastCell];
				}
		}
		for (Cell *cell : row) {
			if(col==grid->getWidth()-1){
				right = grid->findCell(cell->getX() + 1, col);
				if (right != nullptr) {
			
					grid->insertEdge(right, cell);
					
					setMap[right]=setMap[cell];
				}
			
			}
		}
	}
	

	//std::cout << "Done." << std::endl << "Your seed: " << seed() << std::endl;

	return grid;
}



