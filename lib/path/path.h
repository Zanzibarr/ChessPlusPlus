#ifndef PATH_H
#define PATH_H
#include <utility>
#include <stdlib.h>
using namespace std;

/*
 * path.h is a library from operation between 2 point in a chessboard
 * the goal of this library is separate piece from board.
 * @author Riccardo Modolo 2009667
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