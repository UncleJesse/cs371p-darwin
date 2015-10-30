#ifndef Darwin_h
#define Darwin_h

#include <cassert>   // assert
#include <cstddef>   // ptrdiff_t, size_t
#include <stdexcept> // invalid_argument
#include <vector> // vector
#include <string>   // getline, string

#include <iostream> // endl, istream, ostream
#include <sstream>  // istringstream
#include <stdlib.h>     /* srand, rand */



enum direction {north, east, south, west};
enum control {hop, left, right, infect, if_empty, if_wall, if_random, if_enemy, go};

using namespace std;

class Species {

	private:
		vector<string> program;
		char name;
	public:

		void setName(char c);

		void addInstruction(string instruction);

		bool validSpecies();

		string nextInstruction(int pc);

		int numberOfInstructions();

		char getName();
};

class Creature {

	private:
		int _progCounter;
		int _direction;
		Species _species;
		//vector<string> _program;
		// int _x;
		// int _y;
		char name;
		int _numInstructions;
		bool hasRun;
		//Does the creature have to know what specie it is or
		//does it only need to know its program

	public:
		//friend bool Darwin::isWall(int x, int y);

		Creature(Species& species, int dir){
			_direction = dir;
			_species = species;
			//_program = species.program;
			_progCounter = 0;
			name = species.getName();
			_numInstructions = _species.numberOfInstructions();
			hasRun=false;
		}

		char getName();

		//executes the next action command
		string creatureRun(int n, bool runFlag);

		void infect(Creature& creature) const;

		// void hop(){
			
		// }

		bool validCreature();

		int getDirection() const;

		void turnLeft();

		void turnRight();

		bool isEnemy(const Creature& creature)const;

		//Destructor?
};

class Darwin{
	private:
		vector<vector<Creature*> > _grid;
		int _maxX;
		int _maxY;
		bool runFlag;
	public:
		
		//friend bool Creature::hop();

		Darwin(int x,int y){
			_grid.resize(x);
		  	for (int i = 0; i < x; ++i)
		   		_grid[i].resize(y);
			_maxX = x;
			_maxY = y;
			runFlag=false;
			//Check if it null by default
		}

		int instToInt(string str);

		void printDarwin();

		bool isWall(int x, int y);

		bool isEmpty(int x, int y);

		bool addCreature(Creature& creature, int x, int y);

		void runDarwin();
};

#endif 





//Make the Darwin iterator