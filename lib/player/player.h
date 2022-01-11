#ifndef PLAYER_H
#define PLAYER_H
#include "..\chessboard\chessboard.h"
#include <string>
#include <cstdlib>
#include <ctime>
#include <regex>

#define FIRST_LETTER 'A'

class player {

	protected:
		chessboard *game_board;
		std::string player_name;
		set side;

	public:
		virtual bool move() = 0;

};

//coordinate converter
std::pair<int, int> chess_to_matrix(std::pair<char, int> chess_coords) {

	int row = chess_coords.second - 1;
	int col = chess_coords.first - FIRST_LETTER;

	return std::pair<int,int>{row, col};
};
std::pair<char, int> matrix_to_chess(std::pair<int,int> matrix_coords) {

	char letter = matrix_coords.second + FIRST_LETTER;
	int number = matrix_coords.first + 1;

	return std::pair<char,int>{letter, number};
};

#endif