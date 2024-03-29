#include "Darwin.h"

using namespace std;
// Species

void Species::addInstruction(string instruction){
	_program.push_back(instruction);
	return;
}

int Species::instToInt(string str){
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

int Species::executeInstruction(Creature& creature, Darwin& darwin, int x, int y, direction dir, int pc){
	bool done = false;
	
	while(!done){	
		string nextInstruction = _program.at(pc%_program.size());
		istringstream iss(nextInstruction);
		string instruction;
		string secondPart;
		iss >> instruction;
		int inst = instToInt(instruction);
		assert (inst != 0);
		int n=-1;	
		switch (inst){
			case 1: //hop
				darwin.jump(x, y, dir);
				++pc;
				done = true;							
			break;
			case 2: //left
				creature.turnLeft();
				++pc;
				done = true;
			break;
			case 3: //right
				creature.turnRight();
				++pc;
				done = true;
			break;
			case 4: //infect
				darwin.infect(x, y, dir);
				++pc;
				done = true;
			break;
			case 5: //if_empty
				iss >> secondPart;
				n = atoi(secondPart.c_str());
				if (darwin.isEmpty(x, y, dir)){
					pc = n;
				}else{
					++pc;
				}
			break;
			case 6: //if_wall
				iss >> secondPart;
				n = atoi(secondPart.c_str());
				if (darwin.isWall(x, y, dir)){
					pc = n;
				}else{
					++pc;
				}
			break;
			case 7: //if_random
				iss >> secondPart;
				n = atoi(secondPart.c_str());
				if (rand()%2 > 0){
					pc = n;
				}else{
					++pc;
				}
			break;
			case 8: //if_enemy
				iss >> secondPart;
				n = atoi(secondPart.c_str());
				if(darwin.isEnemy(x, y, dir)){
					pc = n;
				}else{
					++pc;
				}
			break;
			case 9: //go
				iss >> secondPart;
				n = atoi(secondPart.c_str());
				pc = n;
			break;
			default:
				assert(false);
			break;
		}
	}
	return pc;
}

// Creature

void Creature::creatureRun(Darwin& darwin, int x, int y){
	_progCounter = _species.executeInstruction(*this, darwin, x, y, _direction, _progCounter);
	++_numRounds;
}

void Creature::infect(Creature& creature) {
	if (!(creature._species == nSpecies) && !(creature._species == _species)){
		creature._species = _species;
		creature._progCounter = 0;
	}
}

void Creature::turnLeft(){
	switch(_direction){
		case north:
			_direction = west;
		break;
		case east:
			_direction = north;
		break;
		case south:
			_direction = east;
		break;
		case west:
			_direction = south;
		break;
	}
}

void Creature::turnRight(){
	switch(_direction){
		case north:
			_direction = east;
		break;
		case east:
			_direction = south;
		break;
		case south:
			_direction = west;
		break;
		case west:
			_direction = north;
		break;
	}
}

bool Creature::current(int n){
	return _numRounds == n;
}

// Darwin

void Darwin::printDarwin(){
	cout<<"Turn = "<<_round-1<<endl;
	cout << " ";
	for (int i=0; i<(_maxY); i++){
		cout << i%10;
	}
	cout <<endl;
	
	for (int j=0; j<(_maxX); j++){
		for (int k=0; k<(_maxY+1); k++){
			if(k%(_maxY+2)==0){
				cout << j%10;
			}else{
				cout << *_creatures[j*_maxY+ k-1];
			}
		}
		cout << endl;
	}
	cout<<endl;
}

bool Darwin::isWall(int x, int y, direction dir)const{
	switch(dir){
		case north:
			if(x-1<0) return true;
		break;
		case east:
			if(y+1>=_maxY) return true;
		break;
		case south:
			if(x+1>=_maxX) return true;
		break;
		case west:
			if(y-1<0) return true;
		break;
	}
	return false;
}

bool Darwin::isEmpty(int x, int y, direction dir)const{
	int newX=x;
	int newY=y;
	switch(dir){
		case north:
			newX-=1;
		break;
		case east:
			newY+=1;
		break;
		case south:
			newX+=1;
		break;
		case west:
			newY-=1;
		break;
	}
	if(isWall(x,y,dir) || !(_creatures[newX*_maxY+newY]==&nCreature)){
		
		return false;
	}
	return true;
}

bool Darwin::isEnemy(int x, int y, direction dir)const{
	int newX=x;
	int newY=y;

	if(!isEmpty(x,y,dir)&&!isWall(x,y,dir)){
		switch(dir){
			case north:
				newX-=1;
			break;
			case east:
				newY+=1;
			break;
			case south:
				newX+=1;
			break;
			case west:
				newY-=1;
			break;
		}

		if(*_creatures[x*_maxY+y] == *_creatures[newX*_maxY+newY]){
			return false;
		}else {
			return true;
		}
	}
	return false;
}

bool Darwin::addCreature(Creature& creature, int x, int y){
	if(x<0 || x>=_maxX || y<0 || y>= _maxY){
		return false;
	}
	for (Darwin_itr it = begin(); it != end(); ++it){
		if(&(**it) == &creature){
			return false;
		}		
	}

	if(!(_creatures[x * _maxY + y] == &nCreature)){
		return false;
	}

	_creatures[x * _maxY + y] = &creature;
	return true;
}

void Darwin::jump(int x, int y, direction dir){
	int newX=x;
	int newY=y;

	if(isEmpty(x,y,dir)&&!isWall(x,y,dir)){
		switch(dir){
			case north:
				newX-=1;
			break;
			case east:
				newY+=1;
			break;
			case south:
				newX+=1;
			break;
			case west:
				newY-=1;
			break;
		}

		_creatures[newX*_maxY+newY] = _creatures[x*_maxY+y];
		_creatures[x*_maxY+y] = &nCreature;

	}
}

void Darwin::infect(int x, int y, direction dir){
	int newX=x;
	int newY=y;

	if(!isEmpty(x,y,dir) && !isWall(x,y,dir)){
		switch(dir){
			case north:
				newX-=1;
			break;
			case east:
				newY+=1;
			break;
			case south:
				newX+=1;
			break;
			case west:
				newY-=1;
			break;
		}

		Creature*& temp = _creatures[x*_maxY+y];
		Creature*& target = _creatures[newX*_maxY+newY];
		temp->infect(*target);
	}
	return;
}

void Darwin::nextRound(){
	int i = 0;
	for (Darwin_itr it = begin(); it != end(); ++it){
		int x = i / _maxY;
		int y = i % _maxY;
		if(!((**it) == nCreature)){
			if(!(**it).current(_round)){
				(**it).creatureRun(*this, x, y);
			}
		}
		++i;
	}
	++_round;
}
