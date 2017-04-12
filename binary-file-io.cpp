#include "binary-file-io.h"

std::unique_ptr<Grid> binaryFileReader(std::string fileName) {
	int height, width, edges;
	int xCellA, xCellB, yCellA, yCellB;

	/* ::in to open file for input,
	   ::binary to format file for binary. */
	std::fstream fin(fileName, std::ios::in | std::ios::binary);

	/* Validation checks. */
	if (!fin.is_open()) {
		std::cerr << "Load file does not exist or could not be opened." << std::endl;
		return nullptr;
	}

	/* Move position to EOF to steal file size. */
	fin.seekg(0, std::ios::end);
	/* Preserve file size so we know when to stop in while loop. */
	std::streampos finSize = fin.tellg();
	/* Move position back to start of file to begin reading. */
	fin.seekg(0, std::ios::beg);

	fin.read((char *) &height, sizeof(height));
	fin.read((char *) &width, sizeof(width));
	fin.read((char *) &edges, sizeof(edges));

	/* Catch invalid dimensions. */
	if (height < 1 || width < 1) return nullptr;

	std::unique_ptr<Grid> grid(new Grid(height, width));

	/* Read through to the end of the file. */
	while (fin.tellg() < finSize) {
		/* Read in cell positions. */
		fin.read((char *) &xCellA, sizeof(xCellA));
		fin.read((char *) &yCellA, sizeof(yCellA));
		fin.read((char *) &xCellB, sizeof(xCellB));
		fin.read((char *) &yCellB, sizeof(yCellB));

		/* Insert an edge between the two read cells. */
		bool validInsert = grid->insertEdge(
				grid->findCell(xCellA, yCellA),
				grid->findCell(xCellB, yCellB)
			);

		/* Try catch any unformatted mazes being read in. */
		if (!validInsert) {
			std::cerr << "Error in load file. Errors may occur." << std::endl;
			return nullptr;
		}
	}

	fin.close();

	return grid;
}

void binaryFileWriter(std::unique_ptr<Grid>& grid, std::string fileName) {
	std::fstream fout(fileName, std::fstream::out | std::fstream::binary | std::fstream::trunc);
	int x, y;

	if (!fout.is_open()) {
		std::cerr << "An error occurred opening the save file." << std::endl;
		return;
	}

	/* List of edges to count and to iterate over for file writing. */
	std::vector <Edge *> edges = grid->getEveryEdge();

	/* Write maze format to file. */
	const int height = grid->getHeight();
	const int width = grid->getWidth();
	const int numEdges = edges.size();
	fout.write((char *) &height, sizeof(height));
	fout.write((char *) &width, sizeof(width));
	fout.write((char *) &numEdges, sizeof(numEdges));

	/* For each edge in the grid... */
	for (Edge *edge : edges) {
		/* Make cell A. */
		x = edge->getCellA()->getX();
		y = edge->getCellA()->getY();
		/* Write cell A to file. */
		fout.write((char *) &x, sizeof(x));
		fout.write((char *) &y, sizeof(y));

		/* Make cell B. */
		x = edge->getCellB()->getX();
		y = edge->getCellB()->getY();
		/* Write cell B to file. */
		fout.write((char *) &x, sizeof(x));
		fout.write((char *) &y, sizeof(y));
	}

	fout.close();
}