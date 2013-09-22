#include "state.h"
#include <stdlib.h>

using namespace std;

State::State(){
}

/* For instantiation based on a parent search node */
// TODO: Don't think this is needed
State::State(State &parent, Direction dir) {
	parent_ = &parent;
	world_ = parent.getWorld();
	curRobot_ = parent.getRobot();
	curBoxes_ = parent.getCurBoxes();
	g_ = computeGCost();
	h_ = computeHCost();
	f_ = g_ + h_;

}
// Initialize a state based upon the individual components
State::State(World &world, Location &curRobot, vector<Location> &curBoxes, State &parent){
  world_ = &world;
  parent_ = &parent;
  curBoxes_ = curBoxes;
  curRobot_ = &curRobot;
	g_ = computeGCost();
	h_ = computeHCost();
	f_ = g_ + h_;
}
// Initialize the first state based upon the world configuration
State::State(World &world) {
	world_ = new World(world.getMap(), world.getInitRobotLocation(), world.getInitBoxes(), world.getTargetBoxes());
	curBoxes_ = *world_->getInitBoxes();
	curRobot_ = world_->getInitRobotLocation();
	g_ = computeGCost();
	h_ = computeHCost();
	f_ = g_ + h_;
}

bool State::isGoal(){
  return false;
}

bool State::boxLogic(const int i, vector<Location> newBoxes, vector<State> expands, const Direction dir){
  if(curBoxes_[i].adjacent(*curRobot_, dir)){
    // Check to make sure you aren't going to push a box into another
    bool free = true;
    for(unsigned int j = 0; j < curBoxes_.size(); j++){
      // If any other box is adjacent to the pushed box inthe direction, it's not free!
      if(j != i && curBoxes_[i].adjacent(curBoxes_[j], dir))
        return false; 
		}

    // Robot is adjacent to box i and box i is not adjacent to any other of the boxes
    newBoxes[i] = curBoxes_[i].push(dir);
	  Location newRob = curRobot_->push(dir);
		State child(*world_, newRob, newBoxes, *this);
		expands.push_back(child);
		return true;
  }
  else
    return false;
}
/*
 * This function returns the possible states from the four different actions (robot up left right down)
 */
vector<State> State::expandState(){

  vector<State> expands;
  Matrix map = *world_->getMap();
  // Flags to ensure we only add one state for each possible action
  bool left = false;
  bool right = false;
  bool up = false;
  bool down = false;
	// -- Edge Conditions -- //
	// Make sure we cannot go off the map
  if(curRobot_->getX() == 0){ 
  	expands.push_back(State(*this, LEFT));
  	left = true;
	}
  
  if(curRobot_->getX() == world_->getSizeX()-1){
  	expands.push_back(State(*this, RIGHT));
  	right = true;
	}

  if(curRobot_->getY() == 0){
  	expands.push_back(State(*this, UP));
  	up = true;
	}
  
  if(curRobot_->getY() == world_->getSizeY()-1){
  	expands.push_back(State(*this, DOWN));
  	down = true;
	}
  	
  // -- Push Box-- //
  vector<Location> newBoxes = curBoxes_;
  for(unsigned int i = 0; i < curBoxes_.size(); i++){
    // Check to see if we will push any boxes (i.e. we are adjacent)
    if(!left)
      left = boxLogic(i, newBoxes, expands, LEFT);
    if(!right)
      right = boxLogic(i, newBoxes, expands, RIGHT);
    if(!up)
      up = boxLogic(i, newBoxes, expands, UP);
    if(!down)
      down = boxLogic(i, newBoxes, expands, DOWN);
  }

  // -- Free movement logic -- //
  if(!left){
    Location newRob = curRobot_->push(LEFT);
		State child(*world_, newRob, newBoxes, *this);
		left = true;
		expands.push_back(child);
  }
  if(!right){
    Location newRob = curRobot_->push(RIGHT);
		State child(*world_, newRob, newBoxes, *this);
		right = true;
		expands.push_back(child);
  }
  if(!up){
    Location newRob = curRobot_->push(UP);
		State child(*world_, newRob, newBoxes, *this);
		up = true;
		expands.push_back(child);
  }
  if(!down){
    Location newRob = curRobot_->push(DOWN);
		State child(*world_, newRob, newBoxes, *this);
		down = true;
		expands.push_back(child);
  }
  return expands;
}

/* Display functions */
void State::printState(const string& name){
	cout << "State: " <<  name << endl;
	cout << "G Cost: " << g_ << endl;
	cout << "H Cost: " << h_ << endl;
	cout << "F Cost: " << f_ << endl;

	int mapSizeX = world_->getSizeX();
	int mapSizeY = world_->getSizeY();

	/* Create temporary map for display purposes only */
	Matrix mapTmp;
	vector<int> tmp;

	for (int x = 0; x < mapSizeX; x++) {
		tmp.clear();

		for (int y = 0; y < mapSizeY; y++) {
			tmp.push_back(EMPTY);
		}

		mapTmp.push_back(tmp);
	}

  cout << "Robot position: " << curRobot_->getX() << " " << curRobot_->getY() << endl;
	/* Add robot location */
	mapTmp.at(curRobot_->getY()).at(curRobot_->getX()) = ROBOT;

	/* Add boxes */
	int i;
	for (i = 0; i < curBoxes_.size(); i++) {
		mapTmp.at(curBoxes_.at(i).getY()).at(curBoxes_.at(i).getX()) = BOX;
	}
	
	for (int x = 0; x < mapSizeX; x++) {
		for (int y = 0; y < mapSizeY; y++) {
			switch(mapTmp.at(y).at(x)) {
				case EMPTY: 		cout << setw(2) << "-"; break;
				case BOX: 			cout << setw(2) <<"B"; break;
				case TARGET: 		cout << setw(2) <<"T"; break;
				case ROBOT: 		cout << setw(2) <<"S"; break;
				case OCCUPIED: 		cout << setw(2) <<"1"; break;
				case BOX+TARGET: 	cout << setw(2) <<"R"; break;
				default: 	break;
			}
		}

		cout << endl;
	}
}

/* ---------------------- */
/* Cost functions 		  */
/* ---------------------- */
// Returns the Manhattan Distance between robot and loc 
int State::distanceBetween(const Location& loc1, const Location &loc2) const{
	//loc1.print();
	//loc2.print();
  int dX = abs(loc1.getX() - loc2.getX());
  int dY = abs(loc1.getY() - loc2.getY());
  /*cout << "Cost between: " << endl;
  loc1.print("target");
  loc2.print("current");
  cout << " is " << dX + dY << endl;*/
  return dX + dY;
}

// Cost from start to current pos
int State::computeGCost() {
	int cost = 0;
	// Get the starting spots
	vector<Location> inits = *world_->getInitBoxes();

	// For each box, compute the distance from the boxes current location and it's starting point
	for(unsigned int i = 0; i < world_->getNumberOfBoxes(); i++){
		cost += distanceBetween(inits[i], curBoxes_[i]);
	}
	return cost;
}
// Heuristic Cost
int State::computeHCost() {
	int cost = 0;
	// Get the starting spots
	vector<Location> targets = *world_->getTargetBoxes();

	// For each box, compute the distance from the boxes current location and it's target
	for(unsigned int i = 0; i < world_->getNumberOfBoxes(); i++){
		cost += distanceBetween(targets[i], curBoxes_[i]);
	}
	return cost;
}
// NOT NEEDED
int State::computeFCost() {}; 	//TODO: implement this function

void State::setGCost(int g) { g_ = g; };
void State::setHCost(int h) { h_ = h; };
void State::setFCost(int f) { f_ = f; };

/* ---------------------- */
/* Overloaded << operator */
/* ---------------------- */
std::ostream& operator<<(std::ostream& os, const State& state) {
	state.getWorld()->printWorld();
	//state.getWorld()->printConfig();
	return os;
}

/* Overload comparison operator */
bool operator== (State &s1, State &s2) {
	/* Compare robot loation */
	if (s1.getRobot() != s2.getRobot())
		return false;

	/* Compare box locations */
	std::vector<Location> s1Boxes = s1.getCurBoxes();
	std::vector<Location> s2Boxes = s2.getCurBoxes();

	for(int i = 0; i < s1Boxes.size(); i++) {
		if(s1Boxes.at(i) != s2Boxes.at(i))
			return false;
	}

	/* Compare f, g, and h costs */
	if(s1.getFCost() != s2.getFCost())
		return false;
	if(s1.getGCost() != s2.getGCost())
		return false;
	if(s1.getHCost() != s2.getHCost())
		return false;

	/*Compare parent */
	if(s1.getParent() != s2.getParent())
		return false;

	return true;
}

bool operator!= (State &s1, State &s2) {
	return !(s1 == s2);
}
