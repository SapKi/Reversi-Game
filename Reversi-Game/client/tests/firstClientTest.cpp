//
// Created by or on 11/12/17.
//



#include <iostream>
#include <gtest/gtest.h>
#include "../src/firstClient.h"

class firstClientTest : public testing::Test {
protected:
    firstClient f;
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
    firstClientTest() : f(board, logic, val, 'X',2){}

};
/*
TEST_F(firstClientTest, doTurn) {
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
TEST_F(firstClientTest, InvalidInValidArray) {
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

