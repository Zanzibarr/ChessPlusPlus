#include "../include/piece.h"

set opposite_of(const set side) {
	switch (side) {
	case set::Black : return set::White;
	case set::White : return set::Black;
	case set::Empty : return set::Empty;
	}
	throw illegal_move_exception();
}

piece::piece(set _set) {
	first_move = true;
	side = _set;
}

bool piece::is_legit_move(path _path, int distance) const {
	for(int i = 0; i < valid_path.size(); i++) {
		if(valid_path[i] == _path && std::abs(distance) <= max_distance) return true;
	}
	return false;
}

char piece::get_alias() const { 
	switch (side) {
		case set::White : return tolower(alias);
		case set::Black : return toupper(alias);
		case set::Empty : return ' ';	
	}
	throw illegal_move_exception();
}

set piece::get_side() const { return side; }
int piece::get_max_distance() const { return max_distance; }
bool piece::is_first_move() const { return first_move;  }
void piece::moved() { first_move = false; }