//
// Created by or on 30/11/17.
//
#include <iostream>
#include <gtest/gtest.h>
#include "../src/HumanPlayer.h"
//#include "../src/Player.h"
//#include "../src/GameLogic.h"
#include <climits>
using namespace std;


class HumanPlayerTest : public testing::Test {
protected:
    HumanPlayer h;
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
    HumanPlayerTest() : h(board, logic, val, 'X',2){}

};
/*
TEST_F(HumanPlayerTest, doTurn) {
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
TEST_F(HumanPlayerTest, InvalidInValidArray) {
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