//
// Created by or on 28/11/17.
//

#include <gtest/gtest.h>
#include "../src/Game.h"


class GameTest : public testing::Test{

protected:
    Game g;
    Board* b;
    MajorGameLogic* m;
    int** moves;

    virtual void SetUp(){
        cout<<"Setting up"<<endl;
        b = new Board(9,9);
        m = new GameLogic();
        moves = new int*[9];
    }
    virtual void TearDown(){
        cout<<"Tearing down"<<endl;
        delete b;
        delete m;
        delete moves;
    }


public:

    GameTest() : g( 9, 9){}
};

//check
TEST_F(GameTest, GetBoard){
    b = g.GetBoard();
    ASSERT_EQ(g.GetBoard(), b );
}

TEST_F(GameTest, getGameLogic){
    m = g.getGameLogic();
    ASSERT_EQ(g.getGameLogic(), m );
}

TEST_F(GameTest, GetMoves ){
int** moves = g.GetMoves();
    ASSERT_EQ(g.GetMoves(), moves);
}

TEST_F(GameTest, gameFlow ){
    int** moves = g.GetMoves();
    ASSERT_EQ(g.GetMoves(), moves);
}
///to do to function of zeromoves




