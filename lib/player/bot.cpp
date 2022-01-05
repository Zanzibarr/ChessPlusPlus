#include "player.h"
#include <cstdlib>
#include <ctime>

class bot : public player {

	private:
		std::vector<std::string> names {"BOTty Fisher", "Magnus BOTsen", "Garry KasparBOT", "Anatoly KarBOT", "Michail BOTvinnik"};
		std::string get_random_name () {
			srand(time(0));
			
			int random_index = rand()%names.size();
			return names.at(random_index);
		}

	public:
		bot(chessboard *_board, set _side) { 
			side = _side;
			game_board = _board;
			player_name = get_random_name();
		}

		bool move() {
			srand(time(0));

			coords start;
			coords end;

			std::vector<coords> pieces = game_board->get_pieces(side);
			std::vector<coords> valid_pieces;
			for(int i = 0; i < pieces.size(); i++){
				if(game_board->get_moves(pieces[i]).size() != 0) valid_pieces.push_back(pieces[i]);
			}

			int random_index_piece = rand()%valid_pieces.size();
			start.first = valid_pieces.at(random_index_piece).first;
			start.second = valid_pieces.at(random_index_piece).second;
			
			std::vector<coords> moves = game_board->get_moves(start);

			int random_index_move = rand()%moves.size();
			end.first = moves.at(random_index_move).first;
			end.second = moves.at(random_index_move).second;

			game_board->move(side, start, end);

			char start_letter = start.second + LETTERA;
			char end_letter = end.second + LETTERA;

			std::cout<<"the "<<player_name<<" move is: "<< start_letter<<start.first+1<<" "<<end_letter<<end.first + 1<<"\n";
			return true;
			
		}

};	