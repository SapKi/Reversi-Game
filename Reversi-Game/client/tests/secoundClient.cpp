//
// Created by or on 11/12/17.


#include <iostream>
#include <gtest/gtest.h>
#include "../src/secondClient.h"

class secondClientTest : public testing::Test {
protected:
    secondClient s;
    Board* board;
    GameLogic* logic;
    int** val ;


    virtual void SetUp(){
        cout<<"Setting up"<<endl;
        board = new Board(9,9);
        val = new int*[9];
        logic = new GameLogic();

    }
    virtual void TearDown(){
        cout<<"Tearing down"<<endl;
        delete board;
        delete val;
        delete logic;
    }

public:
    secondClientTest() : s(board, logic, val, 'O',2){}

};
/*
TEST_F(secondClientTest, doTurn) {
int check = 0;
for (int i = 0; i < 9; ++i)
val[i] = new int[9];

//assinging the matrix by the default values
for (int i = 0; i < 9; ++i) {
for (int j = 0; j < 9; ++j) {
this->val[i][j] = 0;
}
}
this->val;
bool isThereMoves = logic->validMoves(board->getBoard(), this->val, 'X');
//  int check = 0;
//  bool isThereMoves = logic->validMoves(board->getBoard(), this->validMoves, 'X');
//bool isThereMoves = true;
//  if(isThereMoves){
check = h.doTurn();
// }
////  ASSERT_EQ(check,1);
}
*/
/*
TEST_F(secondClientTest, InvalidInValidArray) {
    for (int i = 0; i < 9; ++i)
        val[i] = new int[9];

    //assinging the matrix by the default values
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            this->val[i][j] = 0;
        }
    }
    this->val[4][4] = 0;
    ASSERT_EQ(h.InvalidInValidArray(4, 4),0);
}

*/


