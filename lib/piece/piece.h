#ifndef PIECE_H
#define PIECE_H

#include "../path/path.h"
#include <vector>
#include <cctype>

enum class set {Black, White, Empty};
class invalid_set_exception{};
set opposite_of(const set _set);

class piece {

	protected:
		char alias;
		bool first_move;
		int max_distance;
		std::vector<path> valid_path;
		set side;
		
	public:
		piece(set _side = set::Black);
		virtual bool is_legit_move(path _path, int _path_length) const;

		char get_alias() const;
		set get_side() const;
		int get_max_distance() const;
		bool is_first_move() const;
		void moved();

};


#endif