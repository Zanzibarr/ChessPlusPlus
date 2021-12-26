#include "piece.h"

set opposite_of(const set _set){
	
	switch (_set) {
		case set::Black: return set::White;
		case set::White: return set::Black;
	}

	throw invalid_set_exception();
}

piece::piece(set _side) {
	side = _side;
	alias = 'X';
}

bool piece::is_legit_move(path _path, int distance) const {
	
	for(int i = 0; i < valid_path.size(); i++) {
		if(valid_path[i] == _path) return true;
	}

	return false;
}

char piece::get_alias() const { 
	
	switch (side) {
		case set::White : return tolower(alias);
		case set::Black : return toupper(alias); 	
	} 

	throw invalid_set_exception();
}
set piece::get_side() const { return side; }
bool piece::is_first_move() const { return first_move; }
void piece::moved() { first_move = false; }