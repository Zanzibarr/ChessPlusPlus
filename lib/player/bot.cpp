#include "player.h"
#include <cstdlib>
#include <ctime>

class bot : public player {

	private:
		std::vector<std::string> names {"BOTty Fisher", "Magnus BOTsen", "Garry KasparBOT", "Anatoly KarBOT", "Michail BOTvinnik"};
		std::string get_random_name () {
			srand(time(NULL));
			
			int random_index = rand()%names.size();
			return names.at(random_index);
		}

	public:
		bot(chessboard _board, set _side) { 
			side = _side;
			player_name = get_random_name();
		}

		void move() {


			std::cout<<"the "<<player_name<<" move is: "<<"A5 B6";
		}

};	