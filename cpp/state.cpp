#include "state.h"
#include <stdlib.h>

using namespace std;

State::State(){
}

/* For instantiation based on a parent search node */
State::State(State &parent, Direction dir) {
	// TODO: create new state node based on parent
	// 1. assign parent pointer
	// 2. compute g, h, f cost based on parent node
	//
	// 3. based on the parent node, this constructor has 
	// 	  to reason based on the dir parameter whether a box 
	// 	  has been pushed to another location

	parent_ = &parent;
	g_ = computeGCost();
	h_ = computeHCost();
	f_ = g_ + h_;
	curBoxes_ = parent.getCurBoxes();
}

State::State(World &world) {
	world_ = new World(world.getMap(), world.getInitRobotLocation(), world.getInitBoxes(), world.getTargetBoxes());
	curBoxes_ = *world_->getInitBoxes();
	g_ = computeGCost();
	h_ = computeHCost();
	f_ = g_ + h_;
}

bool State::isGoal(){
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
	// -- No Change Operations --
  if(curRobot_->getX() == 0 // Make sure we cannot go off the map
  	|| map[curRobot_->getY()][curRobot_->getX()-1] != 16 ){ // Make sure we cannot enter an occupied space 
  	expands.push_back(State(*this, LEFT));
  	left = true;
	}
  
  if(curRobot_->getX() == world_->getSizeX()-1
  	|| map[curRobot_->getY()][curRobot_->getX()+1] != 16 ){
  	expands.push_back(State(*this, RIGHT));
  	right = true;
	}

  if(curRobot_->getY() == 0
  	|| map[curRobot_->getY()-1][curRobot_->getX()] != 16 ){
  	expands.push_back(State(*this, UP));
  	up = true;
	}
  
  if(curRobot_->getY() == world_->getSizeY()-1
  	|| map[curRobot_->getY()+1][curRobot_->getX()] != 16 ){
  	expands.push_back(State(*this, DOWN));
  	down = true;
	}

  // -- Push Box--
  if(!left){
  	if(curRobot_->getX() == 1 
  		&& map[curRobot_->getY()][curRobot_->getX()-1] != 16) // We cannot push a box out of the map
  		expands.push_back(State(*this, LEFT));
  	else if(map[curRobot_->getY()][curRobot_->getX()-2] != 16) // We cannot move a box into another occupied space
  		expands.push_back(State(*this, LEFT));
  	else{

  	}
  }
}

/* Display functions */
void State::printState(const string& name){
	cout << "State: " <<  name << endl;
	cout << "G Cost: " << g_ << endl;
	cout << "H Cost: " << h_ << endl;
	cout << "F Cost: " << f_ << endl;
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
  cout << "Cost between: " << endl;
  loc1.print("target");
  loc2.print("current");
  cout << " is " << dX + dY << endl;
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
