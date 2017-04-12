#include "aldousbrodergenerator.h"




	std::unique_ptr<Grid> AldousBroderGenerator::generateMaze()
	{
		int counter=1;
std::unique_ptr<Grid> grid(new Grid(height, width));

    	//Grid *grid = new Grid(height, width);
		
	Cell *cur, *next;
	// Generate seed for algorithm pathtaking. 
	//std::mt19937 seed = seedGenerator(_seed);
	
	std::mt19937 seed (_seed);
	
	// Track how many cells we need to visit and how many we have visited. 
	int remaining = width * height;
	// Pick a random position on the grid to start from. 
	int randomX = seed() % (width-1), randomY = seed() % (height-1);
	// Create a list of visited cells to track current. 

	

	
	// --- BUG --- 
	/*
	if (height != width) {
		std::cerr << "Bug detected! Unfortunately the program has to end."
				  << std::endl << "Try using equal width and height. Sorry!"
				  << std::endl << "Segfaults may occur." << std::endl;
		return nullptr;
	}
*/
	// Start at the first randomly selected cell. 
	cur = grid->findCell(randomX, randomY);
	// Choose random direction from current cell,
		//if cell is unvisited then create an edge to it. 
		
	while (remaining > 0) {
		//std::chrono::duration<int, std::milli> timespan(1000);
//std::this_thread::sleep_for(timespan);


	const int NUM_DIR = 4;
	const int directions[NUM_DIR] = {1, 2, 3, 4};
	int dir = directions[seed() % NUM_DIR];
	
	
	int x = cur->getX(), y = cur->getY();
	if(dir==1){
		next = grid->findCell(x + 1, y);
	}
	if(dir==2){
		next = grid->findCell(x - 1, y);
	}
	if(dir==3){
		next = grid->findCell(x, y + 1);
	}
	if(dir==4){
		next = grid->findCell(x, y - 1);
	}

		if (next != nullptr) {
			
			if (next->unvisited()) {
				next->visit();
				grid->insertEdge(next, cur);
				std::cout << counter  << std::endl;
				counter++;
				remaining--;
				
			}
			// Move to next cell. 
			cur = next;
		}
		
	}

	//std::cout << "Done." << std::endl << "Your seed: " << seed() << std::endl;

	return grid;
}