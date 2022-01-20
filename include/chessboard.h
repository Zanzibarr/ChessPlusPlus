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

#include "pieces.h"
#include <vector>
#include <iostream>
#define LETTER 'A'

typedef std::pair<int, int> coords;

class illegal_type_exception{};

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
        
        /**
         * @brief Get the current location of every piece from _set side
         * 
         * @param _set The side of the pieces wanted
         * @return std::vector<coords> The coords of the _set side pieces
         * 
         */
        std::vector<coords> get_pieces(const set &_set) const;

        /**
         * @brief Get the alias of the piece at (i, j) position
         * 
         * @param _i Row index of the piece
         * @param _j Col index of the piece
         * @return char The alias of the piece in the specified position
         * 
         */
        char at(const int _i, const int _j) const;

        /**
         * @brief Get all the possible moves that a piece in _pos position can make (special moves included)
         * 
         * @param _pos The position of the object
         * @return std::vector<coords>& A vector containing all the coords the piece can reach from _pos
         * 
         */
        std::vector<coords> get_moves(const coords &_pos, const bool _with_castling = false) const;

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
         * @brief Checks if the piece in _pos position is in a promotion condition
         * 
         * @param _pos Position of the piece to check
         * @return true If it's in a promotion condition
         * @return false If it's not in a promotion condition
         * 
         */
        bool is_promotion(const coords &_pos) const;

        /**
         * @brief Method that does the promotion of the piece at _pos position into the _piece selected
         * 
         * @param _pos The position of the pawn to promote
         * @param _piece The choosen promotion
         * 
         */
        void do_promotion(const coords &_pos, const char &_piece);

        std::vector<std::pair<coords, coords>> get_history() const;
        

    private:

        class illegal_coords_exception{};
    
        piece *board[8][8];
        std::vector<std::pair<coords, coords>> history;
        std::vector<coords> white_pieces;
        std::vector<coords> black_pieces;

        piece* empty_piece;
        piece* eaten_piece;

        const std::pair<bool, bool> FAILED {false, false};
        const std::pair<bool, bool> SUCCESS {false, true};
        const std::pair<bool, bool> DRAW {true, false};
        const std::pair<bool, bool> CHECKMATE {true, true};
        const coords ILLEGAL_COORDS {-1, -1};
        
        bool is_out(const coords &_pos) const;
        bool opposites(const coords &_pos_1, const coords &_pos_2) const;

        piece* piece_at_pos(const coords &_pos) const;
        piece* piece_at_pos(const int i, const int j) const;

        bool contains(const set &_side, const char _piece_alias) const;
        std::vector<coords> find(const set &_side, const char _piece_alias) const;

        void edit_pos(const set _side, const coords _start, const coords _end);
        void eat_piece(const set &_side, const coords &_piece);
        void add_piece(const set &_side, const coords &_piece);

        bool try_add_move(std::vector<coords> &_moves, const coords &_pos, const coords &_offset) const;

        bool is_legit(const coords &_start, const coords &_end) const;
        bool is_pawn_eat(const coords &_start, const coords &_end) const;
        std::pair<bool, coords> is_castling(const coords &_start, const coords &_end) const;
        std::pair<bool, coords> is_enpassant(const coords &_start, const coords &_end) const;
        
        void do_legit(const coords &_start, const coords &_end);
        void do_castling(const coords &_tower, const coords &_start, const coords &_end);
        void do_enpassant(const coords &_eat, const coords &_start, const coords &_end);

        bool is_in_danger(const set &_side, const coords &_to_check) const;
        bool check(const set &_side) const;
        bool checkmate(const set &_side);
        bool draw(const set &_side);
        bool draw_for_pieces() const;

        void undo(const int _move_type, const coords _initial_pos, const coords _final_pos, const coords _oth_pos, const set _side);
        
};

template<typename Type>
bool is(const piece data);
coords operator+(const coords &_a, const coords &_b);
bool operator==(const coords &_a, const coords &_b);
std::ostream& operator<<(std::ostream& _os, const chessboard &_board);

#endif