//
// Created by sapir on 12/11/17.
//

#ifndef EXAP1_GAMELOGIC_H
#define EXAP1_GAMELOGIC_H

#include "MajorGameLogic.h"



class GameLogic : public MajorGameLogic{
public:
    /*
     * this function is the constructor of the class - makes it possible to crete an object.
     */
    GameLogic();
    /**********************************************************************
* The function name: validMoves
* The input: board,moves(a board defining valid moves) and player.
* The output: none.
* The function operation: Calculates which squares are valid moves
 * for player. Valid moves are recorded in the moves array - 1
 * indicates a valid move, 0 indicates an invalid move.
**********************************************************************/
    virtual int validMoves(Board::State** board, int** moves, Board::State player);
    /**********************************************************************
* The function name: makeMove
* The input: board,row,column and player.
* The output: none.
* The function operation: places the counter on a square,and reverses
 * all the opponent's counters affected by the move.
**********************************************************************/
    virtual void makeMove(Board::State** board, int row, int col, Board::State player);
    /*
     * this function checks the game status , who wins returns 0 if the game
     * goes on, 1 if draw , 2 if black won and 3 if white won
     */

   // int checkWinner(char** board);
    /*
     * this function checks the validation of the input if in araay or not
     */
    //int checkInput(char** board, int r, int c);
private:
    char currentPlayer;
};

#endif //EXAP1_GAMELOGIC_H
