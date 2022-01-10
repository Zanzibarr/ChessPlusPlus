#ifndef CHESSBOARD_H
#define CHESSBOARD_H

/**
 * 
 * @file chessboard.h
 * @author Zanella Matteo (matteo.zanella.3@studenti.unipd.it)
 * @brief The interface of the chessboard
 * @version 0.1
 * @date 2021-12-26
 *  
 */

#include "../piece/pieces/queen.cpp"
#include "../piece/pieces/king.cpp"
#include "../piece/pieces/bishop.cpp"
#include "../piece/pieces/knight.cpp"
#include "../piece/pieces/rook.cpp"
#include "../piece/pieces/pawn.cpp"
#include "../piece/pieces/empty_tile.cpp"
#include <vector>
#include <iostream>

typedef std::pair<int, int> coords;

class illegal_type_exception{};

class chessboard;

class chessboard {
    
    public:

        /**
         * @brief Construct a new chessboard object
         * 
         */
        chessboard(void);

        /**
         * @brief Destroy the chessboard object
         * 
         */
        ~chessboard();
        
        chessboard(const std::vector<piece*> &_copy, const std::vector<std::pair<coords, coords>> &_history);
        
        /**
         * @brief Get the current location of every piece from _set side
         * 
         * @param _set The side of the pieces wanted
         * @return std::vector<coords> The coords of the _set side pieces
         * 
         */
        std::vector<coords> get_pieces(const set &_set) const;

        /**
         * @brief Get all the possible moves that a piece in _pos position can make (special moves included)
         * 
         * @param _pos The position of the object
         * @return std::vector<coords>& A vector containing all the coords the piece can reach from _pos
         * 
         */
        std::vector<coords> get_moves(const coords &_pos) const;

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
        std::pair<bool, bool> move(const set &_turn, const coords &_start, const coords &_end);
        
        /**
         * @brief Method that prints the chessboard in it's current state
         * 
         */
        void print() const;

    private:
    
        piece *board[8][8];
        std::vector<std::pair<coords, coords>> history;
        std::vector<coords> white_pieces;
        std::vector<coords> black_pieces;

        const coords ILLEGAL_COORDS {-1, -1};

        std::vector<piece*> to_vector() const;

        bool opposites(const coords &_pos_1, const coords &_pos_2) const;

        piece* piece_at_pos(const coords &_pos) const;
        piece* piece_at_pos(const int i, const int j) const;

        coords find(const set &_side, const piece* _piece) const;
        coords find(const set &_side, const char _piece_alias) const;

        void edit_pos(const set &_side, const coords &_start, const coords &_end);
        void eat_piece(const set &_side, const coords &_piece);
        void add_piece(const set &_side, const coords &_piece);

        bool try_add_move(std::vector<coords> &_moves, const coords &_pos, const coords &_offset) const;

        bool is_legit(const coords &_start, const coords &_end) const;
        bool is_pawn_eat(const coords &_start, const coords &_end) const;
        std::pair<bool, coords> is_castling(const coords &_start, const coords &_end) const;
        std::pair<bool, coords> is_enpassant(const coords &_start, const coords &_end) const;
        bool is_promotion(const coords &_pos) const;
        
        void do_legit(const coords &_start, const coords &_end);
        void do_castling(const coords &_tower, const coords &_start, const coords &_end);
        void do_enpassant(const coords &_eat, const coords &_start, const coords &_end);
        void do_promotion(const coords &_pos);

        bool is_in_danger(const set &_side, const coords &_to_check) const;
        bool check(const set &_side) const;
        bool checkmate(const set &_side) const;
        bool draw(const set &_side) const;
        bool draw_for_pieces() const;
        
};

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