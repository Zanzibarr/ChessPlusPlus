#ifndef PLAYER_H
#define PLAYER_H

#include "chessboard.h"
#include <regex>
#include <ctime>

/**
 * 
 * @file player.h
 * @author Riccardo Modolo (riccardo.modolo.1@studenti.unipd.it)
 * 
 * @brief The interface consists in creation of generic player class its derived classes. 
 * 
 * @version 0.4
 * @date 2022-01-15
 * 
 */

//the generic full virtual player class
class player {
	protected:
		chessboard *game_board; //the reference to the chessboard on which to make moves
		std::string name; //the name of the player
		set side; //the side of the player [Black, White]

	public:
		virtual bool move() = 0;
		virtual std::string get_name() const = 0;
		set get_side() const { return side; }
};

//human is a player controllable from a real person
class human : public player {
	public:
		human(chessboard *board, set _side, std::string _name);
		~human();

		//move decided by human input
		virtual bool move();
		virtual std::string get_name() const;
};

//made by: Kabir Bertan (kabir.bertan@studenti.unipd.it)
//
//bot is a player who choose random move in a range of possible moves
class bot : public player {
	private:
		std::vector<std::string> names {"BOTty Fisher", "Magnus BOTsen", "Garry KasparBOT", "Anatoly KarBOT", "Michail BOTvinnik"};
		std::string get_random_name();
	public:
		bot(chessboard *board, set _side);
		~bot();
		
		//move decided by random value
		virtual bool move();
		virtual std::string get_name() const;
};

//made by: Kabir Bertan (kabir.bertan@studenti.unipd.it)
//
//replayer is a player-like class, in this case the function move have a string argument.
//this class is uses in replay.
class replayer {
	protected:
		chessboard *game_board;
		std::string name;
		std::string last_move;
		set side;
	public:
		replayer(chessboard *board, set _side, std::string _name);
		void move(std::string arg);
		std::string get_name() const;
		std::string print_move() const;
};

//convert a matrix format coordinate [0 0] to  chess coordinate [A 1]
std::pair<char, int> matrix_to_chess(coords matrix_coords);

//convert a chess format coordinate [A 1] to  matrix coordinate [0 0]
//args in pair are string 'cause we reach after regex search.
coords chess_to_matrix(std::pair<std::string, std::string> chess_coords);

#endif // PLAYER_H