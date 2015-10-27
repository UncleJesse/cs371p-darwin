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


Darwin::Darwin(int x,int y){
	_grid.resize(x);
  	for (int i = 0; i < x; ++i)
   		_grid[i].resize(y);
	_maxX = x;
	_maxY = y;
	//Check if it null by default
}

bool Darwin::addCreature(Creature* creature, int x, int y){
	//to access x,y
	_grid[x][y] = creature;
	return true;
}

void Darwin::run(){
	//traverses the grid executing run on all creatures
	//If the creature returns an int 0-3 then 
	//Check if it can move in that direction, otherwise call infect 
	//on the new creature
	for(int i=0;i< _maxX;i++){
		for(int j=0 ;j < _maxY;j++){
			Creature& temp = *_grid[i][j];
			if(temp.validCreature()){
				//execute temp's program at prog counter
				temp.creatureRun();
			}
			//_grid[i][j]=*temp;
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

Creature::Creature(const Species species, int dir){
	_direction = dir;
	_species = species;
	//_program = species.program;
	_progCounter = 0;
}

//executes the next action command
void Creature::creatureRun() const{
	//execute _species.program.get(_progCounter)
	//string instruction = _species.program.at(_progCounter);
    istringstream iss(instruction);
    //copy(istream_iterator<string>(iss),istream_iterator<string>(),ostream_iterator<string>(cout, "\n"));
	string firstPart;
	string secondPart;
	iss >> firstPart;
	int temp = control.valueOf(firstPart);
	switch (temp){
		case 1: //hop
			this.hop();
		break;
		case 2: //left
		break;
		case 3: //right
		break;
		case 4: //infect
		break;
		case 5: //if_empty
			iss >> secondPart;
			//the creature to see one point in the grid
			//access what's in that location

			//depending on its direction
			bool temp = isWall(x,y);
		break;
		case 6: //if_wall
			iss >> secondPart;
		break;
		case 7: //if_random
			iss >> secondPart;
		break;
		case 8: //if_enemy
			iss >> secondPart;
		break;
		case 9: //go
			iss >> secondPart;
		break;
		default:
		break;
			iss >> secondPart;

	}
	return;
}

void Creature::infect(Creature& creature) const{
	//Check that it has different species
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
	return _species.validSpecie();
}

//Destructor?



//Make the Darwin iterator



int main( int argc, const char* argv[] )
{
	Darwin darwin(8,8);
	/*
	The creatures dont hage enough information to perform 
	their program. They can't see whats around them nor access
	the grid.

	option 1. make the grid a global variable
	option 2. 
	*/
	return 0;
}