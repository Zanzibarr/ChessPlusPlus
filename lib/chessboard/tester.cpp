#include "chessboard.h"
#include <iostream>

int main(void) {

    chessboard scacchiera {};
    scacchiera.print();
    std::vector<coords> mosse = scacchiera.get_moves(std::make_pair(0, 1));
    scacchiera.move(std::make_pair(0, 1), std::make_pair(2, 0));
    scacchiera.print();
    scacchiera.move(std::make_pair(1, 1), std::make_pair(2, 1));
    scacchiera.print();
    scacchiera.move(std::make_pair(0, 2), std::make_pair(1, 1));
    scacchiera.print();
    scacchiera.move(std::make_pair(0, 3), std::make_pair(0, 1));
    scacchiera.print();

}