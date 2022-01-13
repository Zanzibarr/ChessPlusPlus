#include "chessboard.cpp"
#include <regex>
#include <iostream>
#include <string>
#include <stdlib.h>

#define LETTERA 'A'

int main(void) {

    chessboard scacchiera{};

    std::vector<std::string> names {"Colla", "Riccardo"};
    std::vector<set> turn {set::White, set::Black};
    int counter = 0;
			
    std::regex reg1("^([A-H]){1}([1-8]){1} ([A-H]){1}([1-8]){1}$");
    std::smatch match;

    scacchiera.print();

    while (true) {

        bool failed;

        /*
        failed = true;

        while(failed) {

            std::cout << std::endl << names[counter] + " inserisci una mossa: ";
            std::string input;
			std::getline(std::cin, input);

            coords start;
            coords target;

            if (std::regex_search(input, match, reg1) && match.size() >=5) {

                //coordinate iniziali
                start.first = std::stoi(match.str(2)) -1;
                start.second =  match.str(1)[0] - LETTERA;

                //coordinate finali					
                target.first = std::stoi(match.str(4)) -1;
                target.second =  match.str(3)[0] - LETTERA;

            }

            std::pair<bool, bool> result;

            try {
                result = scacchiera.move(turn[counter], start, target);
            } catch (illegal_move_exception) { continue; }

            if (result.first && result.second) {

                scacchiera.print();
                std::cout << "Scacco matto!";
                exit(0);

            } else if(result.first && !result.second) {

                scacchiera.print();
                std::cout << "Patta!";
                exit(0);

            } else
                failed = (!result.first && !result.second);

            if (!failed) {
                scacchiera.print();
                counter = (counter + 1)%2;
            }

        }
        */

       failed = true;

        while(failed) {

            //std::cout << "\nTentativo del bot " << counter << ": ";

            std::vector<coords> pc = scacchiera.get_pieces(turn[counter]);

            std::srand(time(0));
            coords start = pc.at(std::rand()%pc.size());

            std::vector<coords> mv = scacchiera.get_moves(start, true);

            std::srand(time(0));

            if (mv.empty()) {
                //std::cout << " mossa fallita per pedina bloccata";
                continue;
            }

            coords target = mv.at(std::rand()%mv.size());

            std::pair<bool, bool> result;

            try {
                result = scacchiera.move(turn[counter], start, target);
            } catch (illegal_move_exception) {
                //std::cout << " mossa fallita per mossa illegale";
            }

            if (result.first && result.second) {

                scacchiera.print();
                std::cout << "Scacco matto!";
                exit(0);

            } else if(result.first && !result.second) {

                scacchiera.print();
                std::cout << "Patta!";
                exit(0);

            } else
                failed = (!result.first && !result.second);

            if (!failed) {
                //std::cout << start.first << ";" << start.second << " -> " << target.first << ";" << target.second;
                scacchiera.print();
            } //else
                //std::cout << " mossa fallita per scacco";
            
            if (!failed) {
                std::cout << "\nTentativo del bot " << counter << ": ";
                counter = ( counter + 1) % 2;
            }

        }

        /*
        std::string wait;
        std::cin >> wait;
        std::cin.ignore();
        */

    }

}
