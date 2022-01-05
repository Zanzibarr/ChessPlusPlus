#include "chessboard.cpp"
#include <iostream>
#include <regex>

#define LETTERA 'A'

int main(void) {

    //std::cout<<"Welcome to Chess++, chose a mode:\n\t1) Bot VS Bot\n\t2) Human VS Bot";

    chessboard scacchiera {};
    scacchiera.print();
    std::regex reg1("([A-H-a-h])([1-8]) ([A-H-a-h])([1-8])");

    char in;
    do {
        coords start;
        coords end;
        std::string start_reaching;
        std::string end_reaching;
        std::smatch match;

        std::cout << "\nstart: ";
        std::getline(std::cin, start_reaching);

        if(start_reaching == "XX XX" || start_reaching == "xx xx") {
            scacchiera.print();
        }
        else {
            std::cout<<"ce entro";
            if (std::regex_search(start_reaching, match, reg1) && match.size() > 1) {
                if(match.size() != 5) throw illegal_path_exception();

                start.second =  std::toupper(match.str(1)[0]) - LETTERA;
                end.second = std::toupper(match.str(3)[0]) - LETTERA;
                start.first = std::stoi(match.str(2)) -1;
                end.first = std::stoi(match.str(4)) -1;
            } else {
                break;
            }
            scacchiera.move(start, end);
        }        

        std::cout << "\n'q' to quit (other key to keep playing): ";
        std::cin >> in;
        std::cout << "\n";
        std::cin.ignore();
    } while (in != 'q');

    scacchiera.print();
}