//
// Created by sapir on 10/12/17.
//

#ifndef EX1FINAL_SECONDCLIENT_H
#define EX1FINAL_SECONDCLIENT_H


#include "Player.h"

class SecondClient : public Player {

public:
    SecondClient(Board* board, GameLogic* logic, int** validMoves, Board::State playerChar, int typeOfGame,ConsolePrinting* con,
    const char* filename);
    void connectToServer();
    void UpdateArgs(int firstarg, int secondarg);
    void doTurn(int typeOfGame, Board *board, ConsolePrinting *con, Cell *&c);
    int InvalidInValidArray(int x, int y);
    int getMoveFromServer();
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
    const char* filename;
};


#endif //EX1FINAL_SECONDCLIENT_H
