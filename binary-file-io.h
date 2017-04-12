#ifndef BINARY_FILE_IO_H
#define BINARY_FILE_IO_H

#include <iostream>
#include <fstream>
#include <vector>
#include <thread>
#include <string>
#include "grid.h"

std::unique_ptr<Grid> binaryFileReader(std::string);
void binaryFileWriter(std::unique_ptr<Grid>&, std::string);

#endif