//
// Created by sapir on 05/12/17.
//

#ifndef EX1FINAL_DISPLAY_H
#define EX1FINAL_DISPLAY_H


#include "Board.h"

/**
 * This is an abstract class for the display.
 */
class Display {
public:
//the board
    virtual void print(Board* board) = 0;

   // virtual void possibleMoves(Cell positions[], int moves) = 0;

   // virtual void noValidMove() = 0;

    virtual void noValidOption() = 0;

    virtual void currentBoard() = 0;

    virtual void itsYourMove(Board::State) = 0;

//n chacking if there are no possible moves for current player
    virtual void noPossibleMoves() = 0;
// printing new line
    virtual void newLine() = 0;

     //printing the game options.

    virtual void chooseGameOptions() = 0;


    virtual void writeBlackWin() = 0;

    virtual void writeWhiteWIn() = 0;

    virtual void writeDraw() = 0;

    ///////to change names
    virtual void pressAnyKey() = 0;

    virtual void printClientMenu()  = 0;

    virtual void notAvailableGame()  = 0;

    virtual void gameAlreadyExist()  = 0;

    virtual void gameNotOption()  = 0;

    virtual void EnterNameOfGame()  = 0;

    virtual void printString(string stringToPrint) = 0;

    virtual void printAvailableGames(string availableGamesNames) = 0;




};
#endif //EX3WITHTESTS_DISPLAY_H