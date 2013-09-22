#ifndef LOCATION_H
#define LOCATION_H

#include <iostream>

typedef enum {UP, LEFT, DOWN, RIGHT} Direction;

class Location{
	public:
		/* Constructor */
		Location() { x_ = 0; y_ = 0;};
		Location(int x, int y) { x_ = x; y_ = y;};

		/* Destructor */
		~Location() {};

		int getX() const { return x_; }
		int getY() const { return y_; }

		void print(const std::string& type="") const { std::cout << type << " x/y: " << x_ << " / " << y_ << std::endl; }

		bool adjacent(const Location& loc, const Direction dir){
			if(dir==LEFT)
				return loc.getX()==x_-1 && loc.getY() == y_;
			else if(dir==RIGHT)
				return loc.getX()==x_+1 && loc.getY() == y_;
			else if(dir==UP)
				return loc.getX()==x_ && loc.getY() == y_-1;
			else // DOWN
				return loc.getX()==x_ && loc.getY() == y_+1;
		}

		friend std::ostream& operator<<(std::ostream& os, const Location& loc) {
			os << loc.getX() << "/" << loc.getY() << std::endl;
			return os; 
		}
		
		friend bool operator== (Location &l1, Location &l2) {
			return l1.getX() == l2.getX() && l1.getY() == l2.getY();
		}

		friend bool operator!= (Location &l1, Location &l2) {
			return !(l1 == l2);
		}

	private:
		int x_;
		int y_;
};
#endif
