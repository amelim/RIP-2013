#ifndef STATE_H
#define STATE_H 

#include "location.h"
#include <vector>

using namespace std;

class State{
	public:
		/* Constructors */
		State ();
		State (State *parent, Direction dir);	/* For instantiation based on a parent search node */
		State (World *world);					/* For the initial instantiation of a search node, 
												   used to create the root of the search */

		/* Destructor */
		~State();

		/* Display functions */
		void printState();
		
		/* A* planning related functions */
		vector<State>* expandState();

		/* Compute various cost functions */
		int computeGCost(State* parent);
		int computeHCost(State* parent);
		int computeFCost(State* parent);

		/* Get functions */
		int getGCost();
		int getHCost();
		int getFCost();
		World* getWorld();
		State* getParent();

		/* Set functions */
		int setGCost();
		int setHCost();
		int setFCost();
		void setParent(State *parent);

	private:
		static World *world_;				/* Pointer to the static world initialization */
		Location curRobot_;					/* Current robot location */
		vector<Location> curBoxes_;			/* Current box locations on the map */

		State *parent_;						/* Pointer to previous state, if it exists,
											   otherwise NULL. This pointer is required so that
											   we can traverse the search tree back from the goal
											   to extract the solution */

		int g;		/* Cost to get to current node for A* */
		int h;		/* Heuristic estimate to goal for this node for A* */
		int f;		/* Total cost for a node for A* */

		typedef enum {UP, LEFT, DOWN, RIGHT} Direction;
}
