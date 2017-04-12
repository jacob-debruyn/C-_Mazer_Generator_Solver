#include "svgsaver.h"
	
	void SVGSaver::saveMaze()
	{
	/* ::out to open file for output, 
	   ::trunc to clear any existing file contents. */
	std::ofstream fout(fileName, std::fstream::out | std::fstream::trunc);

	/* Validation checks. */
	if (!fout.is_open()) {
		std::cerr << "Could not open file." << std::endl;
		return;
	}
	// if (!grid->getEveryEdge.size()) {
	// 	std::cerr << "Grid has no edges to print as maze." << std::endl;
	// 	return;
	// }

	float padding = 0.2;
	int boxWidth = 21 * grid->getHeight() + padding+2;
	int boxHeight = 21 * grid->getWidth() + padding+2;
	fout << "<svg width='" << boxWidth << "' ";
	fout << "height='" << boxHeight << "' ";
	fout << "xmlns='http://www.w3.org/2000/svg'>" << "\n";

	fout << "<rect width='" << boxWidth << "' height='" << boxHeight;
	fout << "' style='fill: black' />" << "\n";
	
	/* Make a line for every edge in the grid. */
	std::vector <Edge *> edges = grid->getEveryEdge();
	for (Edge *edge : edges) {
		/* Cast denomonator to double or decimal is lost after math. */
		double x1 = edge->getCellA()->getX();
		double x2 = edge->getCellB()->getX();
		double y1 = edge->getCellA()->getY();
		double y2 = edge->getCellB()->getY();
		/* Generate line based on edge position in grid. */
	
			int cellWidth = 40;
			int cellHeight = 40;
			int xPos;
			int yPos;
		
			if(x1<x2)xPos = (21)*x1+2;
			if(x2<x1)xPos = (21)*x2+2;
			if(x2==x1){
				xPos = (21)*x2+2;
				cellWidth = 19;
			}
			
			if(y1<y2)yPos = (21)*y1+2;
			if(y2<y1)yPos = (21)*y2+2;
			if(y2==y1){
				yPos = (21)*y2+2;
				cellHeight = 19;
			}
			
			fout << "<rect style='fill:rgb(255,255,255)' ";
			fout << " x='" << xPos;
			fout << "' y='" << yPos;
			fout << "' width='" << cellWidth;
			fout << "' height='" << cellHeight << "'/>" << "\n";
	
	
	
	}
for (Edge *edge : edges) {
		/* Cast denomonator to double or decimal is lost after math. */
		double x1 = edge->getCellA()->getX();
		double x2 = edge->getCellB()->getX();
		double y1 = edge->getCellA()->getY();
		double y2 = edge->getCellB()->getY();
		

		if(edge->getCellA()->getShortestPath()==true&&edge->getCellB()->getShortestPath()==true){
		/* Generate line based on edge position in grid. */
	
			int cellWidth = 40;
			int cellHeight = 40;
			int xPos;
			int yPos;
		
			if(x1<x2)xPos = (21)*x1+2;
			if(x2<x1)xPos = (21)*x2+2;
			if(x2==x1){
				xPos = (21)*x2+2;
				cellWidth = 19;
			}
			
			if(y1<y2)yPos = (21)*y1+2;
			if(y2<y1)yPos = (21)*y2+2;
			if(y2==y1){
				yPos = (21)*y2+2;
				cellHeight = 19;
			}
			
			fout << "<rect style='fill:rgb(255,0,0)' ";
			fout << " x='" << xPos;
			fout << "' y='" << yPos;
			fout << "' width='" << cellWidth;
			fout << "' height='" << cellHeight << "'/>" << "\n";
		}
	}
	
	
	/* Close SVG tag and file. */
	fout << "</svg>";
	fout.close();
}