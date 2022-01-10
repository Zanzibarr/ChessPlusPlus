#include "lib/chessboard/chessboard.cpp"
#include <regex>
#include <iostream>
#include <string>

#define LETTERA 'A'

int main(void) {

    chessboard scacchiera{};

    std::vector<std::string> names {"Matteo", "Riccardo"};
    std::vector<set> turn {set::White, set::Black};
    int counter = 0;
			
    std::regex reg1("^([A-H]){1}([1-8]){1} ([A-H]){1}([1-8]){1}$");
    std::smatch match;

    while (true) {

        bool failed = true;

        while(failed) {

            std::cout << names[counter] + " inserisci una mossa: ";
            std::string input;
			std::getline(std::cin, input);
			if(input == "XX XX") {
				scacchiera.print();
			} else {
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
                std::pair<bool, bool> result = scacchiera.move(turn[counter], start, target);
                if (result.first && result.second) {
                    std::cout << "Scacco matto!";
                    exit(0);
                } else if(result.first && !result.second) {
                    std::cout << "Patta!";
                    exit(0);
                } else {
                    failed = (!result.first && !result.second);
                }
            }
        }

        counter = (counter+1)%2;

    }

}
