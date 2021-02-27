//
// Created by sapir on 27/11/17.
//

#ifndef EX1FINAL_MAJORGAMELOGIC_H
#define EX1FINAL_MAJORGAMELOGIC_H

//#include "ConsolePrinting.h"
#include "Board.h"


class MajorGameLogic {
public:
    /*
     * this function is the constructor of the class - makes it possible to crete an object.
     */
    MajorGameLogic();
    /**********************************************************************
* The function name: validMoves
* The input: board,moves(a board defining valid moves) and player.
* The output: none.
* The function operation: Calculates which squares are valid moves
 * for player. Valid moves are recorded in the moves array - 1
 * indicates a valid move, 0 indicates an invalid move.
**********************************************************************/
    virtual int validMoves(Board::State** board, int** moves, Board::State player) = 0;
    /**********************************************************************
* The function name: makeMove
* The input: board,row,column and player.
* The output: none.
* The function operation: places the counter on a square,and reverses
 * all the opponent's counters affected by the move.
**********************************************************************/
    virtual void makeMove(Board::State** board, int row, int col, Board::State player) = 0;
    /*
     * this function checks the game status , who wins returns 0 if the game
     * goes on, 1 if draw , 2 if black won and 3 if white won
     */
    int checkWinner(Board::State** board);
    /*
     * this function checks the validation of the input if in araay or not
     */
    int checkInput(Board::State** board, int r, int c);

    //int ZeroMovesInCurrentTurn(Player* player, int** moves);
private:
    //char currentPlayer;

};


#endif //EX1FINAL_MAJORGAMELOGIC_H
