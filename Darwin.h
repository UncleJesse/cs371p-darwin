#ifndef Darwin_h
#define Darwin_h

#include <cassert>   // assert
#include <cstddef>   // ptrdiff_t, size_t
#include <stdexcept> // invalid_argument
#include <vector> // vector
#include <string>   // getline, string
#include <iterator> // iterator
#include <iostream> // endl, istream, ostream
#include <sstream>  // istringstream, ostringstream
#include <stdlib.h>     /* srand, rand */



enum direction {north, east, south, west};
enum control {hop, left, right, infect, if_empty, if_wall, if_random, if_enemy, go};

using namespace std;

Class Species;
Class Creature;
Class Darwin;

class Species {

	private:
		vector<string> program;
		char _name;
	public:

		Species(char c){
			_name = c;
		}

		void addInstruction(string instruction);

		bool ready();

		string nextInstruction(int pc);

		int numberOfInstructions();

		char getName();
};

class Creature {

	private:
		int _progCounter;
		direction _direction;
		Species _species;
		int numRounds;
		//vector<string> _program;
		// int _x;
		// int _y;
		//char name;
		//int _numInstructions;
		//bool hasRun;
		//Does the creature have to know what specie it is or
		//does it only need to know its program

	public:
		//friend bool Darwin::isWall(int x, int y);

		Creature(Species& species, int dir){
			_direction = dir;
			_species = species;
			//_program = species.program;
			_progCounter = 0;
			//name = species.getName();
			//_numInstructions = _species.numberOfInstructions();
			//hasRun=false;
			numRounds = 0;
		}

		char renderCreature();

		int instToInt(string str);

		//executes the next action command
		void creatureRun(int n, bool runFlag);

		void infect(Creature& creature) const;

		// void hop(){
			
		// }

		bool validCreature();

		int getDirection() const;

		void turnLeft();

		void turnRight();

		bool operator == (const Creature& other) const;

		bool current(int n);

		//Destructor?
};

class Darwin{
	private:
		vector<Creature*> _creatures;
		//vector<vector<Creature*> > _grid;
		const int _maxX;
		const int _maxY;
		int _round;
		vector<Creature*>::iterator _b;
		vector<Creature*>::iterator _e;

	public:
		
		//friend bool Creature::hop();

		Darwin(int x,int y){
			/*_grid.resize(x);
		  	for (int i = 0; i < x; ++i)
		   		_grid[i].resize(y);*/
			_maxX = x;
			_maxY = y;
			runFlag=false;
			_creatures.resize(_maxX * _maxY);
			_b = _creatures.begin();
			_e = _creatures.end();
			//it = _grid[0][0];
			//Check if it null by default
		}		

		vector<Creature*>::iterator begin(){
			return _b;
		}

		vector<Creature*>::iterator end(){
			return _e;
		}

		vector<Creature*>::iterator at(int x, int y){
			return _b + (x * _maxX) + y;
		}

		void printDarwin();

		bool isWall(int x, int y, direction d);

		bool isEmpty(int x, int y, direction d);

		bool isEnemy(const Creature& creature)const;

		bool addCreature(int x, int y, direction d);

		void nextRound();
};


#endif 





//Make the Darwin iterator