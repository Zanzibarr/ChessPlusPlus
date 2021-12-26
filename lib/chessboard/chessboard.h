/**
 * @file chessboard.h
 * @author Zanella Matteo (matteo.zanella.3@studenti.unipd.it)
 * @brief The interface of the chessboard
 * @version 0.1
 * @date 2021-12-26
 *  
 */

#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include "../piece/piece.h"
#include "../piece/pieces/queen.cpp"
#include "../piece/pieces/king.cpp"
#include "../piece/pieces/bishop.cpp"
#include "../piece/pieces/horse.cpp"
#include "../piece/pieces/tower.cpp"
#include "../piece/pieces/pawn.cpp"
#include "../path/path.h"
#include <vector>

class chessboard {

    private:
        piece *board[8][8];

        std::vector<std::pair<unsigned int , unsigned int>> get_moves(const std::pair<unsigned int, unsigned int> &_pos) const;

        bool is_promotion(const std::pair<unsigned int, unsigned int> &_pos) const;
        void promote(const std::pair<unsigned int, unsigned int> &_pos, const char piece);

        bool pawn_eat(const path &_p, const std::pair<unsigned int, unsigned int> &_start, const std::pair<unsigned int, unsigned int> &_end) const;
        bool enpassant(const std::pair<unsigned int, unsigned int> &_start, const std::pair<unsigned int, unsigned int> &_end) const;
        bool castling((const path &_p, const std::pair<unsigned int, unsigned int> &_start, const std::pair<unsigned int, unsigned int> &_end) const;

        bool check(const set &_side) const;
        bool checkmate(const set &_side) const;

    public:
        chessboard(void);
        ~chessboard(void);

        piece get(const std::pair<unsigned int, unsigned int> &_pos) const;
        std::pair<int, int> find(const char _piece) const;
        bool check_path(const path _path, unsigned int const _dist) const;
        bool move(const std::pair<unsigned int, unsigned int> &_start, const std::pair<unsigned int, unsigned int> &_end);
        void print() const;

};

template< typename Type, typename DataType >
bool is( const DataType& data ) {
	if( &data == NULL ) return false;
    return typeid( data ) == typeid( Type );
}

#endif