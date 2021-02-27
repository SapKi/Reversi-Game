//
// Created by or on 27/11/17.
//

#include <iostream>
#include <gtest/gtest.h>
#include "../src/Board.h"

class BoardTest : public testing::Test {
protected:
    Board b;

    virtual void SetUp(){
        cout<<"Setting up"<<endl;
    }
    virtual void TearDown(){
        cout<<"Tearing down"<<endl;
    }


public:
    BoardTest() : b(9,9){}

};



TEST_F(BoardTest, deafultPosition) {
    //b = Board(2,2);
    //char **c = b.getBoard();
    //b->print();
    char **c = b.getBoard();
    //printf(">> %c,%c,%c,%c\n", c[3][3], c[4][4], c[3][4], c[4][3]);
    ASSERT_EQ('O', c[3][3]);
    ASSERT_EQ('O',c[4][4]);
    ASSERT_EQ('X',c[3][4]);
    ASSERT_EQ('X',c[4][3]);
    //ASSERT_EQ(b.sut.printBoardTests(1), "1");
}

TEST_F(BoardTest, getRows) {
    int row = b.GetRows();
    ASSERT_EQ(row,9);
}

TEST_F(BoardTest, getCols) {
    int col = b.GetCoulmns();
    ASSERT_EQ(col,9);
}
///check if makes sense

TEST_F(BoardTest, getBoard) {
    char** matrix_ = b.getBoard();
    ASSERT_EQ(matrix_, b.getBoard());
}

TEST_F(BoardTest, getCell) {
    char cell = b.getCell(b.GetRows()-1, b.GetCoulmns()-1);
    ASSERT_EQ(cell, b.getBoard()[b.GetRows()-1][b.GetCoulmns()-1]);
}

TEST_F(BoardTest, setCell) {
    char cell = b.getBoard()[3][3];
    b.setCell(3, 3, 'O');
    ASSERT_EQ(cell, b.getCell(3,3));
}







