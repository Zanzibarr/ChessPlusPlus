#include"include/player.h"
#include <iostream>
#include <fstream>

int main(int argc, char *argv[]) {

	std::cout << R"(
    ____             __           
   / __ \___  ____  / /___ ___  __
  / /_/ / _ \/ __ \/ / __ `/ / / /
 / _, _/  __/ /_/ / / /_/ / /_/ / 
/_/ |_|\___/ .___/_/\__,_/\__, /  
          /_/            /____/   
                                                                  
created by Riccardo Modolo, Matteo Zanella, Kabir Bertan)"<<"\n\n";
	std::ifstream in_file;
	std::fstream out_file;
	replayer* players[2];
	chessboard board;
	std::string name;
	int turn_decider = 0;



	if(argc <3) return -1;

	std::string mode = argv[1];

	for(int i = 0; i < mode.size(); i++){
		mode[i] = std::toupper(mode[i]);
	}

	if(mode=="V"){
		in_file.open(argv[2]);
	}

	if(mode=="F"){
		if(argc < 4) return -1;
		in_file.open(argv[2]);
		out_file.open(argv[3],std::ios::out);
	}

	if(!in_file.is_open()){
		std::cout << "File not found";
		return -1;
	}
	std::getline (in_file,name);
	players[0] = new replayer(&board,set::White,name);
	std::getline (in_file,name);
	players[1] = new replayer(&board,set::Black,name);

	while(in_file){
		std::string instruction;
		std::getline (in_file,instruction);
		if (instruction.compare("END") == 0)
			break;
		players[turn_decider]->move(instruction);
		std::cout << board;
		turn_decider = (turn_decider + 1)%2;
	}
	
	std::cout << "Fine Replay";
	
	return 0;
}