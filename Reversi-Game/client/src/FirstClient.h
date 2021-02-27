//
// Created by sapir on 10/12/17.
//

#ifndef EX1FINAL_FIRSTCLIENT_H
#define EX1FINAL_FIRSTCLIENT_H


#include "Player.h"

class FirstClient : public Player {

public:
    //constrctor of the first client that being connected
    FirstClient(Board* board, GameLogic* logic, int** validMoves, Board::State playerChar, int typeOfGame,ConsolePrinting* con,
    const char* filename);
    //conecting to the server
    void connectToServer();
    //updating the moves of the first client that being connected
    void UpdateArgs(int firstarg, int secondarg);
    //do turn of the first player that being connected
    virtual void doTurn(int typeOfGame, Board *board, ConsolePrinting *con, Cell *&c);
    int InvalidInValidArray(int x, int y);
    int getMoveFromServer();
    virtual void noMove(ConsolePrinting* con);
    virtual void finishGame();
    void playerMenu(Display* display);
    //
    void playerChoose();
    int ReadFromServer(string &command_str);
    int WriteToServer(string command);
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


#endif //EX1FINAL_CLIENT_H
