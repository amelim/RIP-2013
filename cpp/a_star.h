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

class A_Star{
	public:
		/* Planning functions */
		void solve();
		void extract_solution();

		/* Display functions */
		void printSolution();

		/* Get functions */
		statePQ* getOpen();
		map<State, int>* getClosed();
		State* getRoot();
		State* getSolution();

	private:
		/* Open and closed list for the search */
		statePQ open_;
		map<State, int> closed_;

		State* root;			/* Root of the search tree */
		State* solutionLeaf; 	/* State of the world when a solution is found
									Keep this state for reconstructing the solution */

		int debugLevel;
}
