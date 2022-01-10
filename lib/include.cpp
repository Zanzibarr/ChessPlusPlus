#ifndef INCLUDE_CPP
#define INCLUDE_CPP

/**
 * 
 * @file include.h
 * 
 * @authors Bertan Kabir     2008287     (kabir.bertan@studenti.unipd.it)
 *          Modolo Riccardo  2009667     (riccardo.modolo1@studenti.unipd.it)
 *          Zanella Matteo   2000139     (matteo.zanella.3@studenti.unipd.it)
 * 
 * @brief Raccolta di metodi eccezioni e classi utili a tutti i file
 * @version 0.1
 * @date 2021-12-26
 *  
 */


#include "piece/pieces/queen.cpp"
#include "piece/pieces/king.cpp"
#include "piece/pieces/bishop.cpp"
#include "piece/pieces/knight.cpp"
#include "piece/pieces/rook.cpp"
#include "piece/pieces/pawn.cpp"
#include "piece/pieces/empty_tile.cpp"

#include <utility>
#include <vector>
#include <stdlib.h>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <regex>


typedef std::pair<int, int> coords;

const coords ILLEGAL_COORDS {-1, -1};
const char LETTERA {'A'};

class illegal_move_exception{};
class illegal_set_exception{};
class illegal_type_exception{};
class illegal_path_exception{};

enum class set {Black, White, Empty};
enum class path {Horizontal, Vertical, Diagonal, L};


bool is_out(const coords &_pos) { return _pos.first < 0 || _pos.first >= 8 || _pos.second < 0 || _pos.second >= 8; }

set opposite_of(const set _set){
	
	switch (_set) {
		case set::Black: return set::White;
		case set::White: return set::Black;
		case set::Empty: return set::Empty;
	}

	throw illegal_set_exception();

}


bool is_Horizontal(const coords &_current_position, const coords &_destination) {

    int row_distance = _destination.first - _current_position.first;
    int col_distance = _destination.second - _current_position.second;

    return (row_distance == 0 && col_distance != 0);

}

bool is_Vertical(const coords &_current_position, const coords &_destination) {

    int row_distance = _destination.first - _current_position.first;
    int col_distance = _destination.second - _current_position.second;

    return (col_distance == 0 && row_distance != 0);

}

bool is_Diagonal(const coords &_current_position, const coords &_destination) {

    int row_distance = _destination.first - _current_position.first;
    int col_distance = _destination.second - _current_position.second;

    return ((row_distance != 0 && col_distance != 0 ) && std::abs(row_distance) == std::abs(col_distance));
}

bool is_L(const coords &_current_position, const coords &_destination) {

    int row_distance = _destination.first - _current_position.first;
    int col_distance = _destination.second - _current_position.second;

    return (std::abs(col_distance) == 1 && (std::abs(row_distance) == 2) || (std::abs(col_distance) == 2 && std::abs(row_distance) == 1));

}

path get_path(const coords &_current_position, const coords &_destination) {

    if(is_Horizontal(_current_position, _destination)) return path::Horizontal;
    else if(is_Vertical(_current_position, _destination)) return path::Vertical;
    else if(is_Diagonal(_current_position, _destination)) return path::Diagonal;
    else if(is_L(_current_position, _destination)) return path::L;

    throw illegal_move_exception();

}

int get_distance(const coords &_current_position, const coords &_destination) {

    if(is_Horizontal(_current_position, _destination)) return _destination.second - _current_position.second;
    else if(is_Vertical(_current_position, _destination)) return _destination.first - _current_position.first;
    else if(is_Diagonal(_current_position, _destination)) return _destination.first - _current_position.first;
    else if(is_L(_current_position, _destination)) return 3;

    throw illegal_move_exception();

}


template<typename Type>
bool is(const piece &data) {

    if( &data == NULL ) return false;
    
    if (typeid(Type) == typeid(rook)) return std::tolower(data.get_alias()) == 't';
    else if (typeid(Type) == typeid(knight)) return std::tolower(data.get_alias()) == 'c';
    else if (typeid(Type) == typeid(bishop)) return std::tolower(data.get_alias()) == 'a';
    else if (typeid(Type) == typeid(king)) return std::tolower(data.get_alias()) == 'r';
    else if (typeid(Type) == typeid(queen)) return std::tolower(data.get_alias()) == 'd';
    else if (typeid(Type) == typeid(pawn)) return std::tolower(data.get_alias()) == 'p';
    else if (typeid(Type) == typeid(empty_tile)) return data.get_alias() == ' ';

    throw illegal_type_exception();

}


coords operator+(const coords &_a, const coords &_b) { return std::make_pair(_a.first + _b.first, _a.second + _b.second); }


#endif