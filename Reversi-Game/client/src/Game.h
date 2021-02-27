//Sapir Kikoz 207071192

#ifndef EXAP1_GAME_H
#define EXAP1_GAME_H


#include "Board.h"
#include "GameLogic.h"
#include "Player.h"
#include "ConsolePrinting.h"

class Game {

public:
    /*
     * this function is the constructor of the class assing the current player of the game
     */
    Game(int row, int cols,ConsolePrinting* con, const char* filename);
    /*
     * this function is running the mane game flow by getting the current
     * player and call to the function of running a single turn
     */
    void gameFlow(Player* player1, Player* player2,int typeOfGame, ConsolePrinting* con);

    Player* manageTurn(Player* givenPlayer,Player* currPlayer, Player* otherPlayer);
    ~Game();
    Board* GetBoard();
    GameLogic* getGameLogic();
    int** GetMoves();
    Player* getFirstPlayer();
    Player* getSecondPlayer();
private:
    int rows,cols;
    Board* gameBoard;
    MajorGameLogic* gamelogic;
    int** moves;
    Player* player1;
    Player* player2;
    ConsolePrinting* con;
    Cell* lastTurn;
    int numofmoves;
    int invalidmoves;
    int typeOfGame;
    int BlackDeafualtTurn;
    int lasturnI;
    int lasturnJ;
    const char *filename;
};


#endif //EXAP1_GAME_H
