#ifndef PATH_H
#define PATH_H

#include <utility>
#include <stdlib.h>
using namespace std;

/**
 * @file path.h
 * @author Modolo Riccardo (riccardo.modolo.1@studenti.unipd.it)
 * @brief Interface of the path
 * @version 0.1
 * @date 2021-12-24
 *  
 */

enum class path {Horizontal, Vertical, Diagonal, L};
class illegal_path_exception {};

path get_path(const pair<int, int> &_current_position, const pair<int,int> &_destination);
int get_distance(const pair<int, int> &_current_position, const pair<int,int> &_destination);

//Path check condition
bool is_Horizontal(const pair<int, int> &_current_position, const pair<int,int> &_destination);
bool is_Vertical(const pair<int, int> &_current_position, const pair<int,int> &_destination);
bool is_Diagonal(const pair<int, int> &_current_position, const pair<int,int> &_destination);
bool is_L(const pair<int, int> &_current_position, const pair<int,int> &_destination);

#endif