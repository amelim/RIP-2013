#include "state.h"
#include <stdlib.h>

using namespace std;

State::State(){
}

// Copy Constructor
State::State(State *parent) {
	parent_ = parent;
	world_ = parent->getWorld();
	curRobot_ = parent->getRobot();
	curBoxes_ = parent->getCurBoxes();
	commands_ = parent->getCommands();
  commands_.push_back(STAY);
	g_ = computeGCost();
	h_ = computeHCost();
	f_ = g_ + h_;

}
// Initialize a state based upon the individual components
State::State(World &world, int x, int y, vector<Location> &curBoxes, State *parent, Direction newCommand){
  world_ = &world;
  parent_ = parent;
  curBoxes_ = curBoxes;
  curRobot_ = new Location(x,y);
	commands_ = parent->getCommands();
  commands_.push_back(newCommand);
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
	for (int i = 0; i < curBoxes_.size(); i++){
		if(!isAtTargetLocation(curBoxes_.at(i))) {
				return false;
		}
	}
  return true;
}

bool State::isAtTargetLocation(Location loc) {
	for (int i = 0; i < world_->getTargetBoxes()->size(); i++) {
		if(world_->getTargetBoxes()->at(i) == loc) {
			return true;
		}
	}

	return false;
}

bool State::boxLogic(const int i, const Direction dir){
  if(curRobot_->adjacent(curBoxes_[i], dir)){
    // Check to make sure you aren't going to push a box into another
    if(!freeToMove(curBoxes_[i], dir, i)){
      //cout << "not free to move!" << endl;
      return false;
    }
    Location test = curBoxes_[i].push(dir);
    //test.print();
    // Make sure you aren't pushing a box out of bounds
    if(test.getX() < 0 || test.getY() < 0 
        || test.getX() > world_->getSizeX() || test.getY() > world_->getSizeY())
      return false;

    Location pBox = curBoxes_[i].push(dir);
    Matrix map = *world_->getMap();
    if(map[pBox.getX()][pBox.getY()] == 16)
      return false;

    return true;
  } // Robot is adjacent to box i and box i is not adjacent to any other of the boxes
  else
    return false;
}

// If you wish to ignore a box, sent the vector index as ignore, defaults to -1
bool State::freeToMove(Location &loc, const Direction dir, int ignore){
  for(unsigned int j = 0; j < curBoxes_.size(); j++){
    // If any other box is adjacent to the pushed box inthe direction, it's not free!
    if(j != ignore && loc.adjacent(curBoxes_[j], dir))
      return false;
    Location newRobot = curRobot_->push(dir);
    Matrix map = *world_->getMap();
    if(map[newRobot.getX()][newRobot.getY()] == 16)
      return false;
	}
	return true;
}

/*
 * This function returns the possible states from the four different actions (robot up left right down)
 */
vector<State> State::expandState(){

  vector<State> expands;
  vector<Direction> newCommands = commands_;
  Matrix map = *world_->getMap();
  // Flags to ensure we only add one state for each possible action
  bool left = false;
  bool right = false;
  bool up = false;
  bool down = false;
	// -- Edge Conditions -- //
	// Make sure we cannot go off the map
  if(curRobot_->getX() == 0){ 
  	expands.push_back(State(this));
  	left = true;
	}
  // some weird settings regarind sizes here
  if(curRobot_->getX() == world_->getSizeY()-1){
  	expands.push_back(State(this));
  	right = true;
	}

  if(curRobot_->getY() == 0){
  	expands.push_back(State(this));
  	up = true;
	}
  
  if(curRobot_->getY() == world_->getSizeX()-1){
  	expands.push_back(State(this));
  	down = true;
	}
  	
  // -- Push Box-- //
  for(unsigned int i = 0; i < curBoxes_.size(); i++){
    vector<Location> newBoxes = curBoxes_;
    // Check to see if we will push any boxes (i.e. we are adjacent)
    if(!left && boxLogic(i, LEFT)){
      newBoxes[i] = curBoxes_[i].push(LEFT);
	    Location newRob = curRobot_->push(LEFT);
		  State child(*world_, newRob.getX(), newRob.getY(), newBoxes, this, LEFT);
		  expands.push_back(child);
		  left = true;
    }
    if(!right && boxLogic(i, RIGHT)){
      newBoxes[i] = curBoxes_[i].push(RIGHT);
	    Location newRob = curRobot_->push(RIGHT);
		  State child(*world_, newRob.getX(), newRob.getY(), newBoxes, this, RIGHT);
		  expands.push_back(child);
		  right = true;
    }
    if(!up && boxLogic(i, UP)){
      newBoxes[i] = curBoxes_[i].push(UP);
	    Location newRob = curRobot_->push(UP);
		  State child(*world_, newRob.getX(), newRob.getY(), newBoxes, this, UP);
		  expands.push_back(child);
		  up = true;
    }
    if(!down && boxLogic(i, DOWN)){
      newBoxes[i] = curBoxes_[i].push(DOWN);
	    Location newRob = curRobot_->push(DOWN);
		  State child(*world_, newRob.getX(), newRob.getY(), newBoxes, this, DOWN);
		  expands.push_back(child);
		  down = true;
    }
  }

  // -- Free movement logic -- //
  if(!left && freeToMove(*curRobot_, LEFT)){
    Location newRob = curRobot_->push(LEFT);
		State child(*world_, newRob.getX(), newRob.getY(), curBoxes_, this, LEFT);
		expands.push_back(child);
  }


  if(!right && freeToMove(*curRobot_, RIGHT)){
    Location newRob = curRobot_->push(RIGHT);
		State child(*world_, newRob.getX(), newRob.getY(), curBoxes_, this, RIGHT);
		expands.push_back(child);
  }

  if(!up && freeToMove(*curRobot_, UP)){
    Location newRob = curRobot_->push(UP);
		State child(*world_, newRob.getX(), newRob.getY(), curBoxes_, this, UP);
		expands.push_back(child);
  }

  if(!down && freeToMove(*curRobot_, DOWN)){
    Location newRob = curRobot_->push(DOWN);
		State child(*world_, newRob.getX(), newRob.getY(), curBoxes_, this, DOWN);
		expands.push_back(child);
  }

  return expands;
}

/* Display functions */
void State::printState(const string& name){
  //cout << "State ptr: "	 << this << endl;
	//cout << "Parent ptr: " << parent_ << endl;

  int mapSizeX = world_->getSizeX();
  int mapSizeY = world_->getSizeY();

  cout << "mapSizeX: " << mapSizeX << endl;
  cout << "mapSizeY: " << mapSizeY << endl;

  /* Create temporary map for display purposes only */
  Matrix mapTmp;
  Matrix *worldTmp = world_->getMap();
  vector<int> tmp;

  for (int x = 0; x < mapSizeX; x++) {
    tmp.clear();

    for (int y = 0; y < mapSizeY; y++) {
      if(worldTmp->at(y).at(x) == OCCUPIED)
        tmp.push_back(OCCUPIED);
      else
        tmp.push_back(EMPTY);
    }

    mapTmp.push_back(tmp);
  }

  int robotX = curRobot_->getX();
  int robotY = curRobot_->getY();

  cout << "Robot position: " << robotX << " " << robotY << endl;
  /* Add robot location */
  mapTmp.at(robotY).at(robotX) = ROBOT;

  /* Add boxes */
  int i;
  for (i = 0; i < curBoxes_.size(); i++) {
    int boxX = curBoxes_.at(i).getX();
    int boxY = curBoxes_.at(i).getY();

    if(mapTmp.at(boxY).at(boxX) == EMPTY) {
      mapTmp.at(boxY).at(boxX) = BOX;
    } else {
      mapTmp.at(boxY).at(boxX) += BOX;
    }
  }

  for (i = 0; i < world_->getTargetBoxes()->size(); i++) {
    int targetX = world_->getTargetBoxes()->at(i).getX();
    int targetY = world_->getTargetBoxes()->at(i).getY();

    if(mapTmp.at(targetY).at(targetX) == EMPTY) {
      mapTmp.at(targetY).at(targetX) = TARGET;
    } else {
      mapTmp.at(targetY).at(targetX) += TARGET;
    }
  }

  for (int x = 0; x < mapSizeY; x++) {
    for (int y = 0; y < mapSizeX; y++) {
      switch(mapTmp.at(y).at(x)) {
        case EMPTY:     cout << setw(2) << "-"; break;
        case BOX:       cout << setw(2) <<"B"; break;
        case TARGET:    cout << setw(2) <<"T"; break;
        case ROBOT:     cout << setw(2) <<"R"; break;
        case OCCUPIED:    cout << setw(2) <<"#"; break;
        case BOX+TARGET:  cout << setw(2) <<"G"; break;
        default:      cout << setw(2) <<"U"; break;
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

  // Add the number of commands
  //cost += commands_.size();
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
	if (*s1.getRobot() != *s2.getRobot()) {
		//cout << "s1.robot (" << *s1.getRobot() << ") != s2.robot (" << *s2.getRobot() << ")" << endl;
		return false;
	}

	/* Compare box locations */
	std::vector<Location> s1Boxes = s1.getCurBoxes();
	std::vector<Location> s2Boxes = s2.getCurBoxes();

	for(int i = 0; i < s1Boxes.size(); i++) {
		if(s1Boxes.at(i) != s2Boxes.at(i)) {
			//cout << "s1Box " << s1Boxes.at(i) << " != s2Box " << s2Boxes.at(i) << endl;
			return false;
		}
	}

	/* Compare f, g, and h costs */
	//if(s1.getFCost() != s2.getFCost())
		//return false;
	//if(s1.getGCost() != s2.getGCost())
		//return false;
	//if(s1.getHCost() != s2.getHCost())
		//return false;

	///*Compare parent */
	//if(s1.getParent() != s2.getParent())
		//return false;

	return true;
}

bool operator!= (State &s1, State &s2) {
	return !(s1 == s2);
}
