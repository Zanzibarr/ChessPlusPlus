#include "player.h"

class human : public player {

	public:
		human(chessboard *_board, set _side, std::string _name = "Miss Era Scacchi") { 
			side = _side;
			game_board = _board;
			player_name = _name;
		}
		bool move() {
			
    		std::regex reg1("^([A-H]){1}([1-8]){1} ([A-H]){1}([1-8]){1}$");
        	std::smatch match;

			std::string input;
			coords start;
			coords target;

			std::cout<<player_name<<" insert your move: ";
			std::getline(std::cin, input);

			for(int i = 0; i < input.size(); i++) { input[i] = std::toupper(input[i]); } //Uppercase entire string
			
			if(input == "XX XX") {
				game_board->print();
				return false;
			}
			else {
				if (std::regex_search(input, match, reg1) && match.size() >=5) {
					
					//coordinate iniziali
					start.first = std::stoi(match.str(2)) -1;
					start.second =  match.str(1)[0] - LETTERA;

					//coordinate finali					
					target.first = std::stoi(match.str(4)) -1;
					target.second =  match.str(3)[0] - LETTERA;
				}
				else throw illegal_move_exception();

				game_board->move(side, start, target);
				return true;
			}
		}

};