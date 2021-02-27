//
// Created by sapir on 05/12/17.
//

#include "ConsolePrinting.h"
#include <iostream>

ConsolePrinting::ConsolePrinting() {}

void ConsolePrinting::print(Board *board) {
    int size = board->GetRows();
    int matrixCoordinates[size];
    Cell* c;
    for (int i = 0; i < size; i++) {
        matrixCoordinates[i] = i + 1;
    }
    string line = "----------------------------------";
    for (int i = 0; i < size; i++) {
        cout << " | " << matrixCoordinates[i];
    }
    cout << " | " << endl;
    cout << line << endl;
    for (int i = 0; i < size; i++) {
        cout << matrixCoordinates[i] << "|";
        for (int j = 0; j < size; j++) {
            Cell* c = new Cell(i,j);
            Board::State stat = board->getCellStatus(c);
            switch (stat) {
                case Board::Empty:
                    cout << "   |";
                    break;
                case Board::White:
                    cout << " O |";
                    break;
                case Board::Black:
                    cout << " X |";
                    break;
            }
        }
        cout << "" << endl;
        cout << line << endl;
    }
}

/*void Board::print() {
    // print the first line of the board
    cout << " |";
    for (int i = 1; i < 9; ++i) {
        cout << " " << i << " |";
    }

    cout << endl;
    cout << "----------------------------------" << endl;

    // print the rest of the board according to the matrix
    for (int i = 1; i < 9; ++i) {
        cout << i << "|";
        for (int j = 0; j < 8; ++j) {
        //////////////////////////////////////////////////////////////////
            cout << " " << this->matrix_[i - 1][j] << " |";
        }
        cout << endl;
        cout << "----------------------------------" << endl;
    }
}*/
/*
void ConsolePrinting::noValidMove() {
    cout << "Bad arguments, please type only a valid move" << endl;
}
*/
void ConsolePrinting::currentBoard() {
    cout << "Current board:" << endl << endl;
}

void ConsolePrinting::itsYourMove(Board::State player) {
    if (player == Board::White) {
        cout << "O: It's your move." << endl;
    }
    if (player == Board::Black) {
        cout << "X: It's your move." << endl;
    }
}
void ConsolePrinting::noMorePosMove(Board::State stat) {
    cout << "No possible moves for ";
    if (stat == Board::Black) {
        cout << "X" << endl;
    } else {
        cout << "O" << endl;
    }
    cout << "Play passes back to other player" << endl;

}
//
void ConsolePrinting::possibleMoves(int** moves) {

    int counterofcommas = 0;

    cout << "Your possible moves: ";
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (moves[i][j] == 1) {
                counterofcommas++;
            }
        }
    }

    //we have one less comma than options so we drop one
    counterofcommas--;
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (moves[i][j] == 1) {
                cout << "(" << i + 1 << "," << j + 1 << ")";
                if (counterofcommas > 0) {
                    cout << ",";
                    counterofcommas--;
                }
            }
        }
    }

    cout<<endl;
}

void ConsolePrinting::connectedToServerMessage() {
    cout << "Connected to server" << endl;
}
void ConsolePrinting::waitingForOpponentToConnect() {
    cout << "Waiting for other player to join..." << endl;
}
void ConsolePrinting::noPossibleMoves() {
    cout << "No possible moves. Play passes back to other player. Press any key to continue." << endl;
}

void ConsolePrinting:: noPossibleMovesForComp() {
    cout << "No possible move for computer. Play passes back to you. Press any key and then enter to continiue."<< endl;
}

void ConsolePrinting::newLine() {
    cout << "" << endl;
}

void ConsolePrinting::oPlayed() {
    cout << "O played ";
}

void ConsolePrinting::xPlayed() {
    cout << "X played ";
}

void ConsolePrinting::printCell(Cell* p) {
    cout << "(" << p->getI() + 1 << "," << p->getJ() + 1 << ")";
}
//current player: 1 - X the black, 2 - 0 the white
//currently the default type is human player - first player - 'x'
void ConsolePrinting::chooseGameOptions() {
    cout<<"Wecome to reversi:"<<endl;
    cout<<endl;
    cout<<"Choose an opponent type :"<<endl;
    cout<<"1. a game against computer"<<endl;
    cout<<"2. a human local player"<<endl;
    cout<<"3. a remote player"<<endl;
}
//printing if there are no valid options
void ConsolePrinting::noValidOption() {
    cout << "No valid option" << endl;
}

void ConsolePrinting::pressAnyKeyToCont() {
    cout << "Press any key to continue..." << endl;
}
void ConsolePrinting::writeBlackWin() {
    cout << "Winning Player: Black" << endl;
}

void ConsolePrinting::writeWhiteWIn() {
    cout << "Winning Player: White" << endl;
}

void ConsolePrinting::writeDraw() {
    cout << "It's a draw" << endl;
}
void ConsolePrinting::pressAnyKey() {
    cout << "Press any key to continue..." << endl;
}
/////
void ConsolePrinting::printClientMenu() {
    cout<<"Choose operation number and a name of the game (for 1,3)"<<endl;
    cout<<"1. Starting a new game."<<endl;
    cout<<"2. View list of waiting games"<<endl;
    cout<<"3. Join a game aginst remote player(that waits)"<<endl;
}

void ConsolePrinting::notAvailableGame() {
    cout << "Error! not a valid game name." << endl;
}

void ConsolePrinting::gameAlreadyExist() {
    cout << "Error! The game already exists." << endl;
}

void ConsolePrinting::gameNotOption() {
    cout << "Invalid option! Please choose again." << endl;
}

void ConsolePrinting::EnterNameOfGame() {
    cout << "Enter the name of your game" << endl;
}
//maybe to combine them both
void ConsolePrinting::printString(string stringToPrint) {
    cout << stringToPrint << endl;
}

void ConsolePrinting::printAvailableGames(string availableGamesNames) {
    printString(availableGamesNames);
}
