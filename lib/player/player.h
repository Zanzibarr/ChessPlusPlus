#ifndef PLAYER_H
#define PLAYER_H
#include "..\chessboard\chessboard.h"
#include <string>
#include <cstdlib>
#include <ctime>
#include <regex>

#define LETTERA 'A'

class player {

	protected:
		chessboard *game_board;
		std::string player_name;
		set side;

	public:
		virtual bool move() = 0;

};

#endif