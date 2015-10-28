#include <stdio.h>
#include "Darwin.h"

//Make the Darwin iterator
int main()
{
	using namespace std;
	Darwin darwin(8,8);
	Species trap;
	trap.addInstruction("hop");
	Creature c1(trap,2);
	darwin.addCreature(c1,3,3);
	darwin.printDarwin();
	darwin.runDarwin();
	darwin.printDarwin();
	/*
	The creatures dont hage enough information to perform 
	their program. They can't see whats around them nor access
	the grid.

	option 1. make the grid a global variable
	option 2. 
	*/
	return 0;
}

