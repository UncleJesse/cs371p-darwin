#include "Darwin.h"

// Species

void Species::setName(char c){
	name =c;
}

void Species::addInstruction(string instruction){
	program.push_back(instruction);
	return;
}

bool Species::validSpecies(){
	return !program.empty();
}

string Species::nextInstruction(int pc){
	return program.at(pc % program.size());
}

int Species::numberOfInstructions(){
	return program.size();
}

char Species::getName(){
	return name;
}

// Creature

char Creature::getName(){
		return name;
	}

//executes the next action command
string Creature::creatureRun(int n, bool runFlag){
	//execute _species.program.get(_progCounter)
	assert(n<_numInstructions);
	if(runFlag==hasRun){
		return "";
	}

	hasRun=runFlag;
	string instruction;
	if(n==-1){
		cout << "GGGGG "<<endl;
		instruction = _species.nextInstruction(_progCounter);
		cout << instruction <<endl;
		//_progCounter = (_progCounter+1)%_numInstructions;
	} else {
		instruction = _species.nextInstruction(_progCounter); 
		_progCounter=n;
	}
	return instruction;
}

void Creature::infect(Creature& creature) const{
	//Check that it has different species
	creature._species = _species;
	creature._progCounter = 0;
	return;
}

// void hop(){
	
// }

bool Creature::validCreature(){
	return _species.validSpecies();
}

int Creature::getDirection() const{
	return _direction;
}

void Creature::turnLeft(){
	_direction= (_direction+1)%4;
}

void Creature::turnRight(){
	_direction = (_direction+3)%4;
}

bool Creature::isEnemy(const Creature& creature)const{
	return &_species == &creature._species;
}

// Darwin

Creature& Darwin::begin(){
	return _grid.begin();
}

Creature& Darwin::end(){
	return _grid.end();
}

Creature& Darwin::at(int x, int y){
	return _grid[x][y];
}

int Darwin::instToInt(string str){
	if(str.compare("hop")==0){
		return 1;
	}
	if(str.compare("left")==0){
		return 2;
	}
	if(str.compare("right")==0){
		return 3;
	}
	if(str.compare("infect")==0){
		return 4;
	}
	if(str.compare("if_empty")==0){
		return 5;
	}
	if(str.compare("if_wall")==0){
		return 6;
	}
	if(str.compare("if_random")==0){
		return 7;
	}
	if(str.compare("if_enemy")==0){
		return 8;
	}
	if(str.compare("go")==0){
		return 9;
	}
	return 0;
}


void Darwin::printDarwin(){
	for(int i=0;i<_maxX;i++){
		for(int j=0;j<_maxY;j++){
			if(isEmpty(i,j)){
				cout << "- ";
			}else{
				Creature temp = *_grid[i][j];
				cout<< temp.getName()<< " ";
			}
		}
		cout << endl;
	}
	return;
}

bool Darwin::isWall(int x, int y){
	//if (x,y) is an invalid location return false
	return (x<0 || x>=_maxX || y<0 || y >= _maxY);
}

bool Darwin::isEmpty(int x, int y){
	if(_grid[x][y]==0 && !isWall(x,y)){
		return true;
	}
	return false;
}

bool Darwin::addCreature(Creature& creature, int x, int y){
	//to access x,y
	cout<< "AAAA " << &creature << endl;
	_grid[x][y] = &creature;
	return true;
}

void Darwin::runDarwin(){
	//traverses the grid executing run on all creatures
	//If the creature returns an int 0-3 then 
	//Check if it can move in that direction, otherwise call infect 
	//on the new creature
	cout << "BBBBBB " <<endl;
	runFlag = !runFlag;
	for(int i=0;i< _maxX;i++){
		for(int j=0 ;j < _maxY;j++){
			cout<< "CCCCC "<<endl;
			if(_grid[i][j]==0){
				break;
			}

			Creature& temp = *_grid[i][j];
			cout << "DDDDD " <<endl;
			if(temp.validCreature()){
				cout << "EEEEE" <<endl;
				//execute temp's program at prog counter
				int n=-1;
				string instruction = temp.creatureRun(n,runFlag);
				//cout << instruction <<endl;
				int creatureDirection = temp.getDirection();
				bool done=false;
				cout << "instruction " << instruction <<endl;
				while(!done && instruction.compare("")==0){
					istringstream iss(instruction);
				    //copy(istream_iterator<string>(iss),istream_iterator<string>(),ostream_iterator<string>(cout, "\n"));
					string firstPart;
					string secondPart;
					iss >> firstPart;
					int inst = instToInt(firstPart);
					assert(inst != 0);
					switch (inst){
						case 1: //hop								
							switch(creatureDirection){
								case 0:
									if(isEmpty(i-1,j)){
										_grid[i-1][j] = &temp;
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
										_grid[i][j-1] = &temp;
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
										_grid[i+1][j] = &temp;
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
										_grid[i][j+1] = &temp;
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
							switch(creatureDirection){
								case 0:
									if(temp.isEnemy(*_grid[i-1][j])){
										temp.infect(*_grid[i-1][j]);
										done = true;
									}else{
										done = false;
									}
								break;
								case 1:
									if(temp.isEnemy(*_grid[i][j-1])){
										temp.infect(*_grid[i][j-1]);
										done = true;
									}else{
										done = false;
									}
								break;
								case 2:
									if(temp.isEnemy(*_grid[i+1][j])){
										temp.infect(*_grid[i+1][j]);
										done = true;
									}else{
										done = false;
									}
								break;
								case 3:
									if(temp.isEnemy(*_grid[i][j+1])){
										temp.infect(*_grid[i][j+1]);
										done = true;
									}else{
										done = false;
									}
								break;
							}
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
										 instruction = temp.creatureRun(n,runFlag);
										//temp.hop();
										done = false;
										//TODO ask downing about null or 0
									}
								break;
								case 1:
									if(isEmpty(i,j-1)){
										 instruction = temp.creatureRun(n,runFlag);
										//temp.hop();
										done = false;
										//TODO ask downing about null or 0
									}
								break;
								case 2:
									if(isEmpty(i+1,j)){
										 instruction = temp.creatureRun(n,runFlag);
										//temp.hop();
										done = false;
										//TODO ask downing about null or 0
									}
								break;
								case 3:
									if(isEmpty(i,j+1)){
										 instruction = temp.creatureRun(n,runFlag);
										//temp.hop();
										done = false;
										//TODO ask downing about null or 0
									}
								break;
							}
						break;
						case 6: //if_wall
							iss >> secondPart;
							n = atoi(secondPart.c_str());
							switch(creatureDirection){
								case 0:
									if(isWall(i-1,j)){
										 instruction = temp.creatureRun(n,runFlag);
										//temp.hop();
										done = false;
										//TODO ask downing about null or 0
									}
								break;
								case 1:
									if(isWall(i,j-1)){
										 instruction = temp.creatureRun(n,runFlag);
										//temp.hop();
										done = false;
										//TODO ask downing about null or 0
									}
								break;
								case 2:
									if(isWall(i+1,j)){
										instruction = temp.creatureRun(n,runFlag);
										//temp.hop();
										done = false;
										//TODO ask downing about null or 0
									}
								break;
								case 3:
									if(isWall(i,j+1)){
										instruction = temp.creatureRun(n,runFlag);
										//temp.hop();
										done = false;
										//TODO ask downing about null or 0
									}
								break;
							}
						break;
						case 7: //if_random
							iss >> secondPart;
							n = atoi(secondPart.c_str());
							if(rand()%2==0){
								instruction = temp.creatureRun(-1,runFlag);
							}else{
								instruction = temp.creatureRun(n,runFlag);
							}
						break;
						case 8: //if_enemy
							iss >> secondPart;
							n = atoi(secondPart.c_str());
							switch(creatureDirection){
								case 0:
									if(temp.isEnemy(*_grid[i-1][j])){
										instruction = temp.creatureRun(n,runFlag);
										done = false;
									}
								break;
								case 1:
									if(temp.isEnemy(*_grid[i][j-1])){
										instruction = temp.creatureRun(n,runFlag);
										done = false;
									}
								break;
								case 2:
									if(temp.isEnemy(*_grid[i+1][j])){
										instruction = temp.creatureRun(n,runFlag);
										done = false;
									}
								break;
								case 3:
									if(temp.isEnemy(*_grid[i][j+1])){
										instruction = temp.creatureRun(n,runFlag);
										done = false;
									}
								break;
							}
						break;
						case 9: //go
							iss >> secondPart;
							n = atoi(secondPart.c_str());
							instruction = temp.creatureRun(n,runFlag);
							done = false;
						break;
						default:
							assert(false);
						break;
					}
				}
			}
		}
	}
	return;
}