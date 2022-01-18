#ifndef PIECE_H
#define PIECE_H

#include "../include/path.h"
#include <vector>
#include <cctype>

enum class set { Black, White, Empty };

//get the opposite of a set (Example : the opposite of White = Black)
set opposite_of(const set side);

class piece {
	protected:
		char alias {' '};
		bool first_move;
		int max_distance;
		std::vector<path> valid_path;
		set side;

	public:
		piece(set _set = set::Black);

		//check if a path is legit (Example : Knight path[L]  -> _path = Vertical, output false )
		virtual bool is_legit_move(path _path, int distance) const;

		//get the alias for each piece (Example: Queen => D; King => R)
		//note: alias is Upper Case for Black and Lower Case for White
		char get_alias() const;

		//get the side of the piece 
		set get_side() const;

		//get the max possible distance for a piece 
		int get_max_distance() const;

		//check is the first move of a piece (useful for pawn and special move)
		bool is_first_move() const;

		//make first_move = false when moved
		void moved();
};

#endif //PIECE_H