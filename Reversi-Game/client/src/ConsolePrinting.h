//
// Created by sapir on 05/12/17.
//

#ifndef EX1FINAL_CONSOLEPRINTING_H
#define EX1FINAL_CONSOLEPRINTING_H


#include "Board.h"
#include "Display.h"

/**
 * This class is used to print on the console.
 */
class ConsolePrinting : public Display {
public:
    ConsolePrinting();
    void print(Board* board);
    void possibleMoves(int** moves);
    void noValidMove();
    void noValidOption();
    void currentBoard();
    void itsYourMove(Board::State);
    void xPlayed();
    void oPlayed();
    void getInput();
    void noPossibleMoves();
    void noPossibleMovesForComp();
    void newLine();
    void printCell(Cell* p);
    void chooseGameOptions();
    void anyKeyToExitMassage();
    void writeBlackWin();
    void writeWhiteWIn();
    void writeDraw();
   // void fullBoard();
    void noMoreMovesForAll();
    void connectedToServerMessage();
    void waitingForOpponentToConnect();
    void noMorePosMove(Board::State stat);
    void pressAnyKeyToCont();
    ///////////////////////////////////
    void pressAnyKey();


    void printClientMenu();

    void notAvailableGame();


    void gameAlreadyExist();


    void gameNotOption();


    void EnterNameOfGame();

    void printString(string stringToPrint);

    void printAvailableGames(string availableGamesNames);

};

#endif //EX3WITHTESTS_CONSOLPRINTING_H