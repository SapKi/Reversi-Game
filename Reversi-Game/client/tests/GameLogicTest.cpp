//
// Created by or on 30/11/17.
//
#include <iostream>
#include <gtest/gtest.h>
#include "../src/GameLogic.h"
#include "../src/Board.h"

using namespace std;

class GameLogicTest : public testing::Test {
protected:
    GameLogic g;
    Board* board ;
    int** moves;




    virtual void SetUp(){
        cout<<"Setting up"<<endl;
        board = new Board(9,9);
        moves = new int*[9];
    }
    virtual void TearDown(){

        cout<<"Tearing down"<<endl;
        delete board;
        delete moves;
    }


public:
    GameLogicTest() : g(){}

};

TEST_F(GameLogicTest, validMoves) {
    for (int i = 0; i < 9; ++i)
        moves[i] = new int[9];

    //assinging the matrix by the default values
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            this->moves[i][j] = 0;
        }
    }
    int valid = g.validMoves(board->GetMatrix(), moves, 'X');
    ASSERT_EQ(valid,4);
}
