#include "a_star.h"

using namespace std;

/* Constructor */
AStar::AStar() { 
	// TODO: throw error
}

AStar::AStar(State &init) { 
	root_ 			= init;
	//solutionLeaf_ = NULL;
	debugLevel_ = 0;

	/* Add initial state to queue */
	open_.push(root_);
	closed_.push_back(root_);
	closed_.push_back(root_);
}

/* Destructor */
AStar::~AStar() { }

/* Planning functions */
vector<State> AStar::solve() {
	State tmp;

	while(!open_.empty()) {
		/* Retrieve first element of queue and delete from queue */
		tmp = open_.top();
		open_.pop();

		/* Check if we have found the solution */
		if(tmp.isGoal()) {
			return extractSolution(&tmp);
		}

		/* Compute neighboring states */
		vector<State> neighbors = tmp.expandState();

		/* Iterate over neighboring states */
		for (int i = 0; i < neighbors.size(); i++) {
			/* Check if neighbor is already in closed list */
			//if(closed_.find(neighbors.at(i)) != closed_.end()) {
				/* 1. compute f-cost of neighbor
				 * 2. if f-cost is better than that of the state in the
				 * closed_list, reopen the state (remove from closed, add to
				 * open)
				 */
			//	continue;
			//} else {
				/* neighbor is not in closed_ list already */

				/* 1. create new state based on parent
				 * 2. compute f, g, h costs
				 * 3. add to open_ list
				 */
			//}
		}
	}

	/* If the while loop terminates without calling extractSolution, then no
	 * solution has been found */
	//cout << "Error AStar: No solution has been found." << endl;
	//return NULL;
}

vector<State> AStar::extractSolution(State* solutionLeaf) {
	State* tmp = solutionLeaf;

	while(tmp->getParent() != NULL) {
		solution_.push_back(*tmp);
		tmp = tmp->getParent();
	}

	/* Since the solution goes from goal to initial state, reverse the vector
	 * such that it goes from initial to final state */
	reverse(solution_.begin(), solution_.end());
}

bool AStar::isClosed(State* state) {
	for (int i = 0; i < closed_.size(); i++) {
		if(state == &closed_.at(i))
			return true;
	}

	return false;
}

/* Display functions */
void AStar::printSolution() {
	for (int i = 0; i < solution_.size(); i++) {
		cout << solution_.at(i);

		for (int j = 0; j < solution_.at(i).getWorld()->getSizeX() * 2; j++) {
			cout << "#";
		}

		cout << endl;
	}
}

void AStar::printOpen() {
	/* Can't iterate over queue, therefore printing the open list is not 
	 * trivial and would involve creating a copy of the queue */
}

void AStar::printClosed() {
	for (int i = 0; i < closed_.size(); i++) {
		cout << closed_.at(i);

		for (int j = 0; j < closed_.at(i).getWorld()->getSizeX() * 2; j++) {
			cout << "#";
		}

		cout << endl;
	}
}

/* Get functions */
statePQ AStar::getOpen() { return open_; }
std::vector<State> AStar::getClosed() { return closed_; }
vector<State> AStar::getSolution() { return solution_; }
