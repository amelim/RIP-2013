#include "location.h"
#include "world.h"
#include "state.h"
#include "a_star.h"

#include <iostream>

using namespace std;

int main(){
	/* Test location class */
	Location loc(1, 3);
	//loc.print();

	/* Test world class */
	int i,j;
	Matrix map;
	vector<int> tmp;
	for (i = 0; i < 10; i++){
		tmp.clear();

		for (j = 0; j < 10; j++) {
			tmp.push_back(EMPTY);
		}

		map.push_back(tmp);
	}

	vector<Location> boxes;
	for (i = 0; i < 5; i++) {
		boxes.push_back(Location(i,i));
		map.at(i).at(i) = BOX;
		map.at(i+1).at(i) = TARGET;
	}

	map.at(1).at(5) = ROBOT;

	World world(&map, new Location(1,1), &boxes, &boxes);
	//world.printWorld();
	//world.printConfig();

	State state(world);
	//cout << state;

	AStar astar(state);
	cout << "Output of AStar::printClosed()" << endl;
	astar.printClosed();

  	cout << "Hello World!" << endl;
  return 1;
}
