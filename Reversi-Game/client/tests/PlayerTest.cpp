//
// Created by or on 29/11/17.
//
#include <iostream>
#include <gtest/gtest.h>
#include "../src/Player.h"
#include "../src/AIPlayer.h"
#include "../src/HumanPlayer.h"
using namespace std;

class PlayerTest : public testing::Test {
protected:
  //  char curplayer;

    Player * p;
    //Player * p2;
    Board  * board;
    int** validMoves ;
    GameLogic * logic;


    virtual void SetUp(){
        cout<<"Setting up"<<endl;
        board = new Board(9,9);
        validMoves = new int*[9];
        logic = new GameLogic();
       p = new HumanPlayer(board, logic, validMoves, 'X', 2);
       // p2 =new AIPlayer(board, logic, validMoves, 'O', this->p);
    }
    virtual void TearDown(){
       cout<<"Tearing down"<<endl;
         delete p;
      //  delete p2;
        delete board;
        delete validMoves;
        delete logic;
    }


public:
    PlayerTest() {}

};

TEST_F(PlayerTest, T1GetplayerType) {
    p = new HumanPlayer(board, logic, validMoves, 'X', 2);
    char playerchar = p->GetplayerType();
    ASSERT_EQ(playerchar, 'X');
}
/*
TEST_F(PlayerTest, T2GetplayerType) {
    p = new HumanPlayer(board, logic, validMoves, 'X');
    p2 = new AIPlayer(board, logic, validMoves, 'O', p);
    char playerchar = p2->GetplayerType();
    ASSERT_EQ(playerchar, 'O');
}

*/

TEST_F(PlayerTest, T1GetBoard) {
    Board* copyBoard = p->GetBoard();
    ASSERT_EQ(copyBoard, p->GetBoard());
}
/*
TEST_F(PlayerTest, T2GetBoard) {

    Board* copyBoard = p2->GetBoard();
    ASSERT_EQ(copyBoard, p->GetBoard());
}
*/

TEST_F(PlayerTest, T1GetBoardMatrix) {
    char** bm = p->GetBoardMatrix();
    ASSERT_EQ(bm, p->GetBoard()->GetMatrix());
}
/*
TEST_F(PlayerTest, T2GetBoardMatrix) {
    char** bm = p2->GetBoardMatrix();
    ASSERT_EQ(bm, p2->GetBoard()->GetMatrix());
}
 */
TEST_F(PlayerTest, T1GetMoves) {
    int** moves = p->GetMoves();
    ASSERT_EQ(moves, p->GetMoves());
}
/*
TEST_F(PlayerTest, T2GetMoves) {
    int** moves = p2->GetMoves();
    ASSERT_EQ(moves, p2->GetMoves());
}
 */
TEST_F(PlayerTest, T1getGameLogic) {
    MajorGameLogic* major = p->getGameLogic();
    ASSERT_EQ(major, p->getGameLogic());
}


/*
char** Player::GetBoardMatrix() {
    return this->GetBoard()->GetMatrix();
}
MajorGameLogic* Player::getGameLogic() {
    return this->copyLogic;
}

int** Player::GetMoves(){
    return this->moves;
}

/*
TEST_F(PlayerTest, settypeOfGame) {
    int typeOfGame = 1;
    Player.settypeOfGame(typeOfGame);
    ASSERT_EQ(type, 1);
}

/*
TEST_F(PlayerTest, choosePlayerType) {
    int typeOfGame = Player.settypeOfGame(typeOfGame);
    ASSERT_EQ(typeOfGame,1);
}



char Player::GetplayerType(){
    return this->currentPlayer;
}

*/
