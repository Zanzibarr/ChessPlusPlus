#include "chessboard.h"
#include <iostream>

int main(void) {

    chessboard scacchiera {};
    /*
    std::cout << scacchiera.get_moves(std::make_pair(0, 1)).size();
    */
    scacchiera.print();
    
    char in;
    do {

        std::cout << "\nstart: ";
        coords start;
        std::cin >> start.first >> start.second;
        std::cout << "\nend: ";
        coords end;
        std::cin >> end.first >> end.second;

        scacchiera.move(start, end);
        scacchiera.print();

        std::cout << "\n'q' to quit (other key to keep playing): ";
        std::cin >> in;
        std::cout << "\n";

    } while (in != 'q');

    scacchiera.print();
}