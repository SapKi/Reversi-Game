//
// Created by sapir on 28/11/17.
//

#include "Cell.h"
Cell::Cell() {

}
Cell::Cell(int i, int j) {
    this->i = i;
    this->j = j;
}


int Cell::getI() {
    return this->i;
}
int Cell::getJ() {
    return this->j;
}

void Cell::setI(int i) {
    this->i = i;
}
void Cell::setJ(int j) {
    this->j = j;
}


