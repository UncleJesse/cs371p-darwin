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
// #define north=0;
// #define east=1;
// #define south=2;
// #define west=3;

using namespace std;

class Species;
class Creature;
class Darwin;

class Species {

	private:
		vector<string> program;
		char _name;
	public:

		Species(){
			_name='-';
			program.clear();
		}

		Species(char c){
			_name = c;
		}

		void addInstruction(string instruction);

		bool ready();

		string nextInstruction(int pc);

		// int numberOfInstructions();

		char getName();

};

class Creature {

	private:
		int _progCounter;
		direction _direction;
		Species _species;
		int _numRounds;
		Species nSpecies;
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
		Creature(){
			_progCounter=0;
			_direction=north;
			_numRounds=0;
			_species = nSpecies;
		}

		Creature(Species& species, direction dir){
			_direction = dir;
			_species = species;
			//_program = species.program;
			_progCounter = 0;
			//name = species.getName();
			//_numInstructions = _species.numberOfInstructions();
			//hasRun=false;
			_numRounds = 0;
		}

		char renderCreature();

		int instToInt(string str);

		//executes the next action command
		void creatureRun(Darwin& darwin, int x, int y);

		void infect(Creature& creature) const;

		// void hop(){
			
		// }

		bool validCreature();

		int getDirection() const;

		void turnLeft();

		void turnRight();

		bool operator == (const Creature& other) {
			return &other._species == &_species;
		}

		bool current(int n);

		//Destructor?
};

class Darwin{
	private:
		vector<Creature*> _creatures;
		//vector<vector<Creature*> > _grid;
		int _maxX;
		int _maxY;
		int _round;
		vector<Creature*>::iterator _b;
		vector<Creature*>::iterator _e;
		Creature nCreature;

	public:
		
		//friend bool Creature::hop();

		Darwin(int x,int y){
			/*_grid.resize(x);
		  	for (int i = 0; i < x; ++i)
		   		_grid[i].resize(y);*/
			_maxX = x;
			_maxY = y;
			//runFlag=false;
			_creatures.assign(_maxX * _maxY,&nCreature);
			_b = _creatures.begin();
			_e = _creatures.end();
			_round=1;

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
			return _b + (x * _maxY) + y;
		}

		void printDarwin();

		bool isWall(int x, int y, direction dir)const;

		bool isEmpty(int x, int y, direction dir)const;

		bool isEnemy(int x, int y, direction dir)const;

		bool addCreature(Creature& creature, int x, int y);

		void jump(int x, int y, direction dir);

		void infect(int x, int y, direction dir);

		void nextRound();
};


#endif 





//Make the Darwin iterator