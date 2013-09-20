#ifndef A_STAR_H
#define A_STAR_H


#include "state.h"
#include "location.h"

#include <iostream>
#include <cstdlib>
#include <queue>		/* For priority queues */
#include <map>			/* For map data structure */
#include <vector>
#include <algorithm>    // std::reverse
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
		void printOpen();
		void printClosed();

		/* Get functions */
		statePQ getOpen();
    std::vector<State> getClosed();
    std::vector<State> getSolution();

		/*private:*/
	private:
    	std::vector<State> extractSolution(State* solutionLeaf);
		bool isClosed(State* state);

	private:
		/* Open and closed list for the search */
		statePQ open_;
    	//std::map<State, int> closed_;		
											/* NOTE: maps might not work for this application, 
											   since they require constant keys. A State though
											   is not constant and can change. Therefore it is 
											   not suitable as a key for maps */
		std::vector<State> closed_;

		State root_;			/* Root of the search tree */
		State solutionLeaf_; 	/* State of the world when a solution is found
									Keep this state for reconstructing the solution */
    	std::vector<State> solution_;

		int debugLevel_;

};
#endif
