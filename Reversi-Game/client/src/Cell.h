//
// Created by sapir on 28/11/17.
//

#ifndef EX1FINAL_CELL_H
#define EX1FINAL_CELL_H


class Cell {
public:
    Cell(int i,int j);
    Cell();
    int getI();
    int getJ();
    void setI(int i);
    void setJ(int j);
private:
    int i;
    int j;
};


#endif //EX1FINAL_CELL_H
