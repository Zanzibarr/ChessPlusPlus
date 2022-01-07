#include "chessboard.cpp"
#include "../player/human.cpp"
#include "../player/bot.cpp"
#include <iostream>

#define LETTERA 'A'


int main(void) {

    //std::cout<<"Welcome to Chess++, chose a mode:\n\t1) Bot VS Bot\n\t2) Human VS Bot";

    chessboard scacchiera {};
    std::string name;
    scacchiera.print();
    std::cout<<"\n\n";
    /*std::cout<<"\n INSERISCI IL TUO NOME: ";
    std::getline(std::cin, name);*/

    player *giocatore = new human(&scacchiera, set::White, "Matteo");
    player *giocatore2 = new human(&scacchiera, set::Black);

    bool cond;
    bool cond2;

    char in;

    for(int i = 0; i < 500; i++) {
        try{
        do {
            cond = giocatore->move();
        }
        while(cond != true);
        do {
            cond2 = giocatore2->move();
        }
        while(cond2 != true);
        scacchiera.print();
        std::cin.ignore();
        } 
        catch (illegal_move_exception) {i--;};
    }
    
}