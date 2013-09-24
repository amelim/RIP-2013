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

	/* Initialize costs of root node */
	root_.setGCost(0);
	root_.setHCost(root_.computeHCost());
	root_.setFCost(root_.getGCost() + root_.getHCost());

	/* Add initial state to queue */
	open_.push(root_);
	openVector_.push_back(root_);
	//closed_.push_back(root_);
}

/* Destructor */
AStar::~AStar() { }

/* Planning functions */
bool AStar::solve() {
	int pos, posi;

	/* Initialize closed list (open list initialized in constructor) */
	closed_.clear();

	while(!open_.empty()) {
	//for (int i = 0; i < 1500; i++) {
		/* Retrieve first element of queue and delete from queue */
		State tmp = open_.top();
		open_.pop();

		/* Keep a copy of the priority queue as a vector, so we can
		 * check if something is already in the open list 
		 */

		//cout << " ############################" << endl;
		//cout << " Printing open before delete " << endl;
		//printOpen();
		//cout << " ############################" << endl;
		isOpen(&tmp, &pos);
		openVector_.erase(openVector_.begin() + pos);
		//cout << " ############################" << endl;
		//cout << " Printing open after delete " << endl;
		//cout << " ############################" << endl;
		//printOpen();
		//cout << " ############################" << endl;

		/* Add tmp to closed list */
		if(!isClosed(&tmp, &pos)) {
			closed_.push_back(tmp);
		}

		/* Check if we have found the solution */
		if(tmp.isGoal()) {
			cout << "AStar::solve(): Solution found" << endl;
			extractSolution(&tmp);
			//printSolution();
			return true;
		}

		/* Compute neighboring states */
		vector<State> neighbors = tmp.expandState();

		//cout << " ###########################" << endl;
		//cout << " Printing closed list " << endl;
		//printClosed();
		//printOpen();
		//cout << " ###########################" << endl;

		cout << "!! Computed " << neighbors.size() << " neighbors !!" << endl;
		/* Iterate over neighboring states */
		for (int i = 0; i < neighbors.size(); i++) {
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
				//if(tentative_g_score < neighbors.at(i).getGCost()) {
					///* Add to open list - i.e. reopen the node */
					//open_.push(neighbors.at(i));

					///* Remove from closed list */
					//closed_.erase(closed_.begin() + pos);
				//} else {
					//continue;
				//}
				continue;
			} else {
				/* 1. create new state based on parent tmp
				 * 2. compute f, g, h costs (done in constructor)
				 * 3. add to open_ list
				 */
				/* Only add to open list, if it was not already in there */
				if(!isOpen(&neighbors.at(i), &posi)) {
					cout << "--- Adding the following neighbor to the open list ---" << endl;
					neighbors.at(i).printState();
					open_.push(neighbors.at(i));
					openVector_.push_back(neighbors.at(i));
				}

				/* NOTE: technically we should check if the node is already
				 * 		 in the open list, but that's hard to do with a 
				 *		 priority queue. Instead we allow to add duplicates
				 * 		 to the open list and discard them on following iterations
				 * 		 (because they will be in closed list and discarded.
				 */
			}
		}
		cout << "--- End neighbor iteration ---" << endl;
	}

	/* If the while loop terminates without calling extractSolution, then no
	 * solution has been found */
	cout << "Error AStar: No solution has been found." << endl;
	return false;
}

void AStar::extractSolution(State* solutionLeaf) {
	State* tmp = solutionLeaf;

	/*while(tmp->getParent() != NULL) {
		tmp->printState();
		solution_.push_back(*tmp);
		tmp = tmp->getParent();
	}*/
	vector<Direction> solution = solutionLeaf->getCommands();
	for(unsigned int i = solution.size()-1; i >=0; i--){
	  cout << "Solution";
	  switch(solution[i]){
      case LEFT: cout << "LEFT";
      case RIGHT: cout << "RIGHT";
      case UP: cout << "UP";
      case DOWN: cout << "DOWN";
      defualt: cout << "STAY";
    }
    cout << "End solution";
  }

	/* Since the solution goes from goal to initial state, reverse the vector
	 * such that it goes from initial to final state */
	reverse(solution_.begin(), solution_.end());
}

bool AStar::isOpen(State* state, int *pos) {
	bool debug = false;

	if(debug) {
		cout << "AStar::isOpen: Size of open list: " << openVector_.size() << endl;
		cout << " Comparint state vs open list element" << endl;
		state->printState();
		cout << "##### vs. ####" << endl;
	}

	for (int i = 0; i < openVector_.size(); i++) {
		if(debug) {
			openVector_.at(i).printState();
		}

		if(*state == openVector_.at(i)) {
			if(debug) {
				cout << "state == openVector_.at(" << i  << ")" << endl;
			}

			*pos = i;
			return true;
		} else {
			if(debug) {
				cout << "state != openVector_.at(" << i  << ")" << endl;
			}
		}
	}

	return false;
}

bool AStar::isClosed(State* state, int *pos) {
	bool debug = false;

	if(debug) {
		cout << "AStar::isClosed: Size of closed list: " << closed_.size() << endl;
		cout << " Comparint state vs open list element" << endl;
		state->printState();
		cout << "##### vs. ####" << endl;
	}

	for (int i = 0; i < closed_.size(); i++) {
		if(debug) {
			closed_.at(i).printState();
		}

		if(*state == closed_.at(i)) {
			if(debug) {
				cout << "state == closed_.at(" << i  << ")" << endl;
			}

			*pos = i;
			return true;
		} else {
			if(debug) {
				cout << "state != closed_.at(" << i  << ")" << endl;
			}
		}
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
	for (int i = 0; i < openVector_.size(); i++) {
		openVector_.at(i).printState();

		for (int j = 0; j < openVector_.at(i).getWorld()->getSizeX() * 2; j++) {
			cout << "#";
		}

		cout << endl;
	}
}

void AStar::printClosed() {
	for (int i = 0; i < closed_.size(); i++) {
		closed_.at(i).printState();

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
