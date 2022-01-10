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

#include "../include.h"

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
        
        chessboard(const std::vector<piece*> &_copy, const std::vector<std::pair<coords, coords>> &_history);

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

#endif