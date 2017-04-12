#include "dijkstraalgorithm.h"
	
	void DijkstraAlgorithm::solveMaze()
	{
		
		
		

		
		std::priority_queue< P, std::vector<P>, std::greater<P> > queue;
		
		//queue.push(std::make_pair(std::numeric_limits<int>::max(), grid->findCell(0,0)));			
		queue.push(std::make_pair(0, grid->findCell(0,0)));			
		
		
		
		
		Cell *currentCell;
		Cell *nextCell;
		int cellNum = grid->getHeight()*grid->getWidth()-1;
		//std::cout << cellNum << std::endl;

		bool pathNotSet = true;
		
		Cell *cell = grid->findCell(0, 0);
		
		std::unordered_map<Cell *, int> distanceMap;
		std::unordered_map<Cell *, Cell *> pathMap; 
		
		
		for(int i=0;i<grid->getHeight();i++){
			for(int j=0;j<grid->getWidth();j++){
				cell = grid->findCell(i, j);
				distanceMap[cell]=std::numeric_limits<int>::max();
			}
		}
		distanceMap[grid->findCell(0, 0)]=0;
		//cell->sVisit();
		while(cellNum!=0){
			
			
		
			
			
			//get top of queue (min value)
			//update distance map
			//pop from queue after we are done with it
			currentCell = std::get<1>(queue.top());
			if(!currentCell->getsVisited()){
				currentCell->sVisit();
				cellNum--;
			}
			distanceMap[currentCell]=std::get<0>(queue.top());
			queue.pop();
			
			
			std::vector <Cell *> connections = currentCell->getConnectedCells();
			for(unsigned int i = 0; i < connections.size(); i++) {	

			
				nextCell = connections[i];
				
				bool visted = nextCell->getsVisited();
				
				
				if(!visted){
					if(distanceMap[nextCell]>(distanceMap[currentCell]+1)){
						
						distanceMap[nextCell]=distanceMap[currentCell]+1;
						queue.push(std::make_pair(distanceMap[currentCell]+1, nextCell));	
						pathMap[nextCell]=currentCell;						
					}
					
				}
				
			}
			//std::cout << cellNum << std::endl;
		
		}
		
		
			
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
	