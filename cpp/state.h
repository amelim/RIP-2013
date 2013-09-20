#ifndef STATE_H
#define STATE_H 

<<<<<<< HEAD
#include "location.h"
#include "world.h"
#include <vector>

/*
 * An instance of a state describes the locations of boxes, goals and current robot location
 */
=======
#include "world.h"
#include <vector>

using namespace std;

typedef enum {UP, LEFT, DOWN, RIGHT} Direction;

>>>>>>> f4f2e0aab237b0f13c3e80fb9399be1e0cb13711
class State{
	private:
		static World &world_;				/* Pointer to the static world initialization */
		Location curRobot_;					/* Current robot location */
    std::vector<Location> curBoxes_;			/* Current box locations on the map */

		State &parent_;						/* Pointer to previous state, if it exists,
											   otherwise NULL. This pointer is required so that
											   we can traverse the search tree back from the goal
											   to extract the solution */

		int g_;		/* Cost to get to current node for A* */
		int h_;		/* Heuristic estimate to goal for this node for A* */
		int f_;		/* Total cost for a node for A* */

		typedef enum {UP, LEFT, DOWN, RIGHT} Direction;

	public:
		/* Constructors */
		State ();
		State (State &parent, Direction dir);	/* For instantiation based on a parent search node */
		State (World &world);					/* For the initial instantiation of a search node, 
												   used to create the root of the search */

		/* Destructor */
		~State();

		/* Display functions */
		void printState();
		
		/* A* planning related functions */
    std::vector<State> expandState();
		bool isGoal();
    
    /* Calculates the distance between */
		double distanceToGoal();

		/* Compute various cost functions */
		int computeGCost(const State &parent);
		int computeHCost(const State &parent);
		int computeFCost(const State &parent);

		/* Get functions */
		int getGCost(){ return g_; }
		int getHCost(){ return h_; }
		int getFCost(){ return f_; }
		World* getWorld();
		State* getParent();

		/* Set functions */
		int setGCost();
		int setHCost();
		int setFCost();
		void setParent(const State &parent);

<<<<<<< HEAD
}
=======
		int g;		/* Cost to get to current node for A* */
		int h;		/* Heuristic estimate to goal for this node for A* */
		int f;		/* Total cost for a node for A* */
};
#endif
>>>>>>> f4f2e0aab237b0f13c3e80fb9399be1e0cb13711
