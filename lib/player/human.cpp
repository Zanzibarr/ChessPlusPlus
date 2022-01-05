#include "player.h"
#include <regex>
#include <cctype>
#include <iostream>

class human : public player {

	public:
		human(chessboard _board, set _side, std::string _name = "Miss Era Scacchi") /*: player(_board, _side, _name)*/ { 
			side = _side;
			player_name = _name;
		}

		void move() {
			
    		std::regex reg1("([A-H])([1-8]) ([A-H])([1-8])");
        	std::smatch match;

			std::string input;
			coords start;
			coords target;

			std::cout<<player_name<<" insert your move: ";
			std::getline(std::cin, input);

			for(int i = 0; i < input.size(); i++) { input[i] = std::toupper(input[i]); } //to Uppercase entire string
			
			if(input == "XX XX") game_board.print();
			else {
				if (std::regex_search(input, match, reg1) && match.size() >=5) {
					
					//coordinate iniziali
					start.first = std::stoi(match.str(2)) -1;
					start.second =  match.str(1)[0] - LETTERA;

					//coordinate finali					
					target.first = std::stoi(match.str(4)) -1;
					target.second =  match.str(3)[0] - LETTERA;
				}
				else throw illegal_path_exception();
				game_board.move(side, start, target);
			}
		}


};