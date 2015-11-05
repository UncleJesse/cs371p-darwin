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

TEST(Test_Creature, creatureRun1){
    Species y('y');
    y.addInstruction("infect");
    y.addInstruction("if_enemy 0");
    y.addInstruction("left");
    y.addInstruction("if_wall 2");
    y.addInstruction("hop");
    y.addInstruction("if_empty 4");
    Creature c(y, south);
    Darwin d(5, 7);
    c._progCounter = 3;
    c.creatureRun(d, 5, 7);
    ASSERT_EQ(c._progCounter, 3);
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

TEST(Test_Creature, current1){
    Species x('x');
    Creature c(x, north);
    c._numRounds = 2;
    ASSERT_TRUE(c.current(2));
}

TEST(Test_Creature, current2){
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
    ASSERT_TRUE(c.current(1));
}

TEST(Test_Creature, current3){
    Species y('y');
    y.addInstruction("infect");
    y.addInstruction("if_enemy 0");
    y.addInstruction("left");
    y.addInstruction("if_wall 2");
    y.addInstruction("hop");
    y.addInstruction("if_empty 4");
    Creature c(y, north);
    Darwin d(7, 7);
    c._progCounter = 2;
    c.creatureRun(d, 4, 1);
    c.creatureRun(d, 4, 1);
    ASSERT_TRUE(c.current(2));
}

TEST(Test_Darwin, isWall1){
    Darwin d(7, 7);
    ASSERT_TRUE(d.isWall(6, 0, west));
    ASSERT_TRUE(d.isWall(6, 0, south));
}

TEST(Test_Darwin, isWall2){
    Darwin d(5, 7);
    ASSERT_TRUE(d.isWall(4, 6, east));
    ASSERT_TRUE(d.isWall(4, 6, south));
}

TEST(Test_Darwin, isWall3){
    Darwin d(7, 5);
    ASSERT_FALSE(d.isWall(6, 0, east));
    ASSERT_FALSE(d.isWall(6, 0, north));
}

TEST(Test_Darwin, isEmpty1){
    Darwin d(7, 7);
    ASSERT_FALSE(d.isEmpty(6, 0, west));
    ASSERT_FALSE(d.isEmpty(6, 0, south));
}

TEST(Test_Darwin, isEmpty2){
    Darwin d(7, 5);
    ASSERT_TRUE(d.isEmpty(6, 0, east));
    ASSERT_TRUE(d.isEmpty(6, 0, north));
}

TEST(Test_Darwin, isEmpty3){
    Darwin d(5, 5);
    Species x('x');
    Creature c(x, north);
    Creature e(x, south);
    d.addCreature(c, 4, 1);
    d.addCreature(e, 4, 2);
    ASSERT_FALSE(d.isEmpty(4, 1, east));
    ASSERT_FALSE(d.isEmpty(4, 2, west));
}

TEST(Test_Darwin, isEnemy1){
    Darwin d(7, 5);
    ASSERT_FALSE(d.isEnemy(6, 0, east));
    ASSERT_FALSE(d.isEnemy(6, 0, north));
}

TEST(Test_Darwin, isEnemy2){
    Darwin d(7, 5);
    ASSERT_FALSE(d.isEnemy(6, 0, west));
    ASSERT_FALSE(d.isEnemy(6, 0, south));
}

TEST(Test_Darwin, isEnemy3){
    Darwin d(5, 5);
    Species x('x');
    Species y('y');
    Creature c(x, north);
    Creature e(x, south);
    Creature g(y, east);
    d.addCreature(c, 4, 1);
    d.addCreature(e, 4, 2);
    d.addCreature(g, 3, 1);
    ASSERT_TRUE(d.isEnemy(4, 1, north));
    ASSERT_FALSE(d.isEnemy(4, 1, east));
    
}



TEST(Test_Darwin, addCreature1){
    Darwin d(7, 5);
    Species x('x');
    Creature c(x, north);
    Creature e(x, south);
    d.addCreature(c, 4, 1);
    ASSERT_FALSE(d.addCreature(e, 4, 1));
}

TEST(Test_Darwin, addCreature2){
    Darwin d(7, 5);
    Species x('x');
    Creature c(x, north);
    d.addCreature(c, 4, 1);
    ASSERT_FALSE(d.addCreature(c, 4, 2));
}

TEST(Test_Darwin, addCreature3){
    Darwin d(5, 5);
    Species x('x');
    Creature c(x, north);
    ASSERT_FALSE(d.addCreature(c, 5, 1));
}

TEST(Test_Darwin, jump1){
    Darwin d(5, 5);
    Species x('x');
    Creature c(x, north);
    d.addCreature(c, 4, 1);
    d.jump(4, 1, north);
    ASSERT_TRUE(d.isEmpty(3, 1, south));
}

TEST(Test_Darwin, jump2){
    Darwin d(5, 5);
    Species x('x');
    Creature c(x, north);
    d.addCreature(c, 4, 1);
    d.jump(4, 1, north);
    ASSERT_FALSE(d.isEmpty(4, 1, north));
}

TEST(Test_Darwin, jump3){
    Darwin d(5, 5);
    Species x('x');
    Creature c(x, north);
    d.addCreature(c, 4, 4);
    d.jump(4, 4, south);
    ASSERT_FALSE(d.isEmpty(4, 3, east));
}

TEST(Test_Darwin, infect1){
    Darwin d(5, 5);
    Species x('x');
    Species y('y');
    Creature c(x, north);
    Creature g(y, east);
    d.addCreature(c, 4, 1);
    d.addCreature(g, 3, 1);
    d.infect(4, 1, north);
    ASSERT_EQ(g._progCounter, 0);
}

TEST(Test_Darwin, infect2){
    Darwin d(5, 5);
    Species x('x');
    Species y('y');
    Creature c(x, north);
    Creature g(y, east);
    d.addCreature(c, 4, 1);
    d.addCreature(g, 3, 1);
    d.infect(3, 1, south);
    ASSERT_EQ(c._species._name, 'y');
}

TEST(Test_Darwin, infect3){
    Darwin d(5, 5);
    Species x('x');
    Species y('y');
    Creature c(x, north);
    Creature g(y, east);
    c._progCounter = 1;
    d.addCreature(c, 4, 1);
    d.addCreature(g, 3, 1);
    d.infect(4, 1, north);
    ASSERT_NE(c._progCounter, 0);
}

TEST(Test_Darwin, nextRound1){
    Darwin d(5, 8);
    d.nextRound();
    ASSERT_EQ(d._round, 2);
}

TEST(Test_Darwin, nextRound2){
    Darwin d(5, 8);
    d.nextRound();
    d.nextRound();
    ASSERT_EQ(d._round, 3);
}

TEST(Test_Darwin, nextRound3){
    Darwin d(5, 8);
    Species x('x');
    x.addInstruction("if_empty 1");
    x.addInstruction("hop");
    Creature c(x, north);
    d.addCreature(c, 2, 2);
    d.nextRound();
    ASSERT_EQ(c._numRounds, 1);
}

TEST(Test_Darwin, iterator1) {
	Darwin d(8, 8);
	Species best('b');
	Species food('f');
	best.addInstruction("hop");
	Creature c(best, north);
    Creature e(best, south);
	d.addCreature(c, 0, 0);
    d.addCreature(e, 0, 1);
	Creature f(food, {east});
	d.addCreature(f, 7, 7);
	Darwin_itr it = d.begin();
	ASSERT_EQ(*it, &c);
	++it;
	ASSERT_EQ(*it, &e);
	it = d.end()-1;
	ASSERT_EQ(*it, &f);
}