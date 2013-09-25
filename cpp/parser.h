#ifndef PARSER_H
#define PARSER_H

#include "world.h"
#include "location.h"
#include <vector>
#include <fstream>
#include <string>

class Parser {
	public:
		/* Constructor */
		Parser(char* problem);

		/* Destructor */
		~Parser();

		/* Load */
		Matrix loadMap();

		/* Properties */
		int getColumns();
		int getRows();

	private:
		int readValue();

		std::ifstream fs;
		int rows, columns;
};
#endif
