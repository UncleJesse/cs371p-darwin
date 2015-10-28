#include <cassert>   // assert
#include <cstddef>   // ptrdiff_t, size_t
#include <stdexcept> // invalid_argument
#include <vector> // vector
#include <string>   // getline, string

#include <iostream> // endl, istream, ostream
#include <sstream>  // istringstream
#include <stdlib.h>     /* srand, rand */


using namespace std;

enum direction {north, east, south, west};
enum control {hop, left, right, infect, if_empty, if_wall, if_random, if_enemy, go};

class Species {

	private:
		vector<string> program;
		
	public:

		
	void addInstruction(string instruction){
		program.push_back(instruction);
		return;
	}

	bool validSpecie(){
		return !program.empty();
	}

	string nextInstruction(int pc){
		return program.at(pc);
	}

	int numberOfInstructions(){
		return program.size();
	}
};

class Creature {

	private:
		int _progCounter;
		int _direction;
		Species* _species;
		//vector<string> _program;
		// int _x;
		// int _y;
		int _numInstructions;
		bool hasRun=false;
		//Does the creature have to know what specie it is or
		//does it only need to know its program

	public:
		//friend bool Darwin::isWall(int x, int y);

	Creature(const Species* species, int dir){
		_direction = dir;
		_species = species;
		//_program = species.program;
		_progCounter = 0;
		_numInstructions = *_species.numberOfInstructions();
	}

	//executes the next action command
	string creatureRun(int n) const{
		//execute _species.program.get(_progCounter)
		assert(n<_numInstructions);
		if(runFlag==hasRun){
			return "";
		}

		hasRun=runFlag;

		if(n==-1){
			string instruction = *_species.nextInstruction(_progCounter);
			_progCounter = (_progCounter+1)%_numInstructions;
		} else {
			string instruction = *_species.nextInstruction(_progCounter); 
			_progCounter=n;
		}
	}

	void infect(Creature& creature) const{
		//Check that it has different species
		creature._species = _species;
		creature._progCounter = 0;
		return;
	}

	// void hop(){
		
	// }

	bool validCreature(){
		return *_species.validSpecie();
	}

	int getDirection() const{
		return _direction;
	}

	void turnLeft(){
		_direction= (_direction+1)%4;
	}

	void turnRight(){
		_direction = (_direction+3)%4;
	}

	bool isEnemy(const Creature& creature)const{
		return _species == creature._species;
	}

	//Destructor?
};

class Darwin{
	private:
		vector<vector<Creature*> > _grid;
		int _maxX;
		int _maxY;
		bool runFlag=false;
	public:
		
	//friend bool Creature::hop();

	Darwin(int x,int y){
		_grid.resize(x);
	  	for (int i = 0; i < x; ++i)
	   		_grid[i].resize(y);
		_maxX = x;
		_maxY = y;
		//Check if it null by default
	}

	bool addCreature(Creature* creature, int x, int y){
		//to access x,y
		_grid[x][y] = creature;
		return true;
	}

	void run(){
		//traverses the grid executing run on all creatures
		//If the creature returns an int 0-3 then 
		//Check if it can move in that direction, otherwise call infect 
		//on the new creature
		runFlag = !runFlag;
		for(int i=0;i< _maxX;i++){
			for(int j=0 ;j < _maxY;j++){
				Creature& temp = *_grid[i][j];
				if(temp.validCreature()){
					//execute temp's program at prog counter
					int n=-1;
					string instruction = temp.creatureRun(n);
					int creatureDirection = temp.getDirection();
					bool done=false;

					while(!done && instruction!=""){
						istringstream iss(instruction);
					    //copy(istream_iterator<string>(iss),istream_iterator<string>(),ostream_iterator<string>(cout, "\n"));
						string firstPart;
						string secondPart;
						iss >> firstPart;
						int temp = control.valueOf(firstPart);
						switch (temp){
							case 1: //hop								
								switch(creatureDirection){
									case 0:
										if(isEmpty(i-1,j)){
											_grid[i-1][j] = *temp;
											_grid[i][j] = 0;
											//temp.hop();
											done = true;
											//TODO ask downing about null or 0
										}else{
											done = false;
										}
									break;
									case 1:
										if(isEmpty(i,j-1)){
											_grid[i][j-1] = *temp;
											_grid[i][j] = 0;
											//temp.hop();
											done = true;
											//TODO ask downing about null or 0
										}else{
											done = false;
										}
									break;
									case 2:
										if(isEmpty(i+1,j)){
											_grid[i+1][j] = *temp;
											_grid[i][j] = 0;
											//temp.hop();
											done = true;
											//TODO ask downing about null or 0
										}else{
											done = false;
										}
									break;
									case 3:
										if(isEmpty(i,j+1)){
											_grid[i][j+1] = *temp;
											_grid[i][j] = 0;
											//temp.hop();
											done = true;
											//TODO ask downing about null or 0
										}else{
											done = false;
										}
									break;
								}								
							break;
							case 2: //left
								temp.turnLeft();
							break;
							case 3: //right
								temp.turnRight();
							break;
							case 4: //infect
								case 0:
									if(temp.isEnemy(i-1,j)){
										temp.infect(*_grid[i-1][j]);
										done = true;
									}else{
										done = false;
									}
								break;
								case 1:
									if(temp.isEnemy(i,j-1)){
										temp.infect(*_grid[i][j-1]);
										done = true;
									}else{
										done = false;
									}
								break;
								case 2:
									if(temp.isEnemy(i+1,j)){
										temp.infect(*_grid[i+1][j]);
										done = true;
									}else{
										done = false;
									}
								break;
								case 3:
									if(temp.isEnemy(i,j+1)){
										temp.infect(*_grid[i][j+1]);
										done = true;
									}else{
										done = false;
									}
								break;
							break;
							case 5: //if_empty
								iss >> secondPart;
								//the creature to see one point in the grid
								//access what's in that location
								n = atoi(secondPart.c_str());
								//depending on its direction
								switch(creatureDirection){
									case 0:
										if(isEmpty(i-1,j)){
											 instruction = temp.creatureRun(n);
											//temp.hop();
											done = false;
											//TODO ask downing about null or 0
										}
									break;
									case 1:
										if(isEmpty(i,j-1)){
											 instruction = temp.creatureRun(n);
											//temp.hop();
											done = false;
											//TODO ask downing about null or 0
										}
									break;
									case 2:
										if(isEmpty(i+1,j)){
											 instruction = temp.creatureRun(n);
											//temp.hop();
											done = false;
											//TODO ask downing about null or 0
										}
									break;
									case 3:
										if(isEmpty(i,j+1)){
											 instruction = temp.creatureRun(n);
											//temp.hop();
											done = false;
											//TODO ask downing about null or 0
										}
									break;
							break;
							case 6: //if_wall
								iss >> secondPart;
								n = atoi(secondPart.c_str());
								case 0:
										if(isWall(i-1,j)){
											 instruction = temp.creatureRun(n);
											//temp.hop();
											done = false;
											//TODO ask downing about null or 0
										}
									break;
									case 1:
										if(isWall(i,j-1)){
											 instruction = temp.creatureRun(n);
											//temp.hop();
											done = false;
											//TODO ask downing about null or 0
										}
									break;
									case 2:
										if(isWall(i+1,j)){
											instruction = temp.creatureRun(n);
											//temp.hop();
											done = false;
											//TODO ask downing about null or 0
										}
									break;
									case 3:
										if(isWall(i,j+1)){
											instruction = temp.creatureRun(n);
											//temp.hop();
											done = false;
											//TODO ask downing about null or 0
										}
									break;
							break;
							case 7: //if_random
								iss >> secondPart;
								n = atoi(secondPart.c_str());
								if(rand()%2==0){
									instruction = temp.creatureRun(-1);
								}else{
									instruction = temp.creatureRun(n);
								}
							break;
							case 8: //if_enemy
								iss >> secondPart;
								n = atoi(secondPart.c_str());
								case 0:
									if(temp.isEnemy(i-1,j)){
										instruction = temp.creatureRun(n);
										done = false;
									}
								break;
								case 1:
									if(temp.isEnemy(i,j-1)){
										instruction = temp.creatureRun(n);
										done = false;
									}
								break;
								case 2:
									if(temp.isEnemy(i+1,j)){
										instruction = temp.creatureRun(n);
										done = false;
									}
								break;
								case 3:
									if(temp.isEnemy(i,j+1)){
										instruction = temp.creatureRun(n);
										done = false;
									}
								break;
							break;
							case 9: //go
								iss >> secondPart;
								n = atoi(secondPart.c_str());
								instruction = temp.creatureRun(n);
								done = false;
							break;
							default:
								assert(false);
							break;
						}
					}
					//Check what the instruction is
					//and do the command for that creature
				}
				//_grid[i][j]=*temp;
			}
		}
		return;
	}

	void print(){
		return;
	}

	bool isWall(int x, int y){
		//if (x,y) is an invalid location return false
		return (x<0 || x>=_maxX || y<0 || y >= _maxY);
	}

	bool isEmpty(int x, int y){
		if(_grid[x][y]==0 && !isWall(x,y)){
			return true;
		}
	}

};







//Make the Darwin iterator

