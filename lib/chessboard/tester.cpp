#include "chessboard.h"
#include <iostream>

int main(void) {

    chessboard scacchiera {};
    scacchiera.print();
    scacchiera.move(std::make_pair(6, 2), std::make_pair(4, 2));
    scacchiera.print();
    scacchiera.move(std::make_pair(4, 2), std::make_pair(3, 2));
    scacchiera.print();
    scacchiera.move(std::make_pair(1, 3), std::make_pair(3, 3));
    scacchiera.print();
    scacchiera.move(std::make_pair(3, 2), std::make_pair(2, 3));
    scacchiera.print();

}