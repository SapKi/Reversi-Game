//
// Created by or on 25/11/17.
//

#ifndef EX1FINAL_HUMANPLAYER_H
#define EX1FINAL_HUMANPLAYER_H
#include "Player.h"
#include "Board.h"

#include <string>
using namespace std;
class HumanPlayer : public Player{
public:
    HumanPlayer(Board* board, GameLogic* logic, int** validMoves, Board::State playerChar, int typeOfGame,ConsolePrinting* con,
    const char* filename);
    int GetBestScore();
    virtual void doTurn(int typeOfGame, Board *board, ConsolePrinting *con, Cell *&c);
    /*
     * this function prints the messeges to the user including his possible moves
     */
    void printCurrentStatus(char currentPlayer);
    int InvalidInValidArray(int row, int col);
    virtual void connectToServer();
    virtual int getMoveFromServer();
    virtual void noMove(ConsolePrinting* con);
    virtual void finishGame();

private:
    Board* copyBoard;
    GameLogic* copyLogic;
    int** moves;
    int typeOfGame;
    int finalTurnI;
    int finalTurnJ;
    ConsolePrinting* con;
};


#endif //EX1FINAL_HUMANPLAYER_H
