#include "path.h"

/**
 * @file path.cpp
 * @author Modolo Riccardo (riccardo.modolo.1@studenti.unipd.it)
 * @brief Implementation of the path
 * @version 0.1
 * @date 2021-12-24
 *  
 */

bool is_Horizontal(const pair<int, int> &_current_position, const pair<int,int> &_destination) {

	int row_distance = _destination.first - _current_position.first;
	int col_distance = _destination.second - _current_position.second;

	return (row_distance == 0 && col_distance != 0);

}

bool is_Vertical(const pair<int, int> &_current_position, const pair<int,int> &_destination) {

	int row_distance = _destination.first - _current_position.first;
	int col_distance = _destination.second - _current_position.second;

	return (col_distance == 0 && row_distance != 0);

}

bool is_Diagonal(const pair<int, int> &_current_position, const pair<int,int> &_destination) {

	int row_distance = _destination.first - _current_position.first;
	int col_distance = _destination.second - _current_position.second;

	return ((row_distance != 0 && col_distance != 0 ) && std::abs(row_distance) == std::abs(col_distance));
}

bool is_L(const pair<int, int> &_current_position, const pair<int,int> &_destination) {

	int row_distance = _destination.first - _current_position.first;
	int col_distance = _destination.second - _current_position.second;

	return (std::abs(col_distance) == 1 && (std::abs(row_distance) == 2) || (std::abs(col_distance) == 2 && std::abs(row_distance) == 1));

}

path get_path(const pair<int, int> &_current_position, const pair<int,int> &_destination) {

	if(is_Horizontal(_current_position, _destination)) return path::Horizontal;
	if(is_Vertical(_current_position, _destination)) return path::Vertical;
	if(is_Diagonal(_current_position, _destination)) return path::Diagonal;
	if(is_L(_current_position, _destination)) return path::L;

	throw illegal_path_exception();
}

int get_distance(const pair<int, int> &_current_position, const pair<int,int> &_destination) {

	if(is_Horizontal(_current_position, _destination)) return _destination.second - _current_position.second;
	if(is_Vertical(_current_position, _destination)) return _destination.first - _current_position.first;
	if(is_Diagonal(_current_position, _destination)) return _destination.first - _current_position.first; //for diagonal movement one of coordinate is acceptable
	if(is_L(_current_position, _destination)) return 3;

	throw illegal_path_exception();
}