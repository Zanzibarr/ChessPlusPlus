#include "chessboard.h"
#include <iostream>

int main(void) {

    chessboard scacchiera {};
    scacchiera.print();
    scacchiera.pawn_eat(std::make_pair(1, 3), std::make_pair(2, 3));
    scacchiera.pawn_eat(std::make_pair(1, 2), std::make_pair(2, 2));
    scacchiera.pawn_eat(std::make_pair(1, 4), std::make_pair(2, 4));
    scacchiera.print();
    std::vector<coords> ret = scacchiera.get_moves(std::make_pair(0,6));
    std::cout << std::endl << ret.size() << std::endl;
    for (int i = 0; i < ret.size(); i++) {
        std::cout << ret[i].first << "-" << ret[i].second << std::endl;
    }

}