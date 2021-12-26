#ifndef PIECE_H
#define PIECE_H

#include "../path/path.cpp"
#include <vector>
#include <cctype>

enum class set {Black, White};
class invalid_set_exception{};
set opposite_of(const set _set);

class piece {

	protected:
		char alias;
		bool first_move;
		std::vector<path> valid_path;
		set side;
		
	public:
		piece(set _side = set::Black);
		virtual bool is_legit_move(path _path, int _path_length) const;

		char get_alias() const;
		set get_side() const;
		bool is_first_move() const;
		void moved();

};


#endif