#include <stdio.h>
#include "Darwin.h"

using namespace std;

#include <cassert>   // assert
#include <cstddef>   // ptrdiff_t, size_t
#include <stdexcept> // invalid_argument
#include <vector> // vector
#include <string>   // getline, string

#include <iostream> // endl, istream, ostream
#include <sstream>  // istringstream

using namespace std;

enum direction {north, east, south, west};

Darwin::Darwin(int x,int y){
	_grid = Creature[x][y];
	_maxX = x;
	_maxY = y;
	//Check if it null by default
	for(int i=0;i<x;i++){
		for(int j=0;j<y;j++){
			_grid[i][j] = NULL;
		}
	}

}

bool Darwin::addCreature(Creature creature, int x, int y){
	_grid[x][y] = creature;
	return true;
}

void Darwin::run(){
	//traverses the grid executing run on all creatures
	//If the creature returns an int 0-3 then 
	//Check if it can move in that direction, otherwise call infect 
	//on the new creature
	for(int i=0;i<_maxX;i++){
		for(int j<0;j<_maxY;j++){
			Creature temp = _grid[i][j];
			if(temp.validCreature()){
				//execute temp's program at prog counter
				temp.run();
			}
		}
	}
	return;
}

void Darwin::print(){
	return;
}

bool Darwin::isWall(int x, int y){
	//if (x,y) is an invalid location return false
	return (x<0 || x>=_maxX || y<0 || y >= _maxY);
}

void Species::addInstruction(string instruction){
	program.push_back(instruction);
	return;
}

bool Species::validSpecie(){
	return !program.empty();
}

friend bool Darwin::isWall(int x, int y);

Creature::Creature(const Species species, int dir=0){
	_direction = dir;
	_species = species;
	//_program = species.program;
	_progCounter = 0;
}

//executes the next action command
void Creature::run() const{
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
			//the creature to see one point in the grid
			//access what's in that location

			//depending on its direction
			bool temp = isWall(x,y);
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

void Creature::infect(Creature& creature) const{
	//Check that it has different specie
	creature._species = _species;
	creature._progCounter = 0;
	return;
}

void Creature::hop(){
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

bool Creature::validCreature(){
	return _specie.validSpecie();
}

//Destructor?



//Make the Darwin iterator



int main( int argc, const char* argv[] )
{
	Darwin darwin(8,8);
	return 0;
}