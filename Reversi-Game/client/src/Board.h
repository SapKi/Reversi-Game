//Sapir Kikoz 207071192

#ifndef EXAP1_BOARD_H
#define EXAP1_BOARD_H

#include <string>
#include "Cell.h"
using namespace std;
/*
 * This class is building the board of the game - currently
 * initialize the matrix with default values and holds a method of printing
 */
class Board {

public:
    /*
     * This function is the constructor of the class - holds
     * a matrix that represents the board of the game and assing it
     * with the default values.
     */
    Board(int rows,int cols);
    //Enum for the status of the cell
    enum State {
        Empty, White, Black
    };

    Board(Board* copyBoard);
    /*
     * This function prints the matrix of the board with iconstndexes
     * and lines to separeate between the values.
     */
    void print();
    /**
     * this function returns the actual matrix that the board holds
     */
    State** getBoard();
    Board getBoardObject();
    /*
     * This function is the destructor of the class free the memory
     * that was allocated for the board
     */
    ~Board();
    int GetRows();
    int GetCoulmns();
    State** GetMatrix();
    State getCellStatus(Cell* p);
    void changeStatus(Cell* p, State s);

    State getCell(int row, int col);
    State setCell(int row, int col, State state);
private:
    int rows;
    int cols;
    State** matrix_;

};


#endif //EXAP1_BOARD_H
