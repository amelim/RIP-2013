#include "parser.h"
#include <iostream>

using namespace std;

Parser::Parser() {

}

Parser::~Parser() {

}

Matrix Parser::loadMap() {
	Matrix map;
	int i, j, columns, rows;
	
	cin >> columns >> rows;
	map.resize(rows);
	for (i = 0; i < rows; i++) {
		map[i].resize(columns);
		for (j = 0; j < columns; j++) {
			map[i][j] = readValue();			
		}
	}
	return map;
}

int Parser::readValue() {
	char c;
	cin >> c;
	while (c == ' ') {
		cin >> c;	
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
