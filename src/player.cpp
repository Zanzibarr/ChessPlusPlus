#include "../include/player.h"

/**
 * 
 * @file player.cpp
 * @author Riccardo Modolo (riccardo.modolo.1@studenti.unipd.it)
 * 
 * @brief implementation of pieces.h
 * 
 * @version 0.4
 * @date 2022-01-15
 * 
 */

//START HUMAN IMPLEMENTATION
human::human(chessboard *board, set _side, std::string _name) {
	game_board = board;
	side = _side;
	name = _name;
}

human::~human() {
	game_board = nullptr;
}

bool human::move() {

	std::regex move_expression("^([A-H-a-h]){1}([1-8]){1} ([A-H-a-h]){1}([1-8]){1}$"); //A5 B6
	char _side = (side == set::White) ? 'w' : 'B';
	std::smatch match_container;
	std::string input;
	bool failed = true;
	bool print = false;
	bool draw_condition = false;

	while(failed) {
		print = false;
		draw_condition = false;
		std::cout<<name<<" ["<<_side<<"]"<<" insert a move, or XX XX to view the board, DRAW to ask the draw: ";
		std::getline(std::cin, input);

		//upperstring all input
		for(int i = 0; i < input.length(); i++) { 
			input[i] = std::toupper(input[i]); 
		}
		
		if(input.compare("XX XX") == 0) {
			std::cout<<*game_board;
			print = true;
		}
		else if(input.compare("DRAW") == 0) {
			int draw = rand()%10;
			std::cout<<"the enemy say: ";
			if(draw == 0) {
				std::cout<<"accept the draw\n";
				return true;
			}
			else {
				std::cout<<"deny the draw\n";
				draw_condition = true;
			}
		}

		coords start;
		coords end;

		if(std::regex_search(input, match_container, move_expression) && match_container.size() >=5) {
			//coordinate iniziali
			start = chess_to_matrix(std::make_pair(match_container.str(1), match_container.str(2)));
			
			//coordinate finali	
			end = chess_to_matrix(std::make_pair(match_container.str(3), match_container.str(4)));
		}

		std::pair<bool,bool> move_result; //check chessboard.h for more information

		try {
			move_result = game_board->move(side, start, end);
		} catch (illegal_move_exception) {
			if(!print || !draw_condition)std::cout<<"Oh, you can't do that\n";
		}

		//check chessboard.h for true true condition
		if(move_result.first && move_result.second) { 
			std::cout<<"Checkmate!";
			return true;
		}
		//check chessboard.h for true false condition
		else if(move_result.first && !move_result.second) {
			std::cout<<"Draw";
			return true;
		}
		else {
			failed = (!move_result.first && !move_result.second);
		}

		if(!failed) {
			if(game_board->is_promotion(end)){
				char piece;
				bool exit_cond;

				do {
					std::cout << std::endl << "\nSelect the piece you wish to have your pawn promoted to: 't', 'c', 'a', 'd': ";
					std::string in;
					std::cin >> in;
					piece = std::tolower(in[0]);
					std::cin.ignore();

					exit_cond = piece == 'a' || piece == 'c' || piece == 'd' || piece == 't';
					
				} while(!exit_cond);

				game_board->do_promotion(end, piece);
			}
		}
	}
	
	return false;
}

std::string human::get_name() const {
	return name;
}
//END HUMAN IMPLEMENTATION


//START BOT IMPLEMENTATION
std::string bot::get_random_name() {
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

bot::bot(chessboard *board, set _side) {
	game_board = board;
	side = _side;
	name = get_random_name();
}

bot::~bot() {
	game_board = nullptr;
	names.clear();
}

bool bot::move() {
	bool failed = true;
	char _side = (side == set::White) ? 'w' : 'B';
	std::vector<coords> pieces = game_board->get_pieces(side);
	std::vector<std::pair<coords, coords>> all_moves;

	for (int i = 0; i < pieces.size(); i++) {
		std::vector<coords> mv = game_board->get_moves(pieces.at(i), true);
		for (int j = 0; j < mv.size(); j++) 
			all_moves.push_back(std::make_pair(pieces.at(i), mv.at(j)));
	}

	while(failed) {

		std::srand(time(0));
		int rand_index = std::rand()%all_moves.size();

		coords start = all_moves.at(rand_index).first;
		coords end = all_moves.at(rand_index).second;

		std::pair<bool, bool> result;

		try {
			result = game_board->move(side, start, end);
		} catch (illegal_move_exception) {
			all_moves.erase(all_moves.begin() + rand_index);
			continue;
		}

		if(result.first && result.second) {
			std::cout<<"Checkmate!";
			return true;
		}
		else if(result.first && !result.second) {
			std::cout<<"Draw.";
			return true;
		}
		else {
			failed = (!result.first && !result.second);
		}

		if(!failed) {
			std::pair<char, int> start_print = matrix_to_chess(start);
			std::pair<char, int> end_print = matrix_to_chess(end);
			
			std::cout<<name<<" ["<<_side<<"]"<<" moved from ";
			std::cout<<start_print.first<<start_print.second<<" to "<<end_print.first<<end_print.second<<std::endl;

			if(game_board->is_promotion(end)) {
				std::vector<char> pieces{'t', 'c', 'a', 'd'};

				std::srand(time(0));
				char piece = pieces.at(std::rand()%4);

				game_board->do_promotion(end, piece);
			}
		}
		else {
			all_moves.erase(all_moves.begin() + rand_index);
		}


	}

	return false;
}

std::string bot::get_name() const {
	return name;
}
//END BOT IMPLEMENTATION

/**
 * 
 * @author Kabir Bertan (kabir.bertan@studenti.unipd.it)
 * 
 * @brief implementation of replayer class
 * 
 * @version 0.4
 * @date 2022-01-15
 * 
 */

replayer::replayer (chessboard *board, set _side, std::string _name) {
	game_board = board;
	name = _name;
	side = _side;
}

void replayer::move (std::string arg) {
	std::regex move_expression("^([A-H-a-h]){1}([1-8]){1} ([A-H-a-h]){1}([1-8]){1}$"); //A5 B6
	char _side = (side == set::White) ? 'w' : 'B';
	std::smatch match_container;

	if(arg[0]=='P'){
		char piece = arg[2];
		coords end;
		end.first = arg[5]-49;
		end.second = arg[4]-LETTER;
		game_board->do_promotion(end, piece);
		return;

	}
	coords start;
	coords end;

	if(std::regex_search(arg, match_container, move_expression) && match_container.size() >=5) {
		//coordinate iniziali
		start = chess_to_matrix(std::make_pair(match_container.str(1), match_container.str(2)));
		
		//coordinate finali	
		end = chess_to_matrix(std::make_pair(match_container.str(3), match_container.str(4)));
	}
	std::pair<bool,bool> move_result = game_board->move(side, start, end);

	std::pair<char, int> start_print = matrix_to_chess(start);
	std::pair<char, int> end_print = matrix_to_chess(end);
	
	last_move = name + " [" + _side +"] moved from " + start_print.first +""+ std::to_string(start_print.second) + " to " + end_print.first + std::to_string(end_print.second);


	if(move_result.first && move_result.second) { 
		last_move = "Checkmate!";
		return;
	}
	//check chessboard.h for true false condition
	else if(move_result.first && !move_result.second) {
		last_move = "Draw!";
		return;
	}

}

std::string replayer::get_name() const{
	return name; 
}

std::string replayer::print_move() const {
	return last_move;
}

std::pair<char, int> matrix_to_chess(coords matrix_coords) {

	char letter = matrix_coords.second + 'A';
	int number = matrix_coords.first + 1;

	return std::make_pair(letter, number);
};

//start = chess_to_matrix(std::make_pair(match_container.str(1), match_container.str(2)));
coords chess_to_matrix(std::pair<std::string, std::string> chess_coords) {

	//end.first = std::stoi(match_container.str(2)) -1;
	//end.second =  match_container.str(1)[0] - LETTER;

	int row = std::stoi(chess_coords.second) -1;
	int col = chess_coords.first[0] - LETTER;

	return std::make_pair(row, col);
}