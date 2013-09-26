RIP-2013 Project 1 - Andrew Melim, Daniel Pickem, Matheus Svolenski, Jarius Tillman
========
In oder to build this project, the following packages are required.
1) cmake

To build this project, navigate to the root folder and execute the following commands in the terminal.
1) mkdir build
2) cd build
3) cmake ..
4) make

The executables for the program will be found in build/cpp
The input for the main program ./planner is the following:
./planner <inputworld> [<output file>]

At minimum the input world is needed, the solution will be printed to the terminal solely.
If the output file name is given as a parameter, the solution will be saved to this file as well for future reference.


InputWorld
===========
-The input file for the world is expected to contain a 2-D matrix using tabs as horizontal delimeters and newlines as vertical delimeters
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



