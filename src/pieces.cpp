#include "../include/pieces.h"

empty_tile::empty_tile() : piece(set::Empty) {
	alias = ' ';
	max_distance = 0;
}

bishop::bishop(set side) : piece(side) {
	alias = 'A';
	max_distance = 8;
	valid_path.push_back(path::Diagonal);
}

queen::queen(set side) : piece(side) {
	alias = 'Q';
	max_distance = 8;
	valid_path.push_back(path::Horizontal);
	valid_path.push_back(path::Vertical);
	valid_path.push_back(path::Diagonal);
}

king::king(set side) : piece(side) {
	alias = 'R';
	max_distance = 1;
	valid_path.push_back(path::Horizontal);
	valid_path.push_back(path::Vertical);
	valid_path.push_back(path::Diagonal);
}

rook::rook(set side) : piece(side) {
	alias = 'T';
	max_distance = 8;
	valid_path.push_back(path::Horizontal);
	valid_path.push_back(path::Vertical);
}

knight::knight(set side) : piece(side) {
	alias = 'C';
	max_distance = 3;
	valid_path.push_back(path::L);
}

bool knight::is_legit_move(path _path, int distance) const {
	for(int i = 0; i < valid_path.size(); i++) {
		if(valid_path[i] == _path && std::abs(distance) == 3) return true;
	}

	return false;
}

pawn::pawn(set side) : piece(side) {
	alias = 'P';
	max_distance = 1;
	valid_path.push_back(path::Vertical);
}

bool pawn::is_legit_move(path _path, int distance) const {
	int side_multiplier = 0;

	if(side == set::Black) side_multiplier = -1;
	else if(side == set::White) side_multiplier = 1;

	bool normal_condition = (valid_path[0] == _path && distance == (side_multiplier));
	bool first_condition = (valid_path[0] == _path && distance == (2*side_multiplier) && first_move);

	return normal_condition || first_condition;
}