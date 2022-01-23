#include "include/player.h"
#include <iostream>
#include <fstream>


int main (int argc, char* argv[]) {
	std::string mode;
	
	if(argc == 2) mode = argv[1];
	else {
		std::cout<<"Invalid Arguments";
		return -1;
	}

	for(int i = 0; i < mode.size(); i++) {
		mode[i] = std::toupper(mode[i]);
	}
	int in = 0;
	
	if(mode == "PC") { in = 2; }
	else if( mode == "CC") {in = 1;}
	else {
		std::cout<<"Invalid Arguments";
		return -1;
	}

	std::srand(time(0));
	chessboard board;
	player *players[2];
	std::string player_name;

	int turn_decider = 0;
	int max_turn = 100;
	bool end = false;
	int turn = 0;

	std::cout<<R"(
   ________                                
  / ____/ /_  ___  __________     __    __ 
 / /   / __ \/ _ \/ ___/ ___/  __/ /___/ /_
/ /___/ / / /  __(__  |__  )  /_  __/_  __/
\____/_/ /_/\___/____/____/    /_/   /_/   
                                                                                      
created by Riccardo Modolo, Matteo Zanella, Kabir Bertan)"<<"\n\n";

	switch (in) {
	case 1:
		std::cout<<"you chose Computer vs Computer, please, insert max round (or enter to default 100): ";
		std::cin>>max_turn;
		players[0] = new bot(&board, set::White);
		players[1] = new bot(&board, set::Black);
		while(!end && turn < max_turn*2){
			end = players[turn_decider]->move();
			turn_decider = (turn_decider + 1)%2;
			turn++;
		}
		if(turn == max_turn*2) std::cout<<"Draw for max move reached!";
		break;
	
	case 2:
		std::cout<<"you chose Player vs Computer, please, insert your name (or enter to default name): ";
		std::getline(std::cin, player_name);
		int rand_side = rand()%2;

		if(rand_side == 0){
			players[0] = new human(&board, set::White, player_name);
			players[1] = new bot(&board, set::Black);
		}
		else {
			players[0] = new bot(&board, set::White);
			players[1] = new human(&board, set::Black, player_name);
		}
		while(!end){
			end = players[turn_decider]->move();
			turn_decider = (turn_decider + 1)%2;
			if (board.check(players[turn_decider]->get_side()))
				std::cout << "Attento " << players[turn_decider]->get_name() << "... Sei sotto scacco.\n";
		}
		break;
	}

	std::cout << board;

	std::string white = players[0]->get_name().substr(0, 3);
	std::string black = players[1]->get_name().substr(0, 3);
	
	std::string filename = white + "_vs_" + black + "_" + mode;
	std::string suffiss;
	std::fstream myfile;

	int counter = 1;

	do {
		suffiss = "(" + std::to_string(counter) + ").txt";
		counter++;
	} while((std::ifstream(filename + suffiss)).good());
	
	myfile.open(filename + suffiss, std::ios::out);

	std::vector<std::pair<coords, coords>> history = board.get_history();

	myfile<<players[0]->get_name()<<"\n"<<players[1]->get_name()<<"\n";
	for(int i = 0; i < history.size(); i++) {
		if(history[i].first.first == -1) {
			std::pair<char, char> start = std::make_pair('P', history[i].first.second);
			std::pair<char, int> end = matrix_to_chess(history[i].second);
			myfile<<start.first<<" "<<start.second<<" "<<end.first<<end.second<<"\n";
		}
		else {
			std::pair<char, int> start = matrix_to_chess(history[i].first);
			std::pair<char, int> end = matrix_to_chess(history[i].second);
			myfile<<start.first<<start.second<<" "<<end.first<<end.second<<"\n";
		}
	}

	myfile << "END";
	myfile.close();

	return 0;
}