#ifndef Darwin_h
#define Darwin_h

#include <cassert>   // assert
#include <vector> // vector
#include <string>   // getline, string
#include <iterator> // iterator
#include <iostream> // endl, istream, ostream
#include <sstream>  // istringstream, ostringstream
#include <stdlib.h>     /* srand, rand */


// enum for keeping track of direction each creature is facing
enum direction {north, east, south, west};

using namespace std;

class Species;
class Creature;
class Darwin;

class Species {

	/** 
	 * Species contain a vector of strings called program, which are the instructions
	 * that the creature should follow and a name to be used to represent creature
	 * on the board/grid
	 */
	private:
		vector<string> program;
		char _name;

	public:
		/** 
		 * default constructor for use to make null species, which is used
		 * to make null creatures to be used to populate the board. Null creatures
		 * are used to represent empty spaces
		 */
		Species(){
			_name='-';
			program.clear();
		}

		/** 
		 * one argument constructor; name is used to represent creature on board/grid
		 */
		Species(char c){
			_name = c;
		}

		/** 
		 * method that takes instructions as strings and adds them to the vector
		 * program in species
		 */
		void addInstruction(string instruction);

		/** 
		 * prints character that represents the creature on the board/grid
		 */
		char renderSpecies();

		/** 
		 * makes the creature turn counterclockwise
		 */
		void turnLeft(direction& dir);

		/** 
		 * makes the creature turn clockwise
		 */
		void turnRight(direction& dir);

		/** 
		 * converts instructions to int for switch statement, each int represents a 
		 * command to be executed by the creature
		 */
		int instToInt(string str);

		/** 
		 * executes the next action command
		 */
		void executeInstruction(Darwin& darwin, int x, int y, direction& dir, int& pc);

		/** 
		 * returns true if species has instructions in its program
		 */
		bool ready();
};

class Creature {

	/** 
	 * each creature has a direction (enum) and a Species, and keeps track of how
	 * many rounds it has taken (numRounds) and how many instructions it has 
	 * executed (progCounter)
	 */
	private:
		direction _direction;
		Species _species;
		int _numRounds;
		Species nSpecies;
		int _progCounter;

	public:
		/** 
		 * default creature constructor for use to make null creatures to populate the
		 * board/grid; sets species to null species
		 */
		Creature(){
			_progCounter=0;
			_direction=north;
			_numRounds=0;
			_species = nSpecies;
		}

		/** 
		 * two argument creature constructor, sets species to the species passed in and 
		 * direction to the direction passed in; sets progCounter and numRounds to 0
		 */
		Creature(Species& species, direction dir){
			_direction = dir;
			_species = species;
			_progCounter = 0;
			_numRounds = 0;
		}

		/** 
		 * method that returns the character used to represent the creature on the board/grid
		 */
		char renderCreature();

		/** 
		 * passes darwin reference and coordinates of the creature to species in order
		 * to execute the next instruction in species.program
		 */
		void creatureRun(Darwin& darwin, int x, int y);

		/** 
		 * method that infects a creature in an adjacent space on the grid if necessary
		 */
		void infect(Creature& creature) const;

		/** 
		 * method that checks if creature is valid, a.k.a. not a null creature
		 */
		bool validCreature();

		/** 
		 * overrides the == operator to compare 2 creatures
		 */
		bool operator == (const Creature& other) {
			return &other._species == &_species;
		}

		/** 
		 * checks to see if creature has taken a turn this round
		 */
		bool current(int n);
};

/** 
 * typedefs declaring our iterator as a Darwin_itr, uses a 
 * std::vector<Creature*> iterator
 */
typedef std::vector<Creature*> Darwin_vector;
typedef std::vector<Creature*>::iterator Darwin_itr;
class Darwin{
	/** 
	 * each darwin object keeps a vector of creature objects that represents
	 * the board/grid; it also keeps track of the dimensions of the entire grid
	 * in maxX and maxY; it keeps iterators pointing to the beginning and end of 
	 * the vector of creatures and there is a null creature (nCreature) object
	 * that is used to represent an empty space, and make spaces empty after a 
	 * creature moves out of that space in Darwin::jump()
	 */
	private:
		Darwin_vector _creatures;
		int _maxX;
		int _maxY;
		int _round;
		Darwin_itr _b;
		Darwin_itr _e;
		Creature nCreature;

	public:
		/** 
		 * two argument constructor of darwin object, sets the dimensions of the 
		 * board/grid, makes every spot empty (nCreature), sets the round number 
		 * to 1, and sets the begin() and end() iterators
		 */
		Darwin(int x,int y){
			_maxX = x;
			_maxY = y;
			_creatures.assign(_maxX * _maxY,&nCreature);
			_b = _creatures.begin();
			_e = _creatures.end();
			_round=1;
		}

		/** 
		 * returns iterator pointing to beginning of _creatures
		 */		
		Darwin_itr begin(){
			return _b;
		}

		/** 
		 * returns iterator pointing to end of _creatures
		 */
		Darwin_itr end(){
			return _e;
		}

		/** 
		 * returns object at indicated coordinates
		 */
		Darwin_itr at(int x, int y){
			return _b + (x * _maxY) + y;
		}

		int size(){
			return (_e - _b);
		}

		/** 
		 * prints board/grid
		 */
		void printDarwin();

		/** 
		 * checks if creature is facing a wall
		 */
		bool isWall(int x, int y, direction dir)const;

		/** 
		 * checks if creature is facing an empty space
		 */
		bool isEmpty(int x, int y, direction dir)const;

		/** 
		 * checks if creature is facing an enemy
		 */
		bool isEnemy(int x, int y, direction dir)const;

		/** 
		 * adds creature to the board/grid at specified coordinates
		 */
		bool addCreature(Creature& creature, int x, int y);

		/** 
		 * moves creature to new location
		 */
		void jump(int x, int y, direction dir);

		/** 
		 * calls creature's infect method to infect the creature it is facing
		 */
		void infect(int x, int y, direction dir);

		/** 
		 * executes the next round, making sure each creature takes a turn
		 */
		void nextRound();
};


#endif 





//Make the Darwin iterator