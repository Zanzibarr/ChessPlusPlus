#ifndef PLAYER_H
#define PLAYER_H
#include "..\chessboard\chessboard.h"
#include <string>
#define LETTERA 'A'

class player {

	protected:
		chessboard game_board;
		std::string player_name;
		set side;

	public:
		player(chessboard _board, set _side = set::Black, std::string _name = " ");
		~player();

		virtual void move();

};

#endif