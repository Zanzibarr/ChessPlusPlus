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

#include "../piece/pieces/queen.cpp"
#include "../piece/pieces/king.cpp"
#include "../piece/pieces/bishop.cpp"
#include "../piece/pieces/horse.cpp"
#include "../piece/pieces/tower.cpp"
#include "../piece/pieces/pawn.cpp"
#include "../piece/pieces/empty_tile.cpp"
#include <iostream>
#include <vector>

typedef std::pair<int, int> coords;

class chessboard {

    private:
        piece *board[8][8];
        std::pair<coords, coords> last_move;
        
        bool insert_if_legit(std::vector<coords> &_moves, const coords _pos, const std::pair<int, int> _offset) const;

        piece &piece_at_pos(const coords &_pos) const;
        piece &piece_at_pos(const int i, const int j) const;

        bool is_promotion(const coords &_pos) const;
        void promote(const coords &_pos, const char piece);

        bool is_pawn_eat(const path &_p, const coords &_start, const coords &_end) const;
        std::pair<bool, coords> is_enpassant(const path &_p, const coords &_start, const coords &_end) const;
        std::pair<bool, coords> is_castling(const path &_p, const coords &_start, const coords &_end) const;

        void enpassant(const coords &_eat, const coords &_start, const coords &_end);
        void castling(const coords &_tower, const coords &_start, const coords &_end);

        bool check(const set &_side) const;
        bool checkmate(const set &_side) const;

    public:
        chessboard(void);
        ~chessboard();

        std::vector<coords> get_moves(const coords &_pos) const;

        coords find(const char _piece) const;
        bool check_path(const path _path, unsigned int const _dist) const;
        bool move(const coords &_start, const coords &_end);
        void print() const;
        void pawn_eat(const coords &_start, const coords &_end);
};

template< typename Type, typename DataType >
bool is( const DataType& data ) {
	if( &data == NULL ) return false;
    return typeid( data ) == typeid( Type );
}

#endif