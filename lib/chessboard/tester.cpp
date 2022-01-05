#include "chessboard.cpp"
#include "../player/human.cpp"
#include <iostream>

#define LETTERA 'A'


int main(void) {

    //std::cout<<"Welcome to Chess++, chose a mode:\n\t1) Bot VS Bot\n\t2) Human VS Bot";

    chessboard scacchiera {};
    std::string name;
    scacchiera.print();
    std::cout<<"\n INSERISCI IL TUO NOME: ";
    std::getline(std::cin, name);

    player *giocatore= new human(&scacchiera, set::White, name);
    player *giocatore2 = new human(&scacchiera, set::Black, "GIUDA");

    char in;
    do {

        try {
            giocatore->move();
            giocatore2->move();
            std::cout<<"prova";
        }
        catch (illegal_move_exception e) {
            std::cout<<"mossa non valida, riprovare";
        }
        std::cout << "\n'q' to quit (other key to keep playing): ";
        std::cin >> in;
        std::cout << "\n";
        std::cin.ignore();
    } while (in != 'q');
    
}