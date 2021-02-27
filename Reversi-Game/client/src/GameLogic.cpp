//
// Created by sapir on 12/11/17.
//

#include "GameLogic.h"
#include <iostream>

using namespace std;

GameLogic::GameLogic() {}

int GameLogic::validMoves(Board::State** board, int** moves, Board::State player){//Player* playerObject) {
    //deltas are the distance from the current cell to the borders
    int rowdelta = 0, coldelta = 0;
    int row = 0, col = 0;
    int x = 0, y = 0;
    int numofmoves = 0;
    // define the opponent
    //char player = playerObject->GetplayerType();
    Board::State opponent = (player == Board::Black) ? Board::White : Board::Black;

    // Initialize moves array with zeroes
    for (row = 0; row < 8; row++)
        for (col = 0; col < 8; col++)
            moves[row][col] = 0;


    /////////////////////////////////
    /* Finding squares for valid moves.                           */
    /* A valid move needs to be on a blank square and needs enclose */
    /* at least one square of the opponent between two player squares */
    for (row = 0; row < 8; row++)
        for (col = 0; col < 8; col++) {
            if (board[row][col] != player)
                continue;                  /* No - so on to the next */

            // Check around the blank square
            for (rowdelta = -1; rowdelta <= 1; rowdelta++)
                for (coldelta = -1; coldelta <= 1; coldelta++) {
                    /* check only inside the array - in the borders */
                    if (row + rowdelta < 0 || row + rowdelta >= 8 ||
                        col + coldelta < 0 || col + coldelta >= 8 ||
                        (rowdelta == 0 && coldelta == 0))
                        continue;

                    /*check the square */
                    if (board[row + rowdelta][col + coldelta] == opponent) {
                        /* If we find the opponent, move in the delta direction  */
                        /* over opponent counters searching for a player counter */
                        x = row + rowdelta;                /* Move to          */
                        y = col + coldelta;                /* opponent square  */

                        /* Look for a player square in the delta direction */
                        for (;;) {
                            // Go to next square in delta direction
                            x += rowdelta;
                            y += coldelta;

                            // If we are moving outside the array- stop
                            if ((x < 0) || (x >= 8) || (y < 0) || (y >= 8))
                                break;

                            // If we find a blank square -
                            if (board[x][y] == Board::Empty) {
                                //we have a valid move
                                numofmoves++;
                                moves[x][y] = 1;
                                break;
                            }
                            // If the square has a player counter
                            if (board[x][y] == player) {
                                //stop, give up
                                break;
                            }
                        }
                    }
                }
        }
    return numofmoves;
}

void GameLogic::makeMove(Board::State** board, int row, int col, Board::State player) {
    int rowdelta = 0, coldelta = 0;
    int x = 0, y = 0;
    //define opponent
    //char player = playerObject->GetplayerType();
    Board::State opponent = (player == Board::Black) ? Board::White : Board::Black;

    // Place the player sign
    board[row][col] = player;
    /* Check all squares around this square */
    for (rowdelta = -1; rowdelta <= 1; rowdelta++)
        for (coldelta = -1; coldelta <= 1; coldelta++) {
            /* check only inside the array */
            if (row + rowdelta < 0 || row + rowdelta >= 8 ||
                col + coldelta < 0 || col + coldelta >= 8 ||
                (rowdelta == 0 && coldelta == 0))
                continue;

            /* check the square */
            if (board[row + rowdelta][col + coldelta] == opponent) {
                /* If we find the opponent, search in the same direction */
                x = row + rowdelta;
                y = col + coldelta;

                for (;;) {
                    /* Move to the  next squre */
                    y += coldelta;
                    x += rowdelta;

                    /* If we are outside of the board - stop */
                    if (x < 0 || x >= 8 || y < 0 || y >= 8)
                        break;

                    /* If square is blank - stop */
                    if (board[x][y] == Board::Empty)
                        break;

                    /* If we find the player counter, go backwards */
                    /* changing all the opponents signs to the player sign */
                    if (board[x][y] == player) {
                        while (board[x -= rowdelta][y -= coldelta] == opponent)
                            board[x][y] = player;
                        break;
                    }
                }
            }
        }
    //   if (print == 1) printBoard(board); // print board
}