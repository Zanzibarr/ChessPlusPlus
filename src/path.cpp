#include "../include/path.h"

/**
 * 
 * @file path.cpp
 * @author Riccardo Modolo (riccardo.modolo.1@studenti.unipd.it)
 * 
 * @brief implementation of path.h
 * 
 * @version 0.4
 * @date 2022-01-15
 * 
 */

bool is_Horizontal(const coords &start, const coords &end) {
	int row_distance = end.first - start.first;
	int col_distance = end.second - start.second;

	return (row_distance == 0 && col_distance != 0);
}

bool is_Vertical(const coords &start, const coords &end) {
	int row_distance = end.first - start.first;
	int col_distance = end.second - start.second;

	return (col_distance == 0 && row_distance != 0);
}

bool is_Diagonal(const coords &start, const coords &end) {
	int row_distance = end.first - start.first;
	int col_distance = end.second - start.second;

	return ((row_distance != 0 && col_distance != 0 ) && std::abs(row_distance) == std::abs(col_distance));
}

bool is_L(const coords &start, const coords &end) {
	int row_distance = end.first - start.first;
	int col_distance = end.second - start.second;

	return (std::abs(col_distance) == 1 && (std::abs(row_distance) == 2) || (std::abs(col_distance) == 2 && std::abs(row_distance) == 1));
}

path get_path(const coords &start, const coords &end) {

	if(is_Horizontal(start, end)) return path::Horizontal;
	if(is_Vertical(start, end)) return path::Vertical;
	if(is_Diagonal(start, end)) return path::Diagonal;
	if(is_L(start, end)) return path::L;

	throw illegal_move_exception();
}

int get_distance(const coords &start, const coords &end) {
	if(is_Horizontal(start, end)) return end.second - start.second;
	if(is_Vertical(start, end)) return end.first - start.first;
	if(is_Diagonal(start, end)) return end.first - start.first; //for diagonal movement one of coordinate is acceptable
	if(is_L(start, end)) return 3;

	throw illegal_move_exception();
}