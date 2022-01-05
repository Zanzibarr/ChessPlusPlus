#include "player.h"
#include <regex>
#include <cctype>
#include <iostream>

class human : public player {

	public:
		human(chessboard _board, set _side, std::string _name = "Miss Era Scacchi") : player(_board, _side, _name) { 
			side = _side;
			player_name = _name;
		}

		void move() {
			
    		std::regex reg1("([A-H-a-h])([1-8]) ([A-H-a-h])([1-8])");

			std::string input;

			coords start;
			coords target;

			std::cout<<player_name<<" insert your move: ";
			std::cin>>input;

			

		}

};