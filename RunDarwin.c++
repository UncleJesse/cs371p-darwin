// -----------------------------
// projects/darwin/RunDarwin.c++
// Copyright (C) 2015
// Glenn P. Downing
// -----------------------------

// --------
// includes
// --------

#include <cassert>   // assert
#include <cstdlib>   // rand, srand
#include <iostream>  // cout, endl
#include <stdexcept> // invalid_argument, out_of_range

#include <stdio.h>
#include "Darwin.h"
#include "Darwin.c++"

// ----
// main
// ----

//Make the Darwin iterator
int main()
{
    using namespace std;
    // Darwin darwin(8,8);
    // Species trap('t');
    // trap.addInstruction("hop");
    // Creature c1(trap,{south});
    // cout<<trap.getName()<<endl;
    // darwin.addCreature(c1,0,0);
    // darwin.printDarwin();
    // darwin.nextRound();
    // darwin.printDarwin();




    // ----
    // food
    // ----

    /*
     0: left
     1: go 0
    */
     Species food('f');
     food.addInstruction("left");
     food.addInstruction("go 0");

    // ------
    // hopper
    // ------

    /*
     0: hop
     1: go 0
    */
     Species hopper('h');
     hopper.addInstruction("hop");
     hopper.addInstruction("go 0");

    // -----
    // rover
    // -----

    /*
     0: if_enemy 9
     1: if_empty 7
     2: if_random 5
     3: left
     4: go 0
     5: right
     6: go 0
     7: hop
     8: go 0
     9: infect
    10: go 0
    */
    Species rover('r');
    rover.addInstruction("if_enemy 9");
    rover.addInstruction("if_empty 7");
    rover.addInstruction("if_random 5");
    rover.addInstruction("left");
    rover.addInstruction("go 0");
    rover.addInstruction("right");
    rover.addInstruction("go 0");
    rover.addInstruction("hop");
    rover.addInstruction("go 0");
    rover.addInstruction("infect");
    rover.addInstruction("go 0");
    // ----
    // trap
    // ----

    /*
     0: if_enemy 3
     1: left
     2: go 0
     3: infect
     4: go 0
    */
     Species trap('t');
     trap.addInstruction("if_enemy 3");
     trap.addInstruction("left");
     trap.addInstruction("go 0");
     trap.addInstruction("infect");
     trap.addInstruction("go 0");

    // ----------
    // darwin 8x8
    // ----------

    cout << "*** Darwin 8x8 ***" << endl;
    /*
    8x8 Darwin
    Food,   facing east,  at (0, 0)
    Hopper, facing north, at (3, 3)
    Hopper, facing east,  at (3, 4)
    Hopper, facing south, at (4, 4)
    Hopper, facing west,  at (4, 3)
    Food,   facing north, at (7, 7)
    Simulate 5 moves.
    Print every grid.
    */
    Darwin darwin(8,8);
    Creature f1(food,east);
    Creature h1(hopper,north);
    Creature h2(hopper,east);
    Creature h3(hopper,south);
    Creature h4(hopper,west);
    Creature f2(food,north);
    darwin.addCreature(f1,0,0);
    darwin.addCreature(h1,3,3);
    darwin.addCreature(h2,3,4);
    darwin.addCreature(h3,4,4);
    darwin.addCreature(h4,4,3);
    darwin.addCreature(f2,7,7);
    darwin.printDarwin();
    darwin.nextRound();
    darwin.printDarwin();
    darwin.nextRound();
    darwin.printDarwin();
    darwin.nextRound();
    darwin.printDarwin();
    darwin.nextRound();
    darwin.printDarwin();
    darwin.nextRound();
    darwin.printDarwin();
    cout<<endl;   
    cout<<endl; 
    cout<<endl;  

    // ----------
    // darwin 7x9
    // ----------

    cout << "*** Darwin 7x9 ***" << endl;
    srand(0);
    /*
    7x9 Darwin
    Trap,   facing south, at (0, 0)
    Hopper, facing east,  at (3, 2)
    Rover,  facing north, at (5, 4)
    Trap,   facing west,  at (6, 8)
    Simulate 5 moves.
    Print every grid.
    */
    Darwin darwin2(7,9);
    Creature t1(trap,south);
    Creature h5(hopper,east);
    Creature r1(rover,north);
    Creature t2(trap,west);
    darwin2.addCreature(t1,0,0);
    darwin2.addCreature(h5,3,2);
    darwin2.addCreature(r1,5,4);
    darwin2.addCreature(t2,6,8);
    darwin2.printDarwin();
    darwin2.nextRound();
    darwin2.printDarwin();
    darwin2.nextRound();
    darwin2.printDarwin();
    darwin2.nextRound();
    darwin2.printDarwin();
    darwin2.nextRound();
    darwin2.printDarwin();
    darwin2.nextRound();
    darwin2.printDarwin();

    cout<<endl<<endl<<endl;

    // ------------
    // darwin 72x72
    // without best
    // ------------

    cout << "*** Darwin 72x72 without Best ***" << endl;
    srand(0);
    /*
    Randomly place the following creatures facing randomly.
    Call rand(), mod it with 5184 (72x72), and use that for the position
    in a row-major order grid.
    Call rand() again, mod it with 4 and use that for it's direction with
    the ordering: west, north, east, south.
    Do that for each kind of creature.
    10 Food
    10 Hopper
    10 Rover
    10 Trap
    Simulate 1000 moves.
    Print the first 10 grids          (i.e. 0, 1, 2...9).
    Print every 100th grid after that (i.e. 100, 200, 300...1000).
    */

    /*
    Darwin darwin3(72,72);
    Creature f3(food,static_cast<direction>(rand()%4));
    Creature f4(food,static_cast<direction>(rand()%4));
    Creature f5(food,static_cast<direction>(rand()%4));
    Creature f6(food,static_cast<direction>(rand()%4));
    Creature f7(food,static_cast<direction>(rand()%4));
    Creature f8(food,static_cast<direction>(rand()%4));
    Creature f9(food,static_cast<direction>(rand()%4));
    Creature f10(food,static_cast<direction>(rand()%4));
    Creature f11(food,static_cast<direction>(rand()%4));
    Creature f12(food,static_cast<direction>(rand()%4));
    
    Creature h6(hopper,static_cast<direction>(rand()%4));
    Creature h7(hopper,static_cast<direction>(rand()%4));
    Creature h8(hopper,static_cast<direction>(rand()%4));
    Creature h9(hopper,static_cast<direction>(rand()%4));
    Creature h10(hopper,static_cast<direction>(rand()%4));
    Creature h11(hopper,static_cast<direction>(rand()%4));
    Creature h12(hopper,static_cast<direction>(rand()%4));
    Creature h13(hopper,static_cast<direction>(rand()%4));
    Creature h14(hopper,static_cast<direction>(rand()%4));
    Creature h15(hopper,static_cast<direction>(rand()%4));

    Creature r2(rover,static_cast<direction>(rand()%4));
    Creature r3(rover,static_cast<direction>(rand()%4));
    Creature r4(rover,static_cast<direction>(rand()%4));
    Creature r5(rover,static_cast<direction>(rand()%4));
    Creature r6(rover,static_cast<direction>(rand()%4));
    Creature r7(rover,static_cast<direction>(rand()%4));
    Creature r8(rover,static_cast<direction>(rand()%4));
    Creature r9(rover,static_cast<direction>(rand()%4));
    Creature r10(rover,static_cast<direction>(rand()%4));
    Creature r11(rover,static_cast<direction>(rand()%4));

    Creature t3(trap,static_cast<direction>(rand()%4));
    Creature t4(trap,static_cast<direction>(rand()%4));
    Creature t5(trap,static_cast<direction>(rand()%4));
    Creature t6(trap,static_cast<direction>(rand()%4));
    Creature t7(trap,static_cast<direction>(rand()%4));
    Creature t8(trap,static_cast<direction>(rand()%4));
    Creature t9(trap,static_cast<direction>(rand()%4));
    Creature t10(trap,static_cast<direction>(rand()%4));
    Creature t11(trap,static_cast<direction>(rand()%4));
    Creature t12(trap,static_cast<direction>(rand()%4));

    darwin3.addCreature(f3,rand()%72,rand()%72);
    darwin3.addCreature(f4,rand()%72,rand()%72);
    darwin3.addCreature(f5,rand()%72,rand()%72);
    darwin3.addCreature(f6,rand()%72,rand()%72);
    darwin3.addCreature(f7,rand()%72,rand()%72);
    darwin3.addCreature(f8,rand()%72,rand()%72);
    darwin3.addCreature(f9,rand()%72,rand()%72);
    darwin3.addCreature(f10,rand()%72,rand()%72);
    darwin3.addCreature(f11,rand()%72,rand()%72);
    darwin3.addCreature(f12,rand()%72,rand()%72);

    darwin3.addCreature(h6,rand()%72,rand()%72);
    darwin3.addCreature(h7,rand()%72,rand()%72);
    darwin3.addCreature(h8,rand()%72,rand()%72);
    darwin3.addCreature(h9,rand()%72,rand()%72);
    darwin3.addCreature(h10,rand()%72,rand()%72);
    darwin3.addCreature(h11,rand()%72,rand()%72);
    darwin3.addCreature(h12,rand()%72,rand()%72);
    darwin3.addCreature(h13,rand()%72,rand()%72);
    darwin3.addCreature(h14,rand()%72,rand()%72);
    darwin3.addCreature(h15,rand()%72,rand()%72);

    darwin3.addCreature(r2,rand()%72,rand()%72);
    darwin3.addCreature(r3,rand()%72,rand()%72);
    darwin3.addCreature(r4,rand()%72,rand()%72);
    darwin3.addCreature(r5,rand()%72,rand()%72);
    darwin3.addCreature(r6,rand()%72,rand()%72);
    darwin3.addCreature(r7,rand()%72,rand()%72);
    darwin3.addCreature(r8,rand()%72,rand()%72);
    darwin3.addCreature(r9,rand()%72,rand()%72);
    darwin3.addCreature(r10,rand()%72,rand()%72);
    darwin3.addCreature(r11,rand()%72,rand()%72);

    darwin3.addCreature(t3,rand()%72,rand()%72);
    darwin3.addCreature(t4,rand()%72,rand()%72);
    darwin3.addCreature(t5,rand()%72,rand()%72);
    darwin3.addCreature(t6,rand()%72,rand()%72);
    darwin3.addCreature(t7,rand()%72,rand()%72);
    darwin3.addCreature(t8,rand()%72,rand()%72);
    darwin3.addCreature(t9,rand()%72,rand()%72);
    darwin3.addCreature(t10,rand()%72,rand()%72);
    darwin3.addCreature(t11,rand()%72,rand()%72);
    darwin3.addCreature(t12,rand()%72,rand()%72);


    for(int i=0;i<1000;i++){
        if(i<10 || i%100==0){
            darwin3.printDarwin();
        }
        darwin3.nextRound();
    }*/
    

    // ------------
    // darwin 72x72
    // with best
    // ------------

    cout << "*** Darwin 72x72 with Best ***" << endl;
    srand(0);
    /*
    Randomly place the following creatures facing randomly.
    Call rand(), mod it with 5184 (72x72), and use that for the position
    in a row-major order grid.
    Call rand() again, mod it with 4 and use that for it's direction with
    the ordering: 0:west, 1:north, 2:east, 3:south.
    Do that for each kind of creature.
    10 Food
    10 Hopper
    10 Rover
    10 Trap
    10 Best
    Simulate 1000 moves.
    Best MUST outnumber ALL other species for the bonus pts.
    Print the first 10 grids          (i.e. 0, 1, 2...9).
    Print every 100th grid after that (i.e. 100, 200, 300...1000).
    */

    return 0;}
