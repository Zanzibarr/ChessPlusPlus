#ifndef PATH_H
#define PATH_H

#include <utility>
#include "board.h"

struct path {

    static const char DIAGONAL = 'D';
    static const char STRAIGHT = 'S';
    static const char HORSE_MOVE = 'L';
    int path_length;
    char direction;
    path(const board &_board, const std::pair<char, int> &_start, const std::pair<char, int> &_end);

};

bool operator==(const path &_p, const char _d) {
    return _d == _p.direction;
}

#endif