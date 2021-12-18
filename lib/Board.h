#ifndef BOARD_H
#define BOARD_H

#include<utility>
#include "piece.h"

class board {

	public:

		std::pair<piece, bool> matrix[8][8];

		board();

		//return piece
		std::pair<piece, bool> get_piece(const std::pair<char, int> &position) const;
		bool is_in_chessboard(); //check leget A G
		//returns true if a piece in _cur positon can reach _aim position (true if it's reachable and in _aim there is an eatable piece)
		bool is_reachable(const std::pair<char, int> &_cur, const std::pair<char, int> &_aim) const;
		//returns true if there is a piece of _side faction in _aim position
		bool is_occupied(const set _side, const std::pair<char, int> &_aim) const;
		//returns true if a piece in _side faction is eatable when it's in _aim position
		bool is_danger(const set &_side, const std::pair<char, int> &_aim) const;
		void move();

};

#endif