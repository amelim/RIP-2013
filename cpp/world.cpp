#include "world.h"

using namespace std;

/* Constructors */
World::World() {}

World::World(Matrix *map, Location *robot, vector<Location> *boxes, vector<Location> *targets) {
	map_ = *map;
	robot_ = *robot;

	boxesStart_ = *boxes;
	boxesTarget_ = *targets;

	if( boxesStart_.size() != boxesTarget_.size()) {
	}

	sizeX_ = map->at(0).size();
	sizeY_ = map->size();
	numberOfBoxes_ = boxes->size();
}

/* Destructors */
World::~World() {

}

/* Display functions */
void World::printWorld() const {
	for (int x = 0; x < map_.at(0).size(); x++) {
		for (int y = 0; y < map_.size(); y++) {
			switch(map_.at(y).at(x)) {
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

void World::printConfig() {
	int i;
	cout << "Size X			: " << sizeX_ << endl;
	cout << "Size Y			: " << sizeY_ << endl;
	cout << "Number Boxes	: " << numberOfBoxes_ << endl;
	cout << "Location Robot : " << robot_;
	cout << "Location Boxes : " << endl;
	
	for (i = 0; i < boxesStart_.size(); i++) {
		cout << boxesStart_.at(i);
	}

	cout << "Location Targets: " << endl;
	
	for (i = 0; i < boxesStart_.size(); i++) {
		cout << boxesTarget_.at(i);
	}
}

void World::printAll() {
	printConfig();
	printWorld();
}

/* Get functions */
Matrix* 	World::getMap() { return &map_; }
int 	World::getSizeX() { return sizeX_; };
int 	World::getSizeY() { return sizeY_; };
int 	World::getNumberOfBoxes() { return numberOfBoxes_ ; };

Location* World::getInitRobotLocation() { return &robot_; }
vector<Location>* World::getInitBoxes() { return &boxesStart_; }
vector<Location>* World::getTargetBoxes() { return &boxesTarget_; }

/* Overloaded operators */
bool operator== (World &w1, World &w2) {
	int i;

	if( w1.getInitRobotLocation() != w2.getInitRobotLocation()) 
		return false;
	
	// TODO: complete this comparison operator 
}
