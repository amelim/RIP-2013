#ifndef A_STAR_H
#define A_STAR_H

#include "state.h"
#include <queue>		/* For priority queues */
#include <map>			/* For map data structure */
#include <vector>
#include <functional>   /* std::greater for comparison function for priority queue */

using namespace std;

typedef std::priority_queue<int, vector<State>, StateOrdering> statePQ;

/* This class is required to sort the priority queue based on the f-cost of a
 * node */
class StateOrdering {
	public:
		bool operator() (const State &x, const State &y) const {
			return x->getFCost() > y->getFCost();
		}
};

class AStar{
	public:
		/* Constructor */
		AStar();
		AStar(State* init);

		/* Destructor */
		~AStar();

		/* Planning functions */
		vector<State> solve();

		/* Display functions */
		void printSolution();

		/* Get functions */
		statePQ getOpen();
		map<State, int> getClosed();
		vector<State> getSolution();

		/*private:*/
		vector<State> extractSolution(State* solutionLeaf);

	private:
		/* Open and closed list for the search */
		statePQ <State, vector<State>, StateOrdering> open_;
		map<State, int> closed_;

		State* root_;			/* Root of the search tree */
		State* solutionLeaf_; 	/* State of the world when a solution is found
									Keep this state for reconstructing the solution */
		vector<State> solution_;

		int debugLevel_;
}
