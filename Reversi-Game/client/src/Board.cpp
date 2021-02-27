//Sapir Kikoz 207071192

#include "Board.h"
#include <iostream>


using namespace std;
/*
 * This class is building the board of the game - currently
 * initialize the matrix with default values and holds a method of printing
 */
Board::Board(int rows ,int cols) {
    /*
     * This function is the constructor of the class - holds
     * a matrix that represents the board of the game and assing it
     * with the default values.
     * input: the number of rows and columns of the matrix
     */
    this->rows = rows;
    this->cols = cols;
    this->matrix_= new State*[this->rows];
    for (int i = 0; i < this->rows; ++i)
        matrix_[i] = new State[this->cols];

        //assinging the matrix by the default values
        for (int i = 0; i < this->rows; ++i) {
            for (int j = 0; j < this->cols; ++j) {
                this->matrix_[i][j] = Empty;
            }
        }
    this->matrix_[3][4] = this->matrix_[4][3] = Black;
    this->matrix_[4][4] = this->matrix_[3][3] = White;
}

Board::Board(Board* otherBoard) {
    /*
     * This function is the copy constructor of the class - holds
     * a matrix that represents the board of the game and assing it
     * with the default values.
     * input: the number of rows and columns of the matrix
     */
    this->rows = otherBoard->GetRows();
    this->cols = otherBoard->GetCoulmns();
    this->matrix_= new State*[this->rows];
    for (int i = 0; i < this->rows; ++i)
        matrix_[i] = new State[this->cols];

    //assinging the matrix by the default values
    for (int i = 0; i < this->rows; ++i) {
        for (int j = 0; j < this->cols; ++j) {
            this->matrix_[i][j] = otherBoard->getCell(i,j);
        }
    }
}

int Board::GetRows(){
    return this->rows;
}

int Board::GetCoulmns() {
    return this->cols;
}

Board::State** Board::GetMatrix(){
    return this->matrix_;
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

Board::State** Board::getBoard(){
    return this->matrix_;
}
Board Board::getBoardObject(){
    return *this;
}


/*
 * This function is the destructor of the class - it free
 * the memory that was allocated for the board of the game
 */
Board::~Board() {
        for (int i = 0; i < this->rows; ++i)
            delete [] this->matrix_[i];
        delete [] this->matrix_;
}

Board::State Board::getCellStatus(Cell* p) {
    if (p->getI() >= 0 && p->getI() < this->GetRows() && p->getJ() >= 0 && p->getJ() < this->GetRows()) {
        return this->matrix_[p->getI()][p->getJ()];
    }
}

void Board::changeStatus(Cell* p, State s) {
    if (p->getI() >= 0 && p->getI() < this->GetRows() && p->getJ() >= 0 && p->getJ() < this->GetRows()) {
        this->matrix_[p->getI()][p->getJ()] = s;
    }
}

Board::State Board::getCell(int row, int col) {
    return this->matrix_[row][col];
}

Board::State Board::setCell(int row, int col, State state) {
    this->matrix_[row][col] = state;
}
