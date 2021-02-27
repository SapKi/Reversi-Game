//
// Created by sapir on 25/11/17.
//

#ifndef EX1FINAL_AIPLAYER_H
#define EX1FINAL_AIPLAYER_H

#include "Player.h"
//#include "Game.h"
#include "Board.h"
#include "Cell.h"

class AIPlayer: public Player {
    public:
    AIPlayer(Board  * board, GameLogic * logic, int** validMoves , Board::State playerChar,Player* humanPlayer, int typeOfGame,ConsolePrinting* con,
    const char* filename);
    void GetBestScore(Board* CopyBoard);
    int buildImaginaryBoardforAI(Board* copyboard, int i, int j);
    int buildImaginaryBoardforOpponent(Board* copyboard, int i, int j);
    virtual void doTurn(int typeOfGame, Board *board, ConsolePrinting *con, Cell *&c);
    int retFinalI();
    int retFinalJ();
    void PrintCurrentStatus(Board::State playerChar,int i,int j);
    virtual void connectToServer();
    virtual int getMoveFromServer();
    virtual void noMove(ConsolePrinting* con);
    virtual void finishGame();
private:
    Board* copyBoard;
    Board* realBoard;
    GameLogic* copyLogic;
    int** moves;
    int** opponentmoves;
    int finalI;
    int finalJ;
    int goldenIndex;
    Player* opponent;
    ConsolePrinting* con;
};


#endif //EX1FINAL_AIPLAYER_H
