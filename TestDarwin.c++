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

TEST(Test_Species, renderSpecies1) {
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
    Creature c(y, north);
    Darwin d(5, 7);
    int i = y.instToInt("go");
    ASSERT_EQ(i, 9);
}

TEST(Test_Creature, renderCreature1){
    Species x('x');
    x.addInstruction("if_empty 1");
    x.addInstruction("hop");
    Creature c(x, north);
    ASSERT_TRUE(c.renderCreature()=='x');    
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