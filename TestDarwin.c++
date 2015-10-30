#include "gtest/gtest.h"
#include "Darwin.h"
#include <stdexcept>

using namespace std;

TEST(Test_Species, addInstruction1) {
    Species x;
    x.addInstruction("hop");
    string s = x.nextInstruction(0);
    ASSERT_TRUE(s.compare("hop") == 0);
}

TEST(Test_Species, addInstruction2) {
    Species x;
    x.addInstruction("hop");
    x.addInstruction("go 1");
    x.addInstruction("left");
    x.addInstruction("if_wall 2");
    ASSERT_EQ(4, x.numberOfInstructions());
}

TEST(Test_Species, validSpecies1) {
    Species x;
    x.addInstruction("hop");
    ASSERT_TRUE(x.validSpecies());
}

TEST(Test_Species, validSpecies2) {
    Species x;
    ASSERT_FALSE(x.validSpecies());
}

TEST(Test_Species, nextInstruction1) {
    Species x;
    x.addInstruction("hop");
    x.addInstruction("if_empty 0");
    x.addInstruction("right");
    x.addInstruction("if_wall 2");
    string s = x.nextInstruction(2);
    ASSERT_TRUE(s.compare("right") == 0);
}

TEST(Test_Species, nextInstruction2) {
    Species x;
    x.addInstruction("hop");
    x.addInstruction("if_empty 0");
    x.addInstruction("right");
    x.addInstruction("if_wall 2");
    string s = x.nextInstruction(4);
    ASSERT_TRUE(s.compare("hop") == 0);
}