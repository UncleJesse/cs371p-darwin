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

TEST(Test_Species, validSpecies) {
    Species x;
    x.addInstruction("hop");
    ASSERT_TRUE(x.validSpecies());
}

