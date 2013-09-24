#ifndef PARSER_H
#define PARSER_H

#include "world.h"
#include "location.h"
#include <vector>
#include <fstream>

class Parser {
	public:
		/* Constructors */
		Parser(char* problem);

		/* Destructor */
		~Parser();

		Matrix loadMap();

	private:
		int readValue();

		std::ifstream fs;
};
#endif
