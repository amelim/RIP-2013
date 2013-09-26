RIP-2013 Project 1 - Andrew Melim, Daniel Pickem, Matheus Svolenski, Jarius Tillman
========
In order to build this project, the following packages are required.
1) cmake

To build this project, navigate to the root folder and execute the following commands in the terminal.
1) mkdir build
2) cd build
3) cmake ..
4) make

The executables for the program will be found in build/cpp
The input for the main program ./testState

The name for the inputworld should be coded into testState.cpp in the cpp/scripts directory.

Example input files can be found in the problems directory.

InputWorld
===========
-The input file for the world is expected to contain a 2-D matrix using spaces as horizontal delimiters and newlines as vertical delimiters
-The top line for the world contains the dimensions
-The world is composed of integer values which use bit flipping to determine the property of the world

-For each flipped bit, that location has a specific characteristic.

-The number created for a specific matrix index is the sum of the individual property values.

	(0)-1 		-> Empty
	--Currently unoccupied location
	(1)-2 		-> Box Location
	--Currently has a movable box
	(2)-4 		-> Target Location
	--Box will be at this location in final state
	(3)-8 		-> Robot
	--Robot is at this location
	(4)-16		-> Occupied
	--Has an immovable object(e.g. wall)



