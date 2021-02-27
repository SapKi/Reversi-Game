//
// Created by sapir on 14/11/17.
//

#ifndef EXAP1_PLAYER_H
#define EXAP1_PLAYER_H
#include "Cell.h"
#include "Board.h"
#include "MajorGameLogic.h"
#include "GameLogic.h"
#include "ConsolePrinting.h"
#include <fstream>
#include <cstring>



class Player {
public:
    Player(Board  * board, GameLogic * logic, int** validMoves , Board::State playerChar, int typeOfGame, ConsolePrinting* con,
           const char *filename);
    Player(const char* filename);
    Player(const char *serverIP, int serverPort);
    virtual void doTurn(int typeOfGame, Board *board, ConsolePrinting *con, Cell *&c) = 0;
    Board::State GetplayerType();
    Board* GetBoard();
    MajorGameLogic* getGameLogic();
    int** GetMoves();
    Board::State** GetBoardMatrix();
    virtual void connectToServer() = 0;
    virtual int getMoveFromServer() = 0;
    virtual void noMove(ConsolePrinting* con) = 0;
    void setPlayertype(Board::State stat);
    int getClientSocket();
    void setClientSocket(int socket);
    virtual void finishGame() = 0;

protected:
    Board::State playerChar;
    Board* copyBoard;
    MajorGameLogic* copyLogic;
    int** moves;
    int typeOfGame;
    ConsolePrinting* con;
    string serverIP;
    int serverPort;
    int clientSocket;
};


#endif //EXAP1_PLAYER_H