#include <cassert>   // assert
#include <cstddef>   // ptrdiff_t, size_t
#include <stdexcept> // invalid_argument
#include <vector> // vector

enum direction {north, east, south, west};

class Species {
	using namespace std;

	private:
		vector<string> program;
		
	public:

		void addInstruction(string instruction){
			program.push_back(instruction);
			return;
		}
};

class Creature {
	using namespace std;

	private:
		int _progCounter;
		int _direction;
		Species _specie;
		//Does the creature have to know what specie it is or
		//does it only need to know its program

	public:
		Creature(const Species species, int dir=0){
			_direction = dir;
			_species = species;
			_progCounter = 0;
		}

		//executes the next action command
		void run() const{
			//execute _specie.program.get(_progCounter)
			string instruction = _species.program.at(_progCounter);
		    istringstream iss(instruction);
		    //copy(istream_iterator<string>(iss),istream_iterator<string>(),ostream_iterator<string>(cout, "\n"));
			string firstPart;
			string secondPart;
			iss >> firstPart;
			switch (firstPart){
				case "hop":
					this.hop();
				break;
				case "left":
				break;
				case "right":
				break;
				case "infect":
				break;
				case "if_empty":
					iss >> secondPart;
				break;
				case "if_wall":
					iss >> secondPart;
				break;
				case "if_random":
					iss >> secondPart;
				break;
				case "if_enemy":
					iss >> secondPart;
				break;
				case "go":
					iss >> secondPart;
				break;
				default:
				break;
					iss >> secondPart;

			}
			return;
		}

		void infect(Creature& creature) const{
			//Check that it has different specie
			creature._species = _species;
			creature._progCounter = 0;
			return;
		}

		void hop(){
			switch(_direction){
				case 0:

				break;
				case 1:
				break;
				case 2:
				break;
				case 3:
				break;
			}
		}

		//Destructor?
};

class Darwin{
	private:
		Creature _grid[][];
	public:
		Darwin(int x,int y){
			_grid = Creature[x][y];
			//Check if it null by default
			for(int i=0;i<x;i++){
				for(int j=0;j<y;j++){
					_grid[i][j] = NULL;
				}
			}

		}

		bool addCreature(Creature creature, int x, int y){
			_grid[x][y] = creature;
			return true;
		}

		void run(){
			//traverses the grid executing run on all creatures
			//If the creature returns an int 0-3 then 
			//Check if it can move in that direction, otherwise call infect 
			//on the new creature
			return;
		}

		void print(){
			return;
		}
};

//Make the Darwin iterator

