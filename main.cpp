
#include <vector>
#include <string>
#include <list> 
#include <chrono>

#include "grid.h"
#include "solver.h"
#include "depthfirst.h"
#include "breadthfirst.h"
#include "binary-file-io.h"
#include "svgsaver.h"
#include "aldousbrodergenerator.h"
#include "ellersgenerator.h"
#include "filesaver.h"
#include "dijkstraalgorithm.h"

#define FLAG_BINARY_LOAD "--lb"
#define FLAG_BINARY_SAVE "--sb"
#define FLAG_SVG_SAVE "--sv"

#define FLAG_GENERATE_ALDOUS "--ga"
#define FLAG_GENERATE_ELLERS "--ge"

#define FLAG_DEPTH_SOLVE "--ds"
#define FLAG_BREADTH_SOLVE "--bs"
#define FLAG_DIJKSTRA_SOLVE "--das"



#define DEFAULT_GRID_SIZE 5

void showMenu();

int main(int argc, char *argv[]) {

	std::unique_ptr<Grid> grid;
	std::unique_ptr<FileSaver> fileSaver;
	std::unique_ptr<Solver> pathFinder,pathFinder1,pathFinder2;
	std::string saveFileBinary, saveFileSVG, loadFile;
	std::list<Cell*> path;
	int gridHeight, gridWidth, gridSeed;
	bool generateAldous = false;
	bool generateEllers = false;
	bool loadBinary = false;
	bool saveBinary = false;
	bool saveSVG = false;
	bool depthSolve = false;
	bool breadthSolve = false;
	bool dijSolve = false;
	std::unique_ptr<Generator> generator;

	/* Read program parameters. */
	/* Start from 1 to skip program name. */
	for (int i = 1; i < argc; i++) {
		std::string arg = argv[i];

		if (arg == FLAG_GENERATE_ALDOUS || arg == FLAG_GENERATE_ELLERS) {
			if (arg == FLAG_GENERATE_ALDOUS) {
				generateAldous = true;
			} else {
				generateEllers = true;
			}
			try {
				gridSeed = (i + 1 < argc) ? atoi(argv[++i]) : 0;
				gridWidth = (i + 1 < argc) ? atoi(argv[i + 1]) : 0;
				gridHeight = (i + 2 < argc) ? atoi(argv[i + 2]) : 0;
			} catch (...) {
				std::cerr << "An error has occurred." << std::endl;
				showMenu();
				return 0;
			}
			
			/* If only the seed has been entered... */
			if (gridSeed > 0 && !gridWidth && !gridHeight) {
				gridWidth = DEFAULT_GRID_SIZE;
				gridHeight = DEFAULT_GRID_SIZE;
			}
			/* Else if only the width and height are entered... */
			/* Note that this if condition is confusingly written: 
				gridHeight is the third parameter, perform block if only 2 args are parsed.
			*/
			else if (gridWidth > 0 && gridSeed > 0 && !gridHeight) {
				/* Shift args back as seed is redundant. */
				gridHeight = gridWidth;
				gridWidth = gridSeed;
				gridSeed = -1;
				/* Shift forward one arg as we know the next arg is grid height. */
				i++;
			} 
			/* Else if no valid args are entered for the generate flag... */
			else if (!gridHeight || !gridWidth) {
				std::cerr << "Invalid grid width or height specified." << std::endl << std::endl;
				showMenu();
				break;
			}
			/* Else we have seed, height and width for generate and can skip over the next 2 args. */
			else i += 2;
		}
		else if (arg == FLAG_BINARY_LOAD) {
			loadBinary = true;
			loadFile = (i + 1 < argc) ? argv[++i] : "";
		}
		else if (arg == FLAG_BINARY_SAVE) {
			if (!loadBinary && !(generateAldous || generateEllers)) {
				std::cerr << "You must load or generate a maze before saving a grid." << std::endl << std::endl;
				showMenu();
				return 0;
			}
			saveBinary = true;
			saveFileBinary = (i + 1 < argc) ? argv[++i] : "";
		}
		else if (arg == FLAG_SVG_SAVE) {
			saveSVG = true;
			saveFileSVG = (i + 1 < argc) ? argv[++i] : "";
		}
		else if (arg == FLAG_DEPTH_SOLVE) {
			depthSolve = true;
		}
		else if (arg == FLAG_BREADTH_SOLVE) {
			breadthSolve = true;
		}
		else if (arg == FLAG_DIJKSTRA_SOLVE) {
			dijSolve = true;
		}
		else {
			std::cerr << "Invalid parameter detected: " << arg << std::endl << std::endl;
			showMenu();
			return 0;
		}
	}

	std::chrono::time_point<std::chrono::system_clock> start, end;
    
	
	if (generateAldous || generateEllers) {
		/* Larger grids may take >30 seconds on slower processors. */
		std::cout << "Generating maze (this may take a while)... \n";

		/* Designate which generator to use. */
		if (generateAldous) {
			
			generator = std::unique_ptr<Generator>(new AldousBroderGenerator(gridHeight, gridWidth, gridSeed));	
			
			std::cout << "Aldous Broder Generator time:\n";
			start = std::chrono::system_clock::now();
				grid = generator->generateMaze();
			end = std::chrono::system_clock::now();
			std::chrono::duration<double> elapsed_seconds = end-start;
			std::cout << elapsed_seconds.count() << "\n";			
		} else {
			generator = std::unique_ptr <Generator> (new EllersGenerator(gridHeight, gridWidth, gridSeed));
			
			std::cout << "Ellers Generator time:\n";
			start = std::chrono::system_clock::now();
				grid = generator->generateMaze();
			end = std::chrono::system_clock::now();
			std::chrono::duration<double> elapsed_seconds = end-start;
			std::cout << elapsed_seconds.count() << "\n";
			
		}
		/* Generate. */
	}
	else if (loadBinary) {
		grid = binaryFileReader(loadFile);
	}
	/* If we are trying to save to a file without loading or generating a maze... */
	else if (saveBinary || saveSVG) {
		std::cerr << "You must load or generate a maze before saving it." << std::endl;
		showMenu();
		return 0;
	}
	else {
		std::cerr << "Insufficient arguments." << std::endl << std::endl;
		showMenu();
		return 0;
	}

	if (saveBinary && grid != nullptr) {
		
		
		std::cout << "Binary Save time:\n";
		start = std::chrono::system_clock::now();
			binaryFileWriter(grid, saveFileBinary);
		end = std::chrono::system_clock::now();
		std::chrono::duration<double> elapsed_seconds = end-start;
		std::cout << elapsed_seconds.count() << "\n";
		
	}
	if(depthSolve && grid != nullptr){
		pathFinder = std::unique_ptr<Solver>(new DepthFirst(*grid));
		
		std::cout << "Depth time:\n";
		start = std::chrono::system_clock::now();
			pathFinder->solveMaze();
		end = std::chrono::system_clock::now();
		std::chrono::duration<double> elapsed_seconds = end-start;
		std::cout <<elapsed_seconds.count() << "\n";
		
	}
	if(breadthSolve && grid != nullptr){
		pathFinder1 = std::unique_ptr<Solver>(new BreadthFirst(*grid));
		std::cout << "Breadth time:\n";
		
		start = std::chrono::system_clock::now();
			pathFinder1->solveMaze();
		end = std::chrono::system_clock::now();
		std::chrono::duration<double> elapsed_seconds = end-start;
		std::cout << elapsed_seconds.count() << "\n";
	}
	
	if(dijSolve && grid != nullptr){
		std::cout << "Dijkstra time:\n";
		pathFinder2 = std::unique_ptr<Solver>(new DijkstraAlgorithm(*grid));

			
			
			
			start = std::chrono::system_clock::now();
				pathFinder2->solveMaze();
			end = std::chrono::system_clock::now();
			std::chrono::duration<double> elapsed_seconds = end-start;
			std::cout << elapsed_seconds.count() << "\n";
		
	}
	if (saveSVG && grid != nullptr) {
		//svgSaver(grid, saveFileSVG);
		fileSaver = std::unique_ptr<FileSaver>(new SVGSaver(*grid,saveFileSVG,&path));
		
		
		std::cout << "SVG Save time:\n";
		start = std::chrono::system_clock::now();
			fileSaver->saveMaze();
		end = std::chrono::system_clock::now();
		std::chrono::duration<double> elapsed_seconds = end-start;
		std::cout << elapsed_seconds.count() << "\n";
	}
	

	return 0;
}

void showMenu() {
	std::cout << "How to use this program:" << std::endl
			  << "------------------------" << std::endl << std::endl
			  << "\t" << FLAG_GENERATE_ALDOUS << " aldous: seed width height, "
			  << "where seed, width and height should be integers." << std::endl
			  
			  << "\t" << FLAG_GENERATE_ELLERS << " ellers: seed width height, "
			  << "where seed, width and height should be integers." << std::endl
			  << "\t\tYou may omit seed, or both height and width, but not both."
			  << std::endl << "\t" << FLAG_BINARY_LOAD << " somemaze.maze, "
			  << "where 'somemaze.maze' is the name of a binary file to save."
			  << std::endl << "\t" << FLAG_BINARY_SAVE << " somemaze.maze, "
			  << "where 'somemaze.maze' is the name of a binary file to load."
			  << std::endl << "\t" << FLAG_SVG_SAVE << " somemaze.svg, "
			  << "where 'somemaze.svg' is the name of the file a maze should " 
			  << "be saved to."
			  
			  << std::endl << "\t" << FLAG_DEPTH_SOLVE << " to solve maze"  
			  << " using Depth First Search." << std::endl;
}