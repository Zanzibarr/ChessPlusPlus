#include "path.h"

/*
 * implementation of path.h
 * @author Riccardo Modolo 2009667
 */

bool is_Horizontal(const pair<int, int> &_current_position, const pair<int,int> &_destination) {

	int x_distance = _destination.first - _current_position.first;
	int y_distance = _destination.second - _current_position.second;

	return (y_distance == 0 && x_distance != 0);

}

bool is_Vertical(const pair<int, int> &_current_position, const pair<int,int> &_destination) {

	int x_distance = _destination.first - _current_position.first;
	int y_distance = _destination.second - _current_position.second;

	return (x_distance == 0 && y_distance != 0);

}

bool is_Diagonal(const pair<int, int> &_current_position, const pair<int,int> &_destination) {

	int x_distance = _destination.first - _current_position.first;
	int y_distance = _destination.second - _current_position.second;

	return ((x_distance != 0  && y_distance != 0 ) && x_distance == y_distance);
}

bool is_L(const pair<int, int> &_current_position, const pair<int,int> &_destination) {

	int x_distance = _destination.first - _current_position.first;
	int y_distance = _destination.second - _current_position.second;

	return ((x_distance == abs(1) && y_distance == abs(2)) || (x_distance == abs(2) && y_distance == abs(1)));

}


path get_path(const pair<int, int> &_current_position, const pair<int,int> &_destination) {

	if(is_Horizontal(_current_position, _destination)) return path::Horizontal;
	if(is_Vertical(_current_position, _destination)) return path::Vertical;
	if(is_Diagonal(_current_position, _destination)) return path::Diagonal;
	if(is_L(_current_position, _destination)) return path::L;

	throw illegal_path_exception();
}

int get_distance(const path _path, const pair<int, int> &_current_position, const pair<int,int> &_destination) {

	if(_path == path::Horizontal) return _destination.first - _current_position.first;
	if(_path == path::Vertical) return _destination.second - _current_position.second;
	if(_path == path::Diagonal) return _destination.first - _current_position.first; //for diagonal movement one of coordinate is acceptable
	if(_path == path::L) return 3;

	throw illegal_path_exception();
}