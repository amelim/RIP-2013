#include "location.h"
#include "world.h"
#include "state.h"
#include "a_star.h"
#include "parser.h"
#include <iostream>

using namespace std;

int main(){

  char* iwString = "../problems/problem3";
  FILE* iwFile = fopen(iwString,"r");
  Parser parser(iwString);
  Matrix map=parser.loadMap();
  int cols = parser.getRows();
  int rows = parser.getColumns();
  cout << "Rows: " << rows << endl;
  cout << "Cols: " << cols << endl;

  Location RobotInit;
  vector<Location>BoxesInit;
  vector<Location>BoxesTarget;
  //Find Location Robot in Matrix
  bool RobotExists=false;
  for (int x=0; x<parser.getRows(); x++){
	  for(int y=0; y<parser.getColumns(); y++){

		  if(map[x][y] == BOX){
		    cout << "Box at: " << x << ", " << y << endl;
		    BoxesInit.push_back(Location(x,y));
		  }
		  else if(map[x][y] == TARGET){
		    cout << "Target at: " << x <<  ", " << y << endl;
			  BoxesTarget.push_back(Location(x,y));
		  }
		  else if (map[x][y] == ROBOT){
		    cout << "Robot at: " << x << ", " << y << endl;
			  RobotInit = Location(x,y);
		  }
	  }
  }

  World inputWorld(&map,&RobotInit,&BoxesInit,&BoxesTarget);
  State state(inputWorld);
  state.printState();

  AStar astar(state);
  astar.solve();


}
