//
// Created by sapir on 27/11/17.
//

#include "MajorGameLogic.h"
#include <iostream>

using namespace std;
MajorGameLogic::MajorGameLogic() {}

/**
 *
 * if function return 0 if both players still has valid moves
 * if function return 1 its a draw same number of tokens
 * if function return 2 the X won
 * if function return 3 the O won
 */


int MajorGameLogic::checkInput(Board::State** board, int r, int c) {
/* Read player moves until a valid move is entered */
    if (r < 0 || r > 7 || c < 0 || c > 7) {
        cout << "No such square" << endl;
        cout << "please choose another square" << endl;
        return 0;
    }
    if (board[r][c] != Board::Empty) {
        cout << "this place is taken .. try again" << endl;
        return 0;
    } else {
        return 1;
    }
}

int MajorGameLogic::checkWinner(Board::State** board) {
    int whiteScore, blackScore;
    whiteScore = blackScore = 0;
    int row, col;

    int** moves= new int*[8];
    for (int i = 0; i < 8; ++i)
        moves[i] = new int[8];

    bool isThereMovesX = false;
    bool isThereMovesO = false;

    validMoves(board, moves, Board::Black);
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (moves[i][j] == 1) {
                isThereMovesX = true;
            }
        }
    }

    validMoves(board, moves, Board::White);
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (moves[i][j] == 1) {
                isThereMovesO = true;
            }
        }
    }

    if (isThereMovesO || isThereMovesX) {
        return 0;
    } else {
        // chose a winner
        for (row = 0; row < 8; row++) {
            for (col = 0; col < 8; col++) {
                whiteScore += (board[row][col] == Board::White);
                blackScore += (board[row][col] == Board::Black);
            }
        }

        if (whiteScore > blackScore) {
           // cout << "Winning player: White" << endl;
            return 3;
        } else if (blackScore > whiteScore) {
           // cout << "Winning player: Black" << endl;
            return 2;
        } else if(whiteScore == blackScore){
           // cout << "It's a draw - No winning player" << endl;
            return 1;
        } else {
            return 0;
        }
    }
}
/*
 * this function retuen 1 if there are no more possible moves
 * returns 0 if there are still possible moves
 *//*
int MajorGameLogic::ZeroMovesInCurrentTurn(Player* player, int** moves){
    int zerocounter = 0;
    for(int i = 0; i < 8; ++i) {
        for(int j = 0; j < 8; ++j) {
            if(moves[i][j] == 0) {
                zerocounter++;
            }
        }
    }
    if(zerocounter == 64){
        if(player->GetplayerType() == 'X') {
            cout << "No possible move. Play passes back to the other player. Press enter to continiue." << endl;
        }
        return 1;
    } else {
        return 0;
    }
}
*/