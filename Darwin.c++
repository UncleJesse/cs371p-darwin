#include "Darwin.h"

using namespace std;
// Species

/*void Species::setName(char c){
	name =c;
}*/

void Species::addInstruction(string instruction){
	program.push_back(instruction);
	return;
}

bool Species::ready(){
	return !program.empty();
}

string Species::nextInstruction(int pc){
	return program.at(pc % program.size());
}

// int Species::numberOfInstructions(){
// 	return program.size();
// }

char Species::getName(){
	return _name;
}

// Creature

char Creature::renderCreature(){
		return _species.getName();
}

int Creature::instToInt(string str){
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

//executes the next action command
void Creature::creatureRun(Darwin& darwin, int x, int y/*int n, bool runFlag*/){
	//execute _species.program.get(_progCounter)
	/*assert(n<_numInstructions);
	if(runFlag==hasRun){
		return "";
	}*/

	//hasRun=runFlag;
	bool done = false;
	
	while(!done){	
		string nextInstruction = _species.nextInstruction(_progCounter);
		istringstream iss(nextInstruction);
		string instruction;
		string secondPart;
		iss >> instruction;
		int inst = instToInt(instruction);
		assert (inst != 0);
		int n=-1;

		//cout<<inst<<" "<<n<<endl;	
		// cout<<"Creature "<<x<<" "<<y<<" Round: "<<_numRounds<<endl;		
		switch (inst){
			case 1: //hop
				darwin.jump(x, y, _direction);
				++_progCounter;

				done = true;							
			break;
			case 2: //left
				turnLeft();
				++_progCounter;
				done = true;
			break;
			case 3: //right
				turnRight();
				++_progCounter;
				done = true;
			break;
			case 4: //infect
				darwin.infect(x, y, _direction);
				++_progCounter;
				done = true;
			break;
			case 5: //if_empty
				iss >> secondPart;
				n = atoi(secondPart.c_str());
				//iss >> secondPart;
				//the creature to see one point in the grid
				//access what's in that location
				//n = atoi(secondPart.c_str());
				//depending on its direction
				if (darwin.isEmpty(x, y, _direction)){
					_progCounter = n;
				}else{
					++_progCounter;
				}
			break;
			case 6: //if_wall
				iss >> secondPart;
				n = atoi(secondPart.c_str());
				if (darwin.isWall(x, y, _direction)){
					_progCounter = n;
				}else{
					++_progCounter;
				}				
			break;
			case 7: //if_random
				iss >> secondPart;
				n = atoi(secondPart.c_str());
				if (rand()%2 > 0){
					_progCounter = n;
				}else{
					++_progCounter;
				}
			break;
			case 8: //if_enemy
				iss >> secondPart;
				n = atoi(secondPart.c_str());
				if(darwin.isEnemy(x, y, _direction)){
					_progCounter = n;
				}else{
					++_progCounter;
				}
			break;
			case 9: //go
				iss >> secondPart;
				n = atoi(secondPart.c_str());
				_progCounter = n;
			break;
			default:
				assert(false);
			break;
		}
	}
	++_numRounds;
	/*if(n==-1){
		instruction = _species.nextInstruction(_progCounter);
		cout << instruction <<endl;
		//_progCounter = (_progCounter+1)%_numInstructions;
	} else {
		instruction = _species.nextInstruction(_progCounter); 
		_progCounter=n;
	}*/
}

void Creature::infect(Creature& creature) const{
	//Check that it has different species
	if (!(&creature._species == &nSpecies) && !(&creature._species == &_species)){
		creature._species = _species;
		creature._progCounter = 0;
	}
	//return;
}

// void hop(){
	
// }

bool Creature::validCreature(){
	return _species.ready();
}

int Creature::getDirection() const{
	return _direction;
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
	//cout<<"creature at: "<<_x", "<<_y<<endl;
	//cout<<"numR: "<<_numRounds<<" n: "<<n<<endl;
	return _numRounds == n;
}

// Darwin

void Darwin::printDarwin(){
	cout<<"Turn = "<<_round-1<<endl;
	cout << "  ";
	for (int i=0; i<(_maxY); i++){
		cout << i%10 << " ";
	}
	cout <<endl;
	
	for (int j=0; j<(_maxX); j++){
		for (int k=0; k<(_maxY+1); k++){
			if(k%(_maxY+2)==0){
				cout << j%10 << " ";
			}else{
				
				//cout << _creatures[0]->renderCreature() <<endl;
				//cout <<"J: "<<j<<", k: "<<k<<endl;
				cout << _creatures[j*_maxY+ k-1]->renderCreature() << " ";
				//cout <<"AAAA"<<endl;
			}
		}
		cout << endl;
	}
	cout<<endl;
}

bool Darwin::isWall(int x, int y, direction dir)const{
	switch(dir){
		//cout<<"ISWALL X:"<<x<<" Y: "<<y<<" dir: "<<dir<<endl;
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
	//if (x,y) is an invalid location return false
	//return (x<0 || x>=_maxX || y<0 || y >= _maxY);
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
	//cout<<"creature: "<<x<<", "<<y<<" "<<_creatures[newX*_maxY+newY]<<" nC: "<<&nCreature<<endl;
	if(isWall(x,y,dir) || (_creatures[newX*_maxY+newY]!=&nCreature)){
		return false;
	}
	//cout<<"BBBBB"<<endl;
	return true;
	/*if(_creatures[] && !isWall(x,y)){
		return true;
	}
	return false;*/
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
	//return &_species == &creature._species;
}

bool Darwin::addCreature(Creature& creature, int x, int y){
	_creatures[x * _maxY + y] = &creature;
	return true;
}

void Darwin::jump(int x, int y, direction dir){
	int newX=x;
	int newY=y;
	// cout<<"JUMP ROUND: "<<_round<<endl;

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
		
		// Creature*& newC = _creatures.at(newX*_maxY+newY);
		// Creature*& oldC = _creatures.at(x*_maxY+y);
		// cout<<"old: "<<x<<", "<<y<<" " << oldC->renderCreature() << endl;
		// cout<<"new: "<<newX<<", "<<newY<<" " << newC->renderCreature() << endl;
		// cout<<"nC: "<<nCreature.renderCreature() << endl;
		// *newC = *oldC;
		// oldC = &nCreature;
		// cout<<"old: "<<x<<", "<<y<<" " << oldC->renderCreature() << endl;
		// cout<<"new: "<<newX<<", "<<newY<<" " << newC->renderCreature() << endl;
		// cout<<"nC: "<<nCreature.renderCreature() << endl;

		_creatures[newX*_maxY+newY] = _creatures[x*_maxY+y];
		_creatures[x*_maxY+y] = &nCreature;
		// cout<<"old: "<<x<<", "<<y<<" " <<  _creatures.at(x*_maxY+y)->renderCreature() << endl;
		// cout<<"new: "<<newX<<", "<<newY<<" " << _creatures.at(newX*_maxY+newY)->renderCreature() << endl;
		// cout<<"nC: "<<nCreature.renderCreature() << endl;

	}
	//printDarwin();
	return;
}

void Darwin::infect(int x, int y, direction dir){
	int newX=x;
	int newY=y;

	if(!isEmpty(x,y,dir) && !isWall(x,y,dir)){
		//cout<<"AAAA "<<x<<", "<<y<<endl;
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
	//traverses the grid executing run on all creatures
	//If the creature returns an int 0-3 then 
	//Check if it can move in that direction, otherwise call infect 
	//on the new creature
	//cout << "BBBBBB " <<endl;
	//runFlag = !runFlag;
	
	for(int i=0; i<(_maxX * _maxY); i++){
		//cout<< "CCCCC "<<endl;
		int x = i / _maxY;
		int y = i % _maxY;
		if(_creatures[i]==0){
			break;
		}
		Creature& next = *_creatures[i];
		//cout << "DDDDD " <<endl;
		//cout<<"Creature[i]: "<<i<<" "<<next.renderCreature()<<endl;
		if(!(next==nCreature)){
			if(!next.current(_round)){
				next.creatureRun(*this, x, y);
			}
			//cout << "EEEEE" <<endl;
			//execute temp's program at prog counter
			/*int n=-1;
			string instruction = temp.creatureRun(n,runFlag);
			cout << instruction <<endl;
			int creatureDirection = temp.getDirection();
			bool done=false;
			cout << "instruction " << instruction <<endl;*/
			
		}
	}
	++_round;
	return;
}






/*switch(creatureDirection){
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

	case 5: //if_empty
				//iss >> secondPart;
				//the creature to see one point in the grid
				//access what's in that location
				//n = atoi(secondPart.c_str());
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
			*/