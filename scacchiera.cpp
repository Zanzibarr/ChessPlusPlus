#include "include/player.h"


int main (void) {

	std::srand(time(0));
	chessboard board;
	player *players[2];
	std::string player_name;

	int max_turn = 100;
	int turn = 0;
	int turn_decider = 0;
	bool end = false;

	std::cout<<R"(
   ___ _                                    
  / __\ |__   ___  ___ ___     _       _   
 / /  | '_ \ / _ \/ __/ __|  _| |_   _| |_ 
/ /___| | | |  __/\__ \__ \ |_   _| |_   _|
\____/|_| |_|\___||___/___/   |_|     |_|  
                                           
	)"<<"\n";

	std::cout<<R"(select one mode:
	1) Bot Vs Bot
	2) Human Vs Bot)"<<"\n";

	int in = 0;
	do {
		std::cout<<"insert 1 or 2: ";
		std::cin>>in;
		std::cin.ignore();
	}while(in != 1 && in != 2);

	switch (in) {
	case 1:
		std::cout<<"you chose bot vs bot, please, insert max round (or enter to default 100): ";
		std::cin>>max_turn;
		players[0] = new bot(&board, set::White);
		players[1] = new bot(&board, set::Black);
		while(!end && turn < max_turn*2){
			end = players[turn_decider]->move();
			turn_decider = (turn_decider + 1)%2;
			turn++;
		}
		if(turn >= max_turn*2) std::cout<<"Draw for max move reached!";
		break;
	
	case 2:
		std::cout<<"you chose human vs bot, please, insert your name (or enter to default name): ";
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
		}
		break;
	}


	return 0;
}