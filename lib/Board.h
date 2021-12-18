#ifndef BOARD_H
#define BOARD_H

#include<utility>
class board {

	public:
		board();

		//return piece
		void get_piece(std::pair<char, int> &position);
		bool is_in_chessboard(); //check leget A G
		bool is_reachable(const set side, const std::pair<char, int> &position);
		void move();

};

#endif