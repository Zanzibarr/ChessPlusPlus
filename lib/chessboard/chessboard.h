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
        
        /**
         * @brief Insert in _moves a pair of coordinates if the tile isn't occupied
         * 
         * @param _moves The vector to fill
         * @param _pos The intial position
         * @param _offset The distance traveled from the initial position
         * @return true If it's possible to keep expanding through this direction
         * @return false If there is an obstacle in this position
         */
        bool insert_if_legit(std::vector<coords> &_moves, const coords _pos, const std::pair<int, int> _offset) const;

        /**
         * @brief Returns a reference to the piece in _pos position
         * 
         * @param _pos or (i, j) The position of the object
         * @return piece& The reference to the piece found
         */
        piece* piece_at_pos(const coords &_pos) const;
        piece* piece_at_pos(const int i, const int j) const;

        /**
         * @brief Checks if a pawn is in promotion position
         * 
         * @param _pos The position in which to search
         * @return true If the piece in _pos is a pawn that needs to be promoted
         * @return false If the piece in _pos is not a pawn or the position is not a promotion position
         */
        bool is_promotion(const coords &_pos) const;
        
        /**
         * @brief Method to promote a pawn to a choosen piece
         * 
         * @param _pos The position of the pawn to promote
         * @param _piece The alias of the piece to promote
         */
        void promote(const coords &_pos, const char piece);

        /**
         * @brief Checks if the move is a pawn eating move
         * 
         * @param _path The path of the move
         * @param _start The initiali position of the piece to move
         * @param _end The final position of the piece to move
         * @return true If it's a pawn eating move
         * @return false If it's not a pawn eating move of if it's an illegal move for the pawn
         */
        bool is_pawn_eat(const path &_p, const coords &_start, const coords &_end) const;
        
        /**
         * @brief Checks if the move is an enpassant
         * 
         * @param _path The path of the move
         * @param _start The initial position of the piece to move
         * @param _end The final position of the piece to move
         * @return std::pair<bool, coords> A pair containing true/false based on if it's or not an enpassant and a pair of coordinates of the pawn that has been eaten
         */
        std::pair<bool, coords> is_enpassant(const path &_p, const coords &_start, const coords &_end) const;
        
        /**
         * @brief Method to attempt an enpassant
         * 
         * @param _eat The pawn to eat
         * @param _start The initial position of the piece to move
         * @param _end The final position of the piece to move
         */
        void do_enpassant(const coords &_eat, const coords &_start, const coords &_end);
        
        /**
         * @brief Checks if the move is a castling
         * 
         * @param _path The path of the move
         * @param _start The initial position of the piece to move
         * @param _end The final position of the piece to move
         * @return std::pair<bool, coords> A pair containing true/false based on if it's or not a castling and a pair of coordinates of the tower to move
         */
        std::pair<bool, coords> is_castling(const path &_p, const coords &_start, const coords &_end) const;

        /**
         * @brief Method to attempt a castling
         * 
         * @param _tower The coordinates of the tower to move
         * @param _start The initial position of the piece to move
         * @param _end The final position of the piece to move
         */
        void do_castling(const coords &_tower, const coords &_start, const coords &_end);

        bool check(const set &_side) const;
        bool checkmate(const set &_side) const;
        bool draw() const;
        
        void undo(const int _special, const coords &_oth_piece, const coords &_start, const coords &_end, const piece* _eaten, const bool _first_move);

    public:
        chessboard(void);
        ~chessboard();
        
        /**
         * @brief Method that returns all the legal move a piece can do based on his legal paths
         * 
         * @param _pos 
         * @return std::vector<coords> 
         */
        std::vector<coords> get_moves(const coords &_pos) const;

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
        std::pair<bool, bool> move(const coords &_start, const coords &_end);
        
        /**
         * @brief Method to print the chessboard
         * 
         */
        void print() const;
};

template<typename Type>
bool is_type(const piece &data) {
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

#endif