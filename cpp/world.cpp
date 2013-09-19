#include "world.h"

using namespace std;

/* Constructors */
World::World() {
	// TODO: throw error
}

World::World(Matrix *map, Location *robot, vector<Location> *boxes, vector<Location> *targets) {
	map_ = &map;
	robot_ = &robot;

	boxesStart_ = &boxes;
	boxesTarget_ = &targets;

	if( boxesStart_ != boxesTarget_) {
		// TODO: throw error
	}
	
	sizeX_ = map->at(0).size();
	sizeY_ = map->size();
	numberOfTargets_ = boxes->size();
}

/* Destructors */
World::~World() {

}

/* Display functions */
void World::printWorld() {
	for (int x = 0; x < map_.at(0).size(); x++) {
		for (int y = 0; y < map_.size(); y++) {
			switch(map.at(y).at(x)) {
				case EMPTY: 	cout << "-"; break;
				case BOX: 		cout << "B"; break;
				case TARGET: 	cout << "x"; break;
				case ROBOT: 	cout << "R"; break;
				case OCCUPIED: 	cout << "O"; break;
				case default: 	break;
			}
		}

	}
}

void World::printConfig() {
	int i;
	cout << "Size X			: " << sizeX_ << endl;
	cout << "Size Y			: " << sizeY_ << endl;
	cout << "Number Boxes	: " << numberOfBoxes_ << endl;
	cout << "Location Robot : " << robot_.getX() << " / " robot_.getY() << endl;
	cout << "Location Boxes : " << endl;
	
	for (i = 0; i < boxesStart_.size(); i++) {
		cout << boxesStart_.at(i).getX() << " / " boxesStart_.at(i).getY() << endl;
	}

	cout << "Location Targets: " << endl;
	
	for (i = 0; i < boxesStart_.size(); i++) {
		cout << boxesTarget_.at(i).getX() << " / " boxesTarget_.at(i).getY() << endl;
	}
}

void World::printAll() {
	printConfig();
	printWorld();
}

/* Get functions */
Matrix 	World::getMap() { return map_; }
int 	World::getSizeX() { return sizeX_; };
int 	World::getSizeY() { return sizeY_; };
int 	World::getNumberOfBoxes() { return numberOfBoxes_ ; };

Location World::getInitRobotLocation() { return robot_; }
vector<Location> World::getInitBoxes() { return boxesStart_; }
vector<Location> World::getTargetBoxes() { return boxesTarget_; }
