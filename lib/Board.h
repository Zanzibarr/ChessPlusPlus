#ifndef BOARD_H
#define BOARD_H

#include<utility>
class board {

	public:
		class OutOfChessboardException{};
		board();
		~board();

		//return piece
		void get_piece(std::pair<char, int> position);
		bool is_in_chessboard();
		void move();


		

};

#endif