#ifndef A_STAR_H
#define A_STAR_H

#include "world.h"
#include "location.h"
#include <queue>		/* For priority queues */
#include <map>			/* For map data structure */
#include <vector>
#include <functional>   /* std::greater for comparison function for priority queue */

using namespace std;

typedef std::priority_queue<int,std::vector<Tile>, mycomparison> pq_custom;

class mycomparison {
	bool reverse;

	public:
		mycomparison(const bool& revparam=false) {reverse=revparam;}
		bool operator() (const int& lhs, const int&rhs) const {
			if (reverse) return (lhs>rhs);
			else return (lhs<rhs);
		}
};

class A_Star{
	public:
		void solve();
		void extract_solution();

	private:
		pq_custom open_;
		map<Tile, int> closed_;
}
