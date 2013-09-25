#include "parser.h"
#include <iostream>


using namespace std;

Parser::Parser(char* filename) {
	fs.open(filename);
	rows = 0;
	columns = 0;
}

Parser::~Parser() {
	fs.close();
}

Matrix Parser::loadMap() {
	Matrix map;
	int i, j;
	char c;

	fs >> columns >> rows;
	map.resize(rows);
	for (i = 0; i < rows; i++) {
		map[i].resize(columns);
		for (j = 0; j < columns; j++) {

			map[i][j] = readValue();
			cout << "i,j: " << i << ", " << j << " : " << map[i][j] << endl;			
		}
	}
	return map;
}

int Parser::getColumns() {
	return columns;
}

int Parser::getRows() {
	return rows;
}

int Parser::readValue() {
	char c;
	fs >> c;
	while (c == ' ') {
		fs >> c;
	}
	int value = 0;
	switch (c) {
		case '*':
			value = EMPTY;
			break;
		case 'B':
			value = BOX;
			break;
		case 'T':
			value = TARGET;
			break;
		case 'R':
			value = ROBOT;
			break;
		case '#':
			value = OCCUPIED;
			break;
		default:
			break;
	}
	return value;
}