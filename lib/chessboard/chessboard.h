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
#include <iterator>

typedef std::pair<int, int> coords;

class chessboard {

    private:
        piece *board[8][8];
        std::vector<std::pair<coords, coords>> moves;
        std::vector<coords> white;
        std::vector<coords> black;

        void edit_white_pos(const coords &_start, const coords &_end);
        void edit_black_pos(const coords &_start, const coords &_end);
        void eat_piece(const set &_side, const coords &_eaten);

        /**/bool is_out(const coords &_pos) const;
        /**/bool opposites(const coords &_c1, const coords &_c2) const;
        
        /**/bool try_add_move(std::vector<coords> &_moves, const coords _pos, const std::pair<int, int> _offset) const;

        /**/piece* piece_at_pos(const coords &_pos) const;
        /**/piece* piece_at_pos(const int i, const int j) const;

        /**/bool is_promotion(const coords &_pos) const;
        /**/void promote(const coords &_pos, const char piece);

        /**/bool is_pawn_eat(const path &_p, const coords &_start, const coords &_end) const;
        
        /**/std::pair<bool, coords> is_enpassant(const path &_p, const coords &_start, const coords &_end) const;
        /**/void do_enpassant(const coords &_eat, const coords &_start, const coords &_end);
        
        /**/std::pair<bool, coords> is_castling(const path &_p, const coords &_start, const coords &_end) const;
        /**/void do_castling(const coords &_tower, const coords &_start, const coords &_end);

        /**/void do_legit(const coords &_start, const coords &_end);

        bool check(const set &_side) const;
        bool checkmate(const set &_side);
        bool draw() const;
        
        /**/void undo(const int _special, const coords &_oth_piece, const coords &_start, const coords &_end, const piece* _eaten);

    public:
        /**/chessboard(void);
        /**/~chessboard();
        
        /**/std::vector<coords> get_moves(const coords &_pos) const;
        std::vector<coords> get_pieces(const set &_set) const;

        coords find(const char _piece) const;

        /**
         * @brief Method to move a peice from _start to _end
         * 
         * @param _start Initial position of the piece to move
         * @param _end Final position of the piece to move
         * @return std::pair<bool, bool> Pair of conditions: ([finished][made the move/won])
         *                  (false, true) if the move was successfull,
         *                  (false, false) if the move was unsuccessfull due to check,
         *                  (true, false) if it's a draw
         *                  (true, true) if it's a checkmate (current player winning)
         *                  
         */
        /**/std::pair<bool, bool> move(const set &_turn, const coords &_start, const coords &_end);

        bool checkmate_control(const coords &_start, const coords &_end);
        
        /**/void print() const;
};

template<typename Type>
bool is(const piece &data) {
	if( &data == NULL ) return false;
    
    if (typeid(Type) == typeid(tower)) return tolower(data.get_alias()) == 't';
    if (typeid(Type) == typeid(horse)) return tolower(data.get_alias()) == 'c';
    if (typeid(Type) == typeid(bishop)) return tolower(data.get_alias()) == 'a';
    if (typeid(Type) == typeid(king)) return tolower(data.get_alias()) == 'r';
    if (typeid(Type) == typeid(queen)) return tolower(data.get_alias()) == 'd';
    if (typeid(Type) == typeid(pawn)) return tolower(data.get_alias()) == 'p';
    if (typeid(Type) == typeid(empty_tile)) return data.get_alias() == ' ';

    return false;
}

coords operator+(const coords &_a, const coords &_b) {

    return std::make_pair(_a.first + _b.first, _a.second + _b.second);

}

#endif