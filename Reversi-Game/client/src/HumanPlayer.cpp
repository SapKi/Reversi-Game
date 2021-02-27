//
// Created by or on 25/11/17.
//

#include "HumanPlayer.h"
#include <iostream>
#include <climits>
#include <limits>

HumanPlayer::HumanPlayer(Board* board, GameLogic* logic, int** validMoves, Board::State playerChar, int typeOfGame,ConsolePrinting* con,
const char* filename):
        Player(board,logic,validMoves,playerChar,typeOfGame,con,filename) {
    this->copyBoard = board;
    this->copyLogic = logic;
    this->moves = validMoves;
    this->typeOfGame = typeOfGame;
}

void HumanPlayer::doTurn(int typeOfGame, Board* board, ConsolePrinting* con, Cell *&c) {
    //x and y are the values that are scaned from the user
    int y = 0, x = 0;
    char xchar, ychar;
    char dummy = ' ';

    bool isThereMoves = copyLogic->validMoves(copyBoard->getBoard(), this->moves, this->GetplayerType());

    con->itsYourMove(this->GetplayerType());
    con->possibleMoves(this->moves);
    cout<<"Please enter your move row,col:";
    // now we check if the inserted values are valid in the array
    if (isThereMoves) {
        while (true) {

            cin >>x >>dummy>>y;
            xchar = x;
            ychar = y;

            if (xchar > 8 || xchar < 1 || ychar < 1 || ychar > 8 || (dummy != ',')) {
                cout << "invalid value, please enter 'row,col' between 1-8" << endl;
                cin.clear();
                std::cin.ignore(INT_MAX, '\n');
                continue;
            }


            // we got ints.
            // player starts from 1. our board starts from 0
            x-=1;
            y-=1;
            if(InvalidInValidArray(x,y) != 1){
                cout << "your move is not possible, please enter a move from the showed possible moves" << endl;
                cin.clear();
                std::cin.ignore(INT_MAX, '\n');
                continue;
            }

            if (copyLogic->checkInput(copyBoard->getBoard(), x, y))
                break;
        }
       // p->setI(x);
       // p->setJ(y);

        //moves to the game!!!!!!!!!!!

        //if the turn worked succesfully
        c = new Cell(x,y);
    } else {
        //bad arguments if the turn failed
        c = new Cell(-1,-1);
    }
}


int HumanPlayer::InvalidInValidArray(int x, int y) {
    if(this->moves[x][y] == 1) {
        return 1;
    } else {
        return 0;
    }
}

void HumanPlayer::connectToServer() {
}

void HumanPlayer::finishGame() {

}

void HumanPlayer::noMove(ConsolePrinting *con) {

}

int HumanPlayer::getMoveFromServer() {
}