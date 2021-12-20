#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include<utility>
#include <string>
#include "detail.h"
#include "piece.h"

class chessboard {

	private:
		std::pair<char, bool> matrix[8][8];

		set find_side(char _piece);

	public:
		chessboard();

		std::string print_chessboard() const;
		bool in_chessboard(const std::pair<int, int> &position) const;


		//return piece
		std::pair<char, bool> get_piece(const std::pair<int, int> &position) const;
		//returns true if a piece in _cur positon can reach _aim position (true if it's reachable and in _aim there is an eatable piece)
		bool is_reachable(const std::pair<int, int> &_cur, const std::pair<char, int> &_aim) const;
		//returns true if there is a piece of _side faction in _aim position
		bool is_occupied(const set _side, const std::pair<char, int> &_aim) const;
		//returns true if a piece in _side faction is eatable when it's in _aim position
		bool is_danger(const set &_side, const std::pair<char, int> &_aim) const;
		void move();

		bool is_path_legit(path _path, const std::pair<int, int> current,const std::pair<int, int> destination);

};

int path_length (const std::pair<int, int> current,const std::pair<int, int> destination);

#endif