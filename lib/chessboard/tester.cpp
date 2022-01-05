#include "chessboard.cpp"
#include "../player/human.cpp"
#include <iostream>
#include <regex>

#define LETTERA 'A'

int main(void) {

    //std::cout<<"Welcome to Chess++, chose a mode:\n\t1) Bot VS Bot\n\t2) Human VS Bot";

    chessboard scacchiera {};
    scacchiera.print();
    std::cout<<"\n";
    player *giocatore = new human(scacchiera, set::White);

    char in;
    do {

        giocatore->move();
        std::cout << "\n'q' to quit (other key to keep playing): ";
        std::cin >> in;
        std::cout << "\n";
        std::cin.ignore();
    } while (in != 'q');

    scacchiera.print();
}