#include "player.h"
#include <cstdlib>
#include <ctime>

class bot : public player {

	private:
		std::vector<std::string> names {"BOTty Fisher", "Magnus BOTsen", "Garry KasparBOT", "Anatoly KarBOT", "Michail BOTvinnik"};
		std::string get_random_name () {
			static int prev_value = -1;
			srand(time(0));
			int random_index;
			do {
				random_index = rand()%names.size();
			}
			while(prev_value == random_index);
			prev_value = random_index;
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

			for(int i = 0; i < valid_pieces.size(); i++) {
				char lett = valid_pieces.at(i).second + LETTERA;
				std::cout<<lett<<valid_pieces.at(i).first+1<<"\n";
			} 
			std::cout<<"------------------------------------------\n";

			int random_index_piece = rand()%valid_pieces.size();
			start.first = valid_pieces.at(random_index_piece).first;
			start.second = valid_pieces.at(random_index_piece).second;

			char l1 = start.second + LETTERA;
			std::cout<<l1<<start.first+1<<"\n";
			std::cout<<"------------------------------------------\n";
			
			std::vector<coords> moves = game_board->get_moves(start);
			std::vector<coords> valid_moves;
			int size = moves.size();

			piece *p = (game_board->piece_at_pos(start));
			if(is<pawn>(*p)) {

				for(int i = 0; i < moves.size(); i++) {
					if(!game_board->is_pawn_eat(path::Diagonal, start, moves.at(i)) && get_path(start, moves.at(i)) != path::Vertical){
						size--;
					} 
				}

				for(int i = 0; i < size; i++){
					valid_moves.push_back(moves.at(i));
				}
				
			}
			else { valid_moves = moves; }

			if(valid_moves.size() == 0){ return false; }
			else {

			for(int i = 0; i < valid_moves.size(); i++) {
				char lett = valid_moves.at(i).second + LETTERA;
				std::cout<<lett<<valid_moves.at(i).first+1<<"\n";
			} 
			std::cout<<"------------------------------------------\n";

			int random_index_move = rand()%valid_moves.size();
			end.first = valid_moves.at(random_index_move).first;
			end.second = valid_moves.at(random_index_move).second;
			char l2 = end.second + LETTERA;
			std::cout<<l2<<end.first+1<<"\n";
			std::cout<<"------------------------------------------\n";

			

			game_board->move(side, start, end);

			
			char start_letter = start.second + LETTERA;
			char end_letter = end.second + LETTERA;

			std::cout<<"the "<<player_name<<" move is: "<< start_letter<<start.first+1<<" "<<end_letter<<end.first + 1<<"\n";
			}
			return true;
		}

};	