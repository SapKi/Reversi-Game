//
// Created by or on 30/11/17.
//
#include <iostream>
#include <gtest/gtest.h>
#include "../src/Cell.h"
using namespace std;
class CellTest : public testing::Test {
protected:
    Cell c;

    virtual void SetUp(){
        cout<<"Setting up"<<endl;
    }
    virtual void TearDown(){
        cout<<"Tearing down"<<endl;
    }


public:
    CellTest() : c(9,9){}

};

TEST_F(CellTest, getI) {
    int i = c.getI();
    ASSERT_EQ(i,9);
}

TEST_F(CellTest, getJ) {
    int j = c.getJ();
    ASSERT_EQ(j,9);
}

TEST_F(CellTest, setI) {
    int i = c.getI();
    c.setI(9);
    ASSERT_EQ(i,c.getI());
}


TEST_F(CellTest, setJ) {
    int j = c.getJ();
    c.setJ(9);
    ASSERT_EQ(j,c.getJ());
}


