//TODO: 
//finish full function implementation
//allow output to solution file
//Modify README to match changes to naming
//Remove output file reference
#include "location.h"
#include "world.h"
#include "state.h"
#include "a_star.h"
#include <iostream>
#include <cstdio>
#include "parser.h"

using namespace std;

Matrix* FlipMatrix(Matrix *m, int rows,int cols){
  Matrix* x;
  x->resize(rows*cols);
	  for(int i =0;i<rows;i++){
		  for(int j=0;j<cols;j++){
			  x[i][j] = m[j][i];
      }
  }
  return x;
}

int main(int argc, char** argv){
  if(argc <2){
	  cout<<"Incorrect Usage: The correct usage is ""./planner <inputworld> [<output file>]\n\n";
  return 1;
  }

  char* iwString = argv[1];
  FILE* iwFile = fopen(iwString,"r");

  if(iwFile ==NULL) {
    cout <<"Error opening inputWorld, make sure the file exists.\n\n";
    return 2;
  }
  fclose(iwFile);
  Parser parser(iwString);
  Matrix map=parser.loadMap();
  int rows = parser.getRows();
  int cols = parser.getColumns();
  int i,j;
  for (i=0;i<rows;i++){
    for(j=0;j<cols;j++){

      printf("%d",map[i][j]);
      printf(" ");

      if(j==cols-1)
        printf("\n");
    }
  }

  Location RobotInit;
  //Matrix *test=FlipMatrix(&map,rows,cols);
  vector<Location>BoxesInit;
  vector<Location>BoxesTarget;
  //Find Location Robot in Matrix
  bool RobotExists=false;
  for (i=0;i<parser.getRows();i++){
	  for(j=0;j<parser.getColumns();j++){

		  if(map[i][j] == BOX){
		    BoxesInit.push_back(Location(i,j));
		  }
		  else if(map[i][j] == TARGET){
			  BoxesTarget.push_back(Location(i,j));
		  }
		  else if (map[i][j] == ROBOT){
			  RobotInit = Location(i,j);
			  RobotExists=true;
		  }
	  }
  }

  if(RobotExists == false){
    cout<<"No robot located on the map";
    return 3;
  }

  World inputWorld(&map,&RobotInit,&BoxesInit,&BoxesTarget);
  State state(inputWorld);
  //TODO: add error catching for world generation
  cout <<"Generated input world sucessfully.\n\n";
  //cout <<state;
  cout << "Rows: " << parser.getRows() << endl;
  cout << "Cols: " << parser.getColumns() << endl;
  state.printState();

  AStar astar(state);
  astar.solve();
  astar.printSolution();

  fclose(iwFile);

  return 0;
}
