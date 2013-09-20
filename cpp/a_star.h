#ifndef A_STAR_H
#define A_STAR_H


#include "state.h"

#include <iostream>
#include <cstdlib>
#include <queue>		/* For priority queues */
#include <map>			/* For map data structure */
#include <vector>
#include <functional>   /* std::greater for comparison function for priority queue */


/* This class is required to sort the priority queue based on the f-cost of a
 * node */
class StateOrdering {
	public:
		bool operator() (const State &x, const State &y) const {
			return x.getFCost() > y.getFCost();
		}
};

typedef std::priority_queue<int, std::vector<State>, StateOrdering> statePQ;

class AStar{

	private:
		/* Open and closed list for the search */
		statePQ open_;
    std::map<State, int> closed_;

		State root_;			/* Root of the search tree */
		State solutionLeaf_; 	/* State of the world when a solution is found
									Keep this state for reconstructing the solution */
    std::vector<State> solution_;

		int debugLevel_;

	public:
		/* Constructor */
		AStar();
		AStar(State& init);

		/* Destructor */
		~AStar();

		/* Planning functions */
    std::vector<State> solve();

		/* Display functions */
		void printSolution();

		/* Get functions */
		statePQ getOpen();
    std::map<State, int> getClosed();
    std::vector<State> getSolution();

		/*private:*/
    std::vector<State> extractSolution(State* solutionLeaf);

};
#endif
