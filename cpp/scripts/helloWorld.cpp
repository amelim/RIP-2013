#include "location.h"
#include "world.h"
#include "state.h"
#include "a_star.h"

#include <iostream>

using namespace std;

int main(){
  /* Test world class */
  Matrix map;
  vector<int> tmp;

  for (int x = 0; x < 5; x++){
    tmp.clear();
    for (int y = 0; y < 4; y++) {// columns
      tmp.push_back(EMPTY);
    }
    map.push_back(tmp);
  }
	

  vector<Location> boxes;
  vector<Location> targets;

  for (int i = 1; i < 2; i++) {
    boxes.push_back(Location(i,i));
    targets.push_back(Location(i,i+1));
    map[i][i] = BOX;
    map[i][i+1] = TARGET;
  }

  World world(&map, new Location(0,1), &boxes, &targets);
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
