#ifndef STATE_H
#define STATE_H 

#include "location.h"
#include <queue>
#include <map>
#include <vector>

using namespace std;

class State{
	public:
		/* Constructors */
		State ();
		State (State *parent, Direction dir);	/* For instantiation based on a parent search node */
		State (World *world);					/* For the initial instantiation of a search node, this is for creating the root node of the search tree */

		/* Destructor */
		~State();


		void expand();

	private:
		static World *world_;				/* Pointer to the static world initialization */
		Location curRobot_;					/* Current robot location */
		vector<Location> curBoxes_;			/* Current box locations on the map */

		int g;		/* Cost to get to current node for A* */
		int h;		/* Heuristic estimate to goal for this node for A* */
		int f;		/* Total cost for a node for A* */

		typedef enum {UP, LEFT, DOWN, RIGHT} Direction;
}
