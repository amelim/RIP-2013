#ifndef WORLD_H
#define WORLD_H

#include "location.h"
#include <iomanip>
#include <vector>

#define EMPTY 	1
#define BOX		2
#define TARGET 	4
#define ROBOT 	8
#define OCCUPIED 16

typedef std::vector< std::vector<int> > Matrix;

class World{
	public:
		/* Constructors */
		World();
		World(Matrix *map, Location *robot, std::vector<Location> *boxes, std::vector<Location> *targets);

		/* Destructor */
		~World();

		/* Display functions */
		void printWorld() const;
		void printConfig();
		void printAll();

		/* Get functions */
		Matrix* getMap();				
		int getSizeX(); 						/* const keyword, because we don't want to be 
											   			able to change the parameters of the world */
		int getSizeY();
		int getNumberOfBoxes();
		Location* getInitRobotLocation();
		std::vector<Location>* getInitBoxes();
		std::vector<Location>* getTargetBoxes();

		/* Overloaded operators */
		friend bool operator== (World &w1, World &w2);

	private:
		Matrix map_;						/* Initialize a static map */
		Location robot_;						/* Robot location */
		std::vector<Location> boxesStart_;			/* Location of boxes on the map */
		std::vector<Location> boxesTarget_;			/* Location of boxes on the map */

		/* Store the parameters of the world */
		int sizeX_;
		int sizeY_;
		int numberOfBoxes_;
};
#endif
