#include "depthfirst.h"
	
	void DepthFirst::solveMaze()
	{

	Cell *currentCell;
	Cell *nextCell;
		std::stack<Cell *> cellStack;
		bool pathNotFound = true;
		Cell *cell = grid->findCell(0, 0);
		cellStack.push(cell);
		
		
		
		while(pathNotFound){
			bool connectionFound = false;
			
			currentCell = cellStack.top();
			
			
			std::vector <Cell *> connections = currentCell->getConnectedCells();
			
			
			if(connections.size()==0)break;
			for(unsigned int i = 0; i < connections.size(); i++) {
				
				nextCell = connections[i];
				
				bool visted = nextCell->getsVisited();
				
				if(!visted){
					
					
					if(grid->getWidth()-1==nextCell->getY() && grid->getHeight()-1==nextCell->getX()){
						pathNotFound=false;
						
					}
					nextCell->sVisit();
					cellStack.push(nextCell);
					connectionFound = true;
					break;
				}
			}
			
			if(!connectionFound){
				
				cellStack.pop();
				
			}
			
		}
		
		while(cellStack.size() > 0)
    {
		Cell *cell = cellStack.top();	
		
		cell->setPath();
        cellStack.pop();	
    }
		
		
	}