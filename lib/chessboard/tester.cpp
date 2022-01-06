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

    player *giocatore = new bot(&scacchiera, set::White);
    player *giocatore2 = new bot(&scacchiera, set::Black);

    bool cond;
    bool cond2;

    char in;

    do {
        try{
            do{
                cond = giocatore->move();
            }while(cond == false);
            do{
                cond2 = giocatore2->move();
            }while(cond2 == false);
            scacchiera.print();
        } 
        catch (illegal_move_exception) {};
        std::cout<<"\nq to quit: ";
        std::cin>>in;
        std::cin.ignore();
    }while(in != 'q');
    
    
}