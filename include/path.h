#ifndef PATH_H
#define PATH_H

#include <utility>
#include <stdlib.h>

/**
 * 
 * @file path.h
 * @author Riccardo Modolo (riccardo.modolo.1@studenti.unipd.it)
 * 
 * @brief The interface consists of a set of functions used to 
 * 		  find pre-existing paths in the game of chess from coordinates 
 * 
 * @version 0.4
 * @date 2022-01-15
 * 
 */

typedef std::pair<int, int> coords;
enum class path { Horizontal, Vertical, Diagonal, L };
class illegal_move_exception {};

//get the path from start coord to end coord
path get_path(const coords &start, const coords &end);

//get the distance from start coord and end coord only if is valid path
int get_distance(const coords &start, const coords &end);

//check if the path is an Horizontal path from start coord to end coord
bool is_Horizontal(const coords &start, const coords &end);

//check if the path is a Vertical path from start coord to end coord
bool is_Vertical(const coords &start, const coords &end);

//check if the path is a Diagonal path from start coord to end coord
bool is_Diagonal(const coords &start, const coords &end);

//check if the path is an L path from start coord to end coord
bool is_L(const coords &start, const coords &end);

#endif //PATH_H