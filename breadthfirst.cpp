#include "breadthfirst.h"
	
	void BreadthFirst::solveMaze()
	{
	
		Cell *currentCell;
		Cell *nextCell;
		
		bool pathNotFound = true;
		bool pathNotSet = true;
		Cell *cell = grid->findCell(0, 0);
		
		std::unordered_map<Cell *, Cell *> pathMap; 
		std::queue<Cell *> queue;
		queue.push(cell);
		cell->sVisit();
		while(pathNotFound){
			
			currentCell = queue.front();
			
			queue.pop();
			
			
			
			
			if(grid->getWidth()-1==currentCell->getY() && grid->getHeight()-1==currentCell->getX()){
						
						pathNotFound=false;
						
			}
			else {
			
				std::vector <Cell *> connections = currentCell->getConnectedCells();
				
				for(unsigned int i = 0; i < connections.size(); i++) {
					
					nextCell = connections[i];
					bool visted = nextCell->getsVisited();
					if(!visted){
						nextCell->sVisit();
						queue.push(nextCell);
						pathMap[nextCell]=currentCell;
					}
				}
			}
		
		}
		
		if(pathNotFound==false){
			
			cell = grid->findCell(grid->getHeight()-1 ,grid->getWidth()-1);
			cell->setPath();
			while(pathNotSet){
				cell = pathMap[cell];
				cell->setPath();
				if(cell->getX()==0 && cell->getY()==0){
						pathNotSet=false;
						
			}
			}
		}
		
	}