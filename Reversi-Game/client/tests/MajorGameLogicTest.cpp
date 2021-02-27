//
// Created by or on 30/11/17.
//
#include <iostream>
#include <gtest/gtest.h>
#include "../src/MajorGameLogic.h"

using namespace std;

class MajorGameLogicTest : public testing::Test {
protected:
    MajorGameLogic m;
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
    MajorGameLogicTest() : m(){}

};

TEST_F(MajorGameLogicTest, checkInput) {


}

TEST_F (MajorGameLogic, checkWinner){

}

