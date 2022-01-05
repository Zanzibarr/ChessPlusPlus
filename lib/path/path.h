#ifndef PATH_H
#define PATH_H

#include <utility>
#include <stdlib.h>

/**
 * @file path.h
 * @author Modolo Riccardo (riccardo.modolo.1@studenti.unipd.it)
 * @brief Interface of the path
 * @version 0.1
 * @date 2021-12-24
 *  
 */

typedef std::pair<int, int> coords;

enum class path {Horizontal, Vertical, Diagonal, L};
class illegal_move_exception {};

path get_path(const coords &_current_position, const coords &_destination);
int get_distance(const coords &_current_position, const coords &_destination);

//Path check condition
bool is_Horizontal(const coords &_current_position, const coords &_destination);
bool is_Vertical(const coords &_current_position, const coords &_destination);
bool is_Diagonal(const coords &_current_position, const coords &_destination);
bool is_L(const coords &_current_position, const coords &_destination);

#endif