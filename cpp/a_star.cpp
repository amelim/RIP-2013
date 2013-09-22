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
}

/* Destructor */
AStar::~AStar() { }

/* Planning functions */
bool AStar::solve() {
	State tmp;
	int pos;

	/* Initialize closed list (open list initialized in constructor) */
	closed_.clear();

	/* Initialize costs of root node */
	root_.setGCost(0);
	root_.setHCost(root_.computeHCost());
	root_.setFCost(root_.getGCost() + root_.getHCost());

	while(!open_.empty()) {
		/* Retrieve first element of queue and delete from queue */
		tmp = open_.top();
		open_.pop();

		/* Add tmp to closed list */
		closed_.push_back(tmp);

		/* Check if we have found the solution */
		if(tmp.isGoal()) {
			extractSolution(&tmp);
			return true;
		}

		/* Compute neighboring states */
		vector<State> neighbors = tmp.expandState();

		cout << "AStar: " << neighbors.size() << " neighbors found" << endl;
		for (int k = 0; k < neighbors.size(); k++){
			neighbors.at(k).printState();
		}

		if(false) {
		/* Iterate over neighboring states */
		for (int i = 0; i < neighbors.size(); i++) {
			/* Test output of state */
			neighbors.at(i).printState();

			/* Compute tentative g-cost of neighbor 
			 * NOTE: the distance between a neigbhor and tmp is always
			 * 		 one move
			 */
			int tentative_g_score = tmp.getGCost() + 1;

			/* Check if neighbor is already in closed list */
			if(isClosed(&neighbors.at(i), &pos)) {
				/* 1. compute g-cost of neighbor
				 * 2. if g-cost is better than that of the state in the
				 * closed_list, reopen the state (remove from closed, add to
				 * open)
				 */
				if(tentative_g_score < neighbors.at(i).getGCost()) {
					/* Add to open list - i.e. reopen the node */
					open_.push(neighbors.at(i));

					/* Remove from closed list */
					closed_.erase(closed_.begin() + pos);
				} else {
					continue;
				}
			} else {
				/* 1. create new state based on parent tmp
				 * 2. compute f, g, h costs (done in constructor)
				 * 3. add to open_ list
				 */
				open_.push(State(tmp, neighbors.at(i).getLastMove()));

				/* NOTE: technically we should check if the node is already
				 * 		 in the open list, but that's hard to do with a 
				 *		 priority queue. Instead we allow to add duplicates
				 * 		 to the open list and discard them on following iterations
				 * 		 (because they will be in closed list and discarded.
				 */
			}
		}
		}
	}

	/* If the while loop terminates without calling extractSolution, then no
	 * solution has been found */
	cout << "Error AStar: No solution has been found." << endl;
	return false;
}

void AStar::extractSolution(State* solutionLeaf) {
	State* tmp = solutionLeaf;

	while(tmp->getParent() != NULL) {
		solution_.push_back(*tmp);
		tmp = tmp->getParent();
	}

	/* Since the solution goes from goal to initial state, reverse the vector
	 * such that it goes from initial to final state */
	reverse(solution_.begin(), solution_.end());
}

bool AStar::isClosed(State* state, int *pos) {
	for (int i = 0; i < closed_.size(); i++) {
		if(state == &closed_.at(i))
			*pos = i;
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
