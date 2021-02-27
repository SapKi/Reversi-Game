//
// Created by or on 26/11/17.
//

#ifndef EX1FINAL_GAMELOGICINTERFACE_H
#define EX1FINAL_GAMELOGICINTERFACE_H


class GameLogicInterface {
public:
    /*
     * this function is the constructor of the class - makes it possible to crete an object.
     */
    GameLogicInterface();
    /**********************************************************************
* The function name: validMoves
* The input: board,moves(a board defining valid moves) and player.
* The output: none.
* The function operation: Calculates which squares are valid moves
 * for player. Valid moves are recorded in the moves array - 1
 * indicates a valid move, 0 indicates an invalid move.
**********************************************************************/
    int validMoves(char** board, int** moves, char player);
    /**********************************************************************
* The function name: makeMove
* The input: board,row,column and player.
* The output: none.
* The function operation: places the counter on a square,and reverses
 * all the opponent's counters affected by the move.
**********************************************************************/
    void makeMove(char** board, int row, int col, char player);
    /*
     * this function checks the game status , who wins returns 0 if the game
     * goes on, 1 if draw , 2 if black won and 3 if white won
     */
    int checkWinner(char** board);
    /*
     * this function checks the validation of the input if in araay or not
     */
    int checkInput(char** board, int r, int c);
private:
    char currentPlayer;

};


#endif //EX1FINAL_GAMELOGICINTERFACE_H
