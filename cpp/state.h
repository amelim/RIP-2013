#ifndef STATE_H
#define STATE_H 

/*
 * An instance of a state describes the locations of boxes, goals and current robot location
 */

#include "location.h"
#include "world.h"
#include <vector>

typedef enum {UP, LEFT, DOWN, RIGHT} Direction;

class State{
	private:
		World *world_;				/* Pointer to the static world initialization */
		Location *curRobot_;					/* Current robot location */
    std::vector<Location> curBoxes_;			/* Current box locations on the map */

		State *parent_;						/* Pointer to previous state, if it exists,
											   otherwise NULL. This pointer is required so that
											   we can traverse the search tree back from the goal
											   to extract the solution */

		int g_;		/* Cost to get to current node for A* */
		int h_;		/* Heuristic estimate to goal for this node for A* */
		int f_;		/* Total cost for a node for A* */
	
		Direction lastMove_;

	public:

		/* Constructors */
		State ();
		State (State &parent, Direction dir);	/* For instantiation based on a parent search node */
		State (World &world);					/* For the initial instantiation of a search node, 
												   used to create the root of the search */

		/* Destructor */
		~State(){}

		/* Display functions */
		void printState(const std::string& name = "");
		
		/* A* planning related functions */
    std::vector<State> expandState();

		bool isGoal();
    
    	/* Calculates the distance between */
		int distanceBetween(const Location& loc1, const Location &loc2) const;

		/* Compute various cost functions */
		int computeGCost();
		int computeHCost();
		int computeFCost();

		/* Get functions */
		Location* getRobot() const { return curRobot_; }
		std::vector<Location> getCurBoxes() const { return curBoxes_; }
		int getGCost() const { return g_; }
		int getHCost() const { return h_; }
		int getFCost() const { return f_; }
		Direction getLastMove() { return lastMove_; }
		World* getWorld() const { return world_; }
		State* getParent(){ return parent_; }

		/* Set functions */
		void setGCost(int g);
		void setHCost(int h);
		void setFCost(int f);
		void setParent(const State &parent);

		/* Overloaded operators */
		friend std::ostream& operator<< (std::ostream& stream, const State& state);
		friend bool operator== (State &s1, State &s2);
		friend bool operator!= (State &s1, State &s2);
};
#endif
