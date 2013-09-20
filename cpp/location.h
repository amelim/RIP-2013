#ifndef LOCATION_H
#define LOCATION_H

using namespace std;

class Location{
	public:
		/* Constructor */
		Location() { x_ = 0; y_ = 0;};
		Location(int x, int y) { x_ = x; y_ = y;};

		/* Destructor */
		~Location() {};

		int getX() { return x_; }
		int getY() { return y_; }

	private:
		int x_;
		int y_;
};
#endif
