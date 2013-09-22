//TODO: 
//finish full function implementation
//allow output to solution file
#include "location.h"
#include "world.h"
#include "state.h"
#include "a_star.h"
#include <iostream>
#include <cstdio>
using namespace std;
//Mattheus's Files


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

//Create Matrices world from inputWorld
//Location robotInit()
//Matrix inputMap = CreateWorld(iwFile);
//vector<Location> boxesInit= inputWorld.getBoxesInit();
//vector <Location> boxesTarget = inputWorld.getBoxesTarget();
//World inputWorld(inputMap,robotInit,boxesInit,boxesTarget);
//State state(inputWorld);
//TODO: add error catching for world generation
//cout <<"Generated input world sucessfully.\n\n";

//cout <<state;

//AStar astar(state);
//astar.solve();
//astar.printSolution();



fclose(iwFile);
//#ifdef outputFile
//fclose(outputFile);
//#endif
return 0;
}
