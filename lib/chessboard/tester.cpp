#include "chessboard.h"
#include <iostream>
#include <regex>

#define LETTERA 'A'

int main(void) {

    //std::cout<<"Welcome to Chess++, chose a mode:\n\t1) Bot VS Bot\n\t2) Human VS Bot";

    chessboard scacchiera {};
    scacchiera.print();
    std::regex reg1("([A-H])([1-8])");

    char in;
    char input;
    do {
        coords start;
        coords end;
        std::string start_reaching;
        std::string end_reaching;
        std::smatch match;

        std::cout << "\nstart: ";
        std::cin >> start_reaching;
        if (std::regex_search(start_reaching, match, reg1) && match.size() > 1) {
            std::string s = match.str(1);
            start.second =  s[0] - LETTERA;
            s = match.str(2);
            start.first = std::stoi(s) -1;
        } else {
            break;
        }
        std::cout << "\nend: ";
        std::cin >> end_reaching;
        if (std::regex_search(end_reaching, match, reg1) && match.size() > 1) {
            std::string s = match.str(1);
            end.second =  s[0] - LETTERA;
            s = match.str(2);
            end.first = std::stoi(s) -1;
        } else {
            break;
        }


        scacchiera.move(start, end);
        scacchiera.print();

        std::cout << "\n'q' to quit (other key to keep playing): ";
        std::cin >> in;
        std::cout << "\n";

    } while (in != 'q');

    scacchiera.print();
}