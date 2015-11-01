#include "gtest/gtest.h"
#include "Darwin.h"
#include <stdexcept>

using namespace std;

TEST(Test_Species, addInstruction1) {
    Species x('x');
    x.addInstruction("hop");
    string s = x.nextInstruction(0);
    ASSERT_TRUE(s.compare("hop") == 0);
}

TEST(Test_Species, addInstruction2) {
    Species x('x');
    x.addInstruction("hop");
    x.addInstruction("go 1");
    x.addInstruction("left");
    x.addInstruction("if_wall 2");
    string s = x.nextInstruction(1);
    ASSERT_EQ(s,"go 1");
}

TEST(Test_Species, addInstruction3) {
    Species x('x');
    x.addInstruction("if_empty 1");
    x.addInstruction("hop");
    string s = x.nextInstruction(0);
    ASSERT_EQ(s,"if_empty 1");
}

TEST(Test_Species, ready1) {
    Species x('x');
    x.addInstruction("hop");
    ASSERT_TRUE(x.ready());
}

TEST(Test_Species, ready2) {
    Species x('x');
    ASSERT_FALSE(x.ready());
}

TEST(Test_Species, ready3) {
    Species x('x');
    x.addInstruction("go 0");
    ASSERT_TRUE(x.ready());
}

TEST(Test_Species, nextInstruction1) {
    Species x('x');
    x.addInstruction("hop");
    x.addInstruction("if_empty 0");
    x.addInstruction("right");
    x.addInstruction("if_wall 2");
    string s = x.nextInstruction(2);
    ASSERT_TRUE(s.compare("right") == 0);
}

TEST(Test_Species, nextInstruction2) {
    Species x('x');
    x.addInstruction("hop");
    x.addInstruction("if_empty 0");
    x.addInstruction("right");
    x.addInstruction("if_wall 2");
    string s = x.nextInstruction(4);
    ASSERT_TRUE(s.compare("hop") == 0);
}

TEST(Test_Species, nextInstruction3) {
    Species x('x');
    x.addInstruction("left");
    x.addInstruction("if_empty 2");
    x.addInstruction("hop");
    x.addInstruction("if_wall 0");
    string s = x.nextInstruction(0);
    ASSERT_FALSE(s.compare("hop") == 0);
}

TEST(Test_Creature, constructor){

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
	vector<Creature*>::iterator it = d.begin();
	ASSERT_EQ(*it, &c);
	it = d.at(7, 6);
	ASSERT_EQ(*it, &c);
	//++it;
	//ASSERT_EQ(*it, &f);
	it = d.end()-1;
	ASSERT_EQ(*it, &f);
}