#ifndef PARSER_H
#define PARSER_H

#include "world.h"
#include "location.h"
#include <iomanip>

class Parser {
	public:
		/* Constructors */
		Parser();

		/* Destructor */
		~Parser();

		Matrix loadMap();

	private:
		int readValue();
};
#endif
