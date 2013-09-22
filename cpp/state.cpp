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
	g_ = computeGCost(parent);
	h_ = computeHCost();
	f_ = g_ + h_;
}

State::State(World &world) {
	world_ = new World(world.getMap(), world.getInitRobotLocation(), world.getInitBoxes(), world.getTargetBoxes());
}

// Returns the Manhattan Distance between robot and loc 
int State::distanceToLoc(const Location &loc) const{
  int dX = abs(curRobot_->getX() - loc.getX());
  int dY = abs(curRobot_->getX() - loc.getX());
  return dX + dY;
}

bool State::isGoal(){
  return false;
}

std::vector<State> State::expandState(){

}
/* ---------------------- */
/* Cost functions 		  */
/* ---------------------- */
// Cost from start to current pos
int State::computeGCost(const State &parent) {
	// Get the starting spots
	//vector<Location> inits = world_->getInitBoxes();

}
// Heuristic Cost
int State::computeHCost() {

}
// NOT NEEDED
int State::computeFCost(const State &parent) {}; 	//TODO: implement this function

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
