#include "chessboard.h"
#include <iostream>

int main(void) {

    chessboard scacchiera {};
    /*
    std::cout << scacchiera.get_moves(std::make_pair(0, 1)).size();
    */
    scacchiera.print();
    scacchiera.move(std::make_pair(6, 0), std::make_pair(4, 0));
    scacchiera.print();
    scacchiera.move(std::make_pair(4, 0), std::make_pair(3, 0));
    scacchiera.print();
    scacchiera.move(std::make_pair(3, 0), std::make_pair(2, 0));
    scacchiera.print();
    scacchiera.move(std::make_pair(0, 1), std::make_pair(2, 0));
    scacchiera.print();
    scacchiera.move(std::make_pair(1, 1), std::make_pair(2, 1));
    scacchiera.print();
    scacchiera.move(std::make_pair(0, 2), std::make_pair(1, 1));
    scacchiera.print();
    scacchiera.move(std::make_pair(0, 3), std::make_pair(0, 1));
    scacchiera.print();
    scacchiera.move(std::make_pair(0, 4), std::make_pair(3, 4));
    scacchiera.print();
    scacchiera.move(std::make_pair(0, 4), std::make_pair(0, 3));
    scacchiera.print();
}