#ifndef WORLD_H
#define WORLD_H

#include "location.h"
#include <queue>
#include <map>
#include <vector>

using namespace std;

#define EMPTY 	1
#define BOX		2
#define TARGET 	4
#define ROBOT 	8
#define OCCUPIED 16

typedef vector<vector<int>> Matrix;

class World{
	public:
		/* Constructors */
		World();
		World(Matrix *map, Location *robot, vector<Location> *boxes, vector<Location> *targets);

		/* Destructor */
		~World();

		/* Display functions */
		void printWorld();
		void printConfig();
		void printAll();

		/* Get functions */
		Matrix getMap() const;				
		int getSizeX() const; 						/* const keyword, because we don't want to be 
											   			able to change the parameters of the world */
		int getSizeY() const ;
		int getNumberOfBoxes() const;
		Location getInitRobotLocation() const;
		vector<Location> getInitBoxes() const;
		vector<Location> getTargetBoxes() const;

	private:
		static Matrix map_;						/* Initialize a static map */
		Location robot_;						/* Robot location */
		vector<Location> boxesStart_;			/* Location of boxes on the map */
		vector<Location> boxesTarget_;			/* Location of boxes on the map */

		/* Store the parameters of the world */
		int sizeX_;
		int sizeY_;
		int numberOfBoxes_;
}
