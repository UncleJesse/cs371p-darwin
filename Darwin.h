#include <cassert>   // assert
#include <cstddef>   // ptrdiff_t, size_t
#include <stdexcept> // invalid_argument
#include <vector> // vector
#include <string>   // getline, string

#include <iostream> // endl, istream, ostream
#include <sstream>  // istringstream

using namespace std;

enum direction {north, east, south, west};

class Creature {

	private:
		int _progCounter;
		int _direction;
		Species _specie;
		//vector<string> _program;
		int _x;
		int _y;
		//Does the creature have to know what specie it is or
		//does it only need to know its program

	public:
		friend bool Darwin::isWall(int x, int y);

		Creature(const Species species, int dir=0);

		//executes the next action command
		void run() const;

		void infect(Creature& creature) const;

		void hop();

		bool validCreature();

		//Destructor?
};

class Darwin{
	private:
		Creature _grid[][];
		int _maxX;
		int _maxY;
	public:
		Darwin(int x,int y);

		bool addCreature(Creature creature, int x, int y);

		void run();

		bool isWall(int x, int y);
};

class Species {

	private:
		vector<string> program;
		
	public:

		void addInstruction(string instruction);

		bool validSpecie();
};





//Make the Darwin iterator

