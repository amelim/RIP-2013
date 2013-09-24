#include "location.h"
#include "world.h"
#include "state.h"
#include "a_star.h"

#include <iostream>

using namespace std;

int main(){
  /* Test world class */
  int i,j;
  Matrix map;
  vector<int> tmp;
  for (i = 0; i < 4; i++){
    tmp.clear();

    for (j = 0; j < 4; j++) {
      tmp.push_back(EMPTY);
    }

    map.push_back(tmp);
  }

  vector<Location> boxes;
  vector<Location> targets;

  for (i = 1; i < 2; i++) {
    boxes.push_back(Location(i,i));
    targets.push_back(Location(i+1,i));
    map.at(i).at(i) = BOX;
    map.at(i+1).at(i) = TARGET;
  }

  World world(&map, new Location(0,0), &boxes, &targets);
  //world.printWorld();
  //world.printConfig();

  State state(world);
  state.printState("Starting");

  int pos;
  AStar astar(state);

  /*cout << "------------------------------" << endl;
  cout << "helloWorld: Output of AStar::printClosed()" << endl;
  astar.printClosed();
  cout << "------------------------------" << endl;*/

  /*if(astar.isClosed(&state, &pos)) {
	  cout << "helloWorld: state was already closed" << endl;
  } else {
	  cout << "helloWorld: state was NOT closed" << endl;
  }*/

  astar.solve();
  //vector<State> solution = astar.solve();
  //astar.printSolution();

    cout << "Hello World!" << endl;
  return 1;
}
