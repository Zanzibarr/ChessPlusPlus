#ifndef PLAYER_H
#define PLAYER_H

#include "chessboard.h"
#include <regex>
#include <ctime>

class player {
	protected:
		chessboard *game_board;
		std::string name;
		set side;

	public:
		virtual bool move() = 0;
};

class human : public player {
	public:
		human(chessboard *board, set _side, std::string _name = "Miss Era Scacchi");
		~human();

		//move decided by human input
		virtual bool move();
};

class bot : public player {
	private:
		std::vector<std::string> names {"BOTty Fisher", "Magnus BOTsen", "Garry KasparBOT", "Anatoly KarBOT", "Michail BOTvinnik"};
		std::string get_random_name();
	public:
		bot(chessboard *board, set _side);
		~bot();
		
		//move decided by random value
		virtual bool move();
};

std::pair<char, int> matrix_to_chess(std::pair<int,int> matrix_coords);

#endif // PLAYER_H