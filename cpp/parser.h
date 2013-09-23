#ifndef PARSER_H
#define PARSER_H

//#include "world.h"
//#include "location.h"
#include <vector>
#include <fstream>


#define EMPTY 	1
#define BOX		2
#define TARGET 	4
#define ROBOT 	8
#define OCCUPIED 16

typedef std::vector< std::vector<int> > Matrix;

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
