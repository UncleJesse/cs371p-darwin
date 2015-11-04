#define private public

#include "gtest/gtest.h"
#include "Darwin.h"
#include <stdexcept>

using namespace std;

TEST(Test_Species, addInstruction1) {
    Species x('x');
    x.addInstruction("hop");
    string s = x._program[0];
    ASSERT_TRUE(s.compare("hop") == 0);
}

TEST(Test_Species, addInstruction2) {
    Species x('x');
    x.addInstruction("hop");
    x.addInstruction("go 1");
    x.addInstruction("left");
    x.addInstruction("if_wall 2");
    string s = x._program[1];
    ASSERT_EQ(s,"go 1");
}

TEST(Test_Species, addInstruction3) {
    Species x('x');
    x.addInstruction("if_empty 1");
    x.addInstruction("hop");
    int i = x._program.size();
    ASSERT_EQ(i, 2);
}

/*TEST(Test_Species, renderSpecies1) {
    Species x('x');
    char c = x.renderSpecies();
    ASSERT_EQ(c,'x');
}

TEST(Test_Species, renderSpecies2) {
    Species y('y');
    ASSERT_EQ(y.renderSpecies(),'y');
}

TEST(Test_Species, renderSpecies3) {
    Species x('x');
    Species y('y');
    x = y;
    char c = x.renderSpecies();
    ASSERT_EQ(c,'y');
}*/

TEST(Test_Species, instToInt1) {
    Species y('y');
    int i = y.instToInt("go");
    ASSERT_EQ(i, 9);
}

TEST(Test_Species, instToInt2) {
    Species y('y');
    int i = y.instToInt("infect");
    ASSERT_EQ(i, 4);
}

TEST(Test_Species, instToInt3) {
    Species y('y');
    int i = y.instToInt("if_random");
    ASSERT_EQ(i, 7);
}

TEST(Test_Species, executeInstruction1) {
    Species y('y');
    y.addInstruction("hop");
    y.addInstruction("if_empty 0");
    y.addInstruction("left");
    Creature c(y, north);
    Darwin d(5, 7);
    int i = y.executeInstruction(c, d, 3, 3, north, 1);
    ASSERT_EQ(i, 1);
}

TEST(Test_Species, executeInstruction2) {
    Species y('y');
    y.addInstruction("infect");
    y.addInstruction("if_enemy 0");
    y.addInstruction("left");
    y.addInstruction("if_wall 2");
    y.addInstruction("hop");
    y.addInstruction("if_empty 4");
    Creature c(y, north);
    Darwin d(5, 7);
    int i = y.executeInstruction(c, d, 3, 3, north, 3);
    ASSERT_EQ(i, 5);
}

TEST(Test_Species, executeInstruction3) {
    Species y('y');
    y.addInstruction("infect");
    y.addInstruction("if_enemy 0");
    y.addInstruction("left");
    y.addInstruction("if_wall 2");
    y.addInstruction("hop");
    y.addInstruction("if_empty 4");
    Creature c(y, north);
    Darwin d(5, 7);
    int i = y.executeInstruction(c, d, 3, 3, north, 5);
    ASSERT_EQ(i, 5);
}

/*TEST(Test_Creature, renderCreature1){
    Species x('x');
    x.addInstruction("if_empty 1");
    x.addInstruction("hop");
    Creature c(x, north);
    ASSERT_TRUE(c.renderCreature()=='x');    
}

TEST(Test_Creature, renderCreature2){
    Species y('y');
    y.addInstruction("if_empty 1");
    y.addInstruction("hop");
    Creature c(y, north);
    ASSERT_TRUE(c.renderCreature()=='y');    
}

TEST(Test_Creature, renderCreature3){
    Species x('x');
    Species y('y');
    y = x;
    x.addInstruction("if_empty 1");
    x.addInstruction("hop");
    Creature c(y, north);
    ASSERT_TRUE(c.renderCreature()=='x');    
}*/

TEST(Test_Creature, creatureRun1){
    Species y('y');
    y.addInstruction("infect");
    y.addInstruction("if_enemy 0");
    y.addInstruction("left");
    y.addInstruction("if_wall 2");
    y.addInstruction("hop");
    y.addInstruction("if_empty 4");
    Creature c(y, north);
    Darwin d(5, 7);
    c.creatureRun(d, 4, 1);
    ASSERT_EQ(c._progCounter, 1);
}

TEST(Test_Creature, creatureRun2){
    Species y('y');
    y.addInstruction("infect");
    y.addInstruction("if_enemy 0");
    y.addInstruction("left");
    y.addInstruction("if_wall 2");
    y.addInstruction("hop");
    y.addInstruction("if_empty 4");
    Creature c(y, north);
    Darwin d(5, 7);
    c._numRounds = 2;
    c.creatureRun(d, 4, 1);
    ASSERT_EQ(c._numRounds, 3);
}

TEST(Test_Creature, creatureRun3){
    Species y('y');
    y.addInstruction("infect");
    y.addInstruction("if_enemy 0");
    y.addInstruction("left");
    y.addInstruction("if_wall 2");
    y.addInstruction("hop");
    y.addInstruction("if_empty 4");
    Creature c(y, north);
    Darwin d(5, 7);
    c._progCounter = 1;
    c.creatureRun(d, 4, 1);
    ASSERT_EQ(c._species._program[c._progCounter], "if_wall 2");
}

TEST(Test_Creature, infect1){
    Species x('x');
    Species y('y');
    Creature c(x, north);
    Creature d(y, east);
    c.infect(d);
    ASSERT_EQ(d._species, x);
    ASSERT_EQ(d._progCounter, 0);
}

TEST(Test_Creature, infect2){
    Species x('x');
    Creature c(x, north);
    Creature d;
    c.infect(d);
    ASSERT_EQ(d._species, d.nSpecies);
}

TEST(Test_Creature, infect3){
    Species x('x');
    Creature c(x, north);
    Creature d(x, south);
    d._progCounter = 2;
    c.infect(d);
    ASSERT_EQ(d._progCounter, 2);
}

TEST(Test_Creature, turnLeft1){
    Species x('x');
    Creature c(x, north);
    c.turnLeft();
    ASSERT_EQ(c._direction, west);
}

TEST(Test_Creature, turnLeft2){
    Species x('x');
    Creature c(x, east);
    c.turnLeft();
    ASSERT_EQ(c._direction, north);
}

TEST(Test_Creature, turnLeft3){
    Species x('x');
    Creature c(x, west);
    c.turnLeft();
    c.turnLeft();
    ASSERT_EQ(c._direction, east);
}

TEST(Test_Creature, turnRight1){
    Species x('x');
    Creature c(x, north);
    c.turnRight();
    ASSERT_EQ(c._direction, east);
}

TEST(Test_Creature, turnRight2){
    Species x('x');
    Creature c(x, east);
    c.turnRight();
    ASSERT_EQ(c._direction, south);
}

TEST(Test_Creature, turnRight3){
    Species x('x');
    Creature c(x, south);
    c.turnRight();
    c.turnRight();
    ASSERT_EQ(c._direction, north);
}

TEST(Test_Darwin, iterator1) {
	Darwin d(8, 8);
	Species best('b');
	Species food('f');
	best.addInstruction("hop");
	Creature c(best, north);
	d.addCreature(c, 7, 6);
	d.addCreature(c, 0, 0);
	Creature f(food, {east});
	d.addCreature(f, 7, 7);
	Darwin_itr it = d.begin();
	ASSERT_EQ(*it, &c);
	it = d.at(7, 6);
	ASSERT_EQ(*it, &c);
	++it;
	ASSERT_EQ(*it, &f);
	it = d.end()-1;
	ASSERT_EQ(*it, &f);
}