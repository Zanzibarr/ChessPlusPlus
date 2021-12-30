/**
 * @file chessboard.h
 * @author Zanella Matteo (matteo.zanella.3@studenti.unipd.it)
 * @brief Implementation of the chessboard
 * @version 0.1
 * @date 2021-12-26
 *  
 */

#include "chessboard.h"

chessboard::chessboard(void) {

    board[7][0] = new tower(set::Black);
    board[7][1] = new horse(set::Black);
    board[7][2] = new bishop(set::Black);
    board[7][3] = new king(set::Black);
    board[7][4] = new queen(set::Black);
    board[7][5] = new bishop(set::Black);
    board[7][6] = new horse(set::Black);
    board[7][7] = new tower(set::Black);

    for (unsigned int i = 0; i < 8; i++) {
        board[6][i] = new pawn(set::Black);
        board[1][i] = new pawn(set::White);
    }

    board[0][0] = new tower(set::White);
    board[0][1] = new horse(set::White);
    board[0][2] = new bishop(set::White);
    board[0][3] = new king(set::White);
    board[0][4] = new queen(set::White);
    board[0][5] = new bishop(set::White);
    board[0][6] = new horse(set::White);
    board[0][7] = new tower(set::White);

    for (unsigned int i = 2; i < 6; i++) for (unsigned int j = 0; j < 8; j++) {
        board[i][j] = new empty_tile();
    }

}

chessboard::~chessboard(void) {

    for (unsigned int i = 0; i < 8; i++) for (unsigned int j = 0; j < 8; j++) {
        delete board[i][j];
    }

}

void chessboard::insert_if_legit(std::vector<coords> &_moves, const coords _pos, std::pair<int, int> _offset, bool &_check) const {

    coords pos_check{_pos.first + _offset.first, _pos.second + _offset.second};

    if (is<empty_tile>(piece_at_pos(pos_check)))
        _moves.push_back(pos_check);
    else
        _check = false;

    if (piece_at_pos(pos_check).get_side() == opposite_of(piece_at_pos(_pos).get_side()))
        _moves.push_back(pos_check);

}

    /**
 * @brief Method that returns all the legal move a piece can do based on his legal paths
 * 
 * @param _pos 
 * @return std::vector<coords> 
 */
std::vector<coords> chessboard::get_moves(const coords &_pos) const {

    piece piece1 = piece_at_pos(_pos);
    
    std::vector<coords> ret;
    int distance = 0;

    bool h_l = true;
    bool h_r = true;
    bool d_1 = true;
    bool d_2 = true;
    bool d_3 = true;
    bool d_4 = true;
    bool v_u = true;
    bool v_d = true;
    bool h = true;

    int counter = 1;

    while (counter <= piece1.max_distance() && (h_l || h_r || d_1 || d_2 || d_3 || d_4 || v_u || v_d)) {

        if (h_l) h_l = _pos.second - counter >= 0;
        if (h_r) h_r = _pos.second + counter < 8;
        if (d_1) d_1 = _pos.first + counter < 8 && _pos.second - counter >= 0;
        if (d_2) d_2 = _pos.first + counter < 8 && _pos.second + counter < 8;
        if (d_3) d_3 = _pos.first - counter >= 0 && _pos.second + counter < 8;
        if (d_4) d_4 = _pos.first - counter >= 0 && _pos.second - counter >= 0;
        if (v_u) v_u = _pos.first + counter< 8;
        if (v_d) v_d = _pos.second - counter >= 0;

        //horizontal
        if (piece1.is_legit_move(path::Horizontal, distance /*????*/)) {

            //left
            if (h_l) insert_if_legit(ret, _pos, std::make_pair(0, -counter), h_l);
            //right
            if (h_r) insert_if_legit(ret, _pos, std::make_pair(0, counter), h_r);

        }

        //vertical
        if (piece1.is_legit_move(path::Vertical, distance /*????*/)) {

            //left
            if (v_u) insert_if_legit(ret, _pos, std::make_pair(counter, 0), v_u);
            //right
            if (v_d) insert_if_legit(ret, _pos, std::make_pair(-counter, 0), v_d);

        }

        //diagonal
        if (piece1.is_legit_move(path::Diagonal, distance/*????*/)) {

            //up left
            if (d_1) insert_if_legit(ret, _pos, std::make_pair(counter, -counter), d_1);
            //up right
            if (d_2) insert_if_legit(ret, _pos, std::make_pair(counter, counter), d_2);
            //down right
            if (d_3) insert_if_legit(ret, _pos, std::make_pair(-counter, counter), d_3);
            //down left
            if (d_4) insert_if_legit(ret, _pos, std::make_pair(-counter, -counter), d_4);
        }

    }
    
    //add the L moves if needed
    if (piece1.is_legit_move(path::L, distance)) {

        insert_if_legit(ret, _pos, std::make_pair(2, 1), h);
        insert_if_legit(ret, _pos, std::make_pair(2, -1), h);
        insert_if_legit(ret, _pos, std::make_pair(1, 2), h);
        insert_if_legit(ret, _pos, std::make_pair(-1, 2), h);
        insert_if_legit(ret, _pos, std::make_pair(-2, 1), h);
        insert_if_legit(ret, _pos, std::make_pair(-2, -1), h);
        insert_if_legit(ret, _pos, std::make_pair(1, -2), h);
        insert_if_legit(ret, _pos, std::make_pair(-1, -2), h);

    }

    return ret;

}

/**
 * @brief Returns a reference to the piece in _pos position
 * 
 * @param _pos The position of the object
 * @return piece& The reference to the piece found
 */
piece& chessboard::piece_at_pos(const coords &_pos) const {

    return *board[_pos.first][_pos.second];

}

/**
 * @brief Returns a reference to the piece in [i][j] position
 * 
 * @param i The row index of the object
 * @param j The col index of the object
 * @return piece& The reference to the piece found
 */
piece& chessboard::piece_at_pos(const int i, const int j) const {

    return *board[i][j];

}

/**
 * @brief Checks if a pawn is in promotion position
 * 
 * @param _pos The position in which to search
 * @return true If the piece in _pos is a pawn that needs to be promoted
 * @return false If the piece in _pos is not a pawn or the position is not a promotion position
 */
bool chessboard::is_promotion(const coords &_pos) const {

    piece p = piece_at_pos(_pos);
    set side = p.get_side();

    if (is<pawn>(p) && ( _pos.first == 0 && side == set::Black || _pos.first == 7 && side == set::White) )
        return true;

    return false;

}

/**
 * @brief Method to promote a pawn to a choosen piece
 * 
 * @param _pos The position of the pawn to promote
 * @param _piece The alias of the piece to promote
 */
void chessboard::promote(const coords &_pos, const char _piece) {

    set side = piece_at_pos(_pos).get_side();

    delete board[_pos.first][_pos.second];

    //promote the piece based on the _piece parameter
    switch(_piece) {
        case 't':
            board[_pos.first][_pos.second] = new tower(side);
        case 'c':
            board[_pos.first][_pos.second] = new horse(side); 
        case 'a':
            board[_pos.first][_pos.second] = new bishop(side);
        case 'd':
            board[_pos.first][_pos.second] = new tower(side);
    }

}

/**
 * @brief Checks if the move is a pawn eating move
 * 
 * @param _path The path of the move
 * @param _start The initiali position of the piece to move
 * @param _end The final position of the piece to move
 * @return true If it's a pawn eating move
 * @return false If it's not a pawn eating move of if it's an illegal move for the pawn
 */
bool chessboard::is_pawn_eat(const path &_path, const coords &_start, const coords &_end) const {

    piece pawn = piece_at_pos(_start);
    piece oth_piece = piece_at_pos(_end);

    int direction = 0;

    //get the direction of the pawn based on his side
    if (pawn.get_side() == set::White) {
        direction = 1;
    } else  {
        direction = -1;
    }

    //if it's a legal move
    if(_path==path::Diagonal && get_distance(_start, _end) == direction && oth_piece.get_side() == opposite_of(pawn.get_side()))
        return true;

    return false;
    
}

std::pair<bool, coords> chessboard::is_enpassant(const path &_path, const coords &_start, const coords &_end) const {

    piece pawn1 = piece_at_pos(_start);
    piece oth_piece = piece_at_pos(last_move.second);

    int direction = 0;
    
    //get the direction of the pawn based on his side
    if (pawn1.get_side() == set::White) {
        direction = 1;
    } else  {
        direction = -1;
    }

    //if the last move was an opposite pawn moving by 2
    if (is<pawn>(oth_piece) && std::abs(get_distance(last_move.first, last_move.second)) == 2) {

        int mid = (last_move.first.first + last_move.first.second)/2;

        //if it's a legal move
        if (_path==path::Diagonal && get_distance(_start, _end) == direction && is_Vertical(last_move.first, _end) && mid == _end.first) {
        
            return std::make_pair(true, last_move.second);
        
        }

    }

    return std::make_pair(false, std::make_pair(0, 0));

}

std::pair<bool, coords> chessboard::is_castling(const path &_path, const coords &_start, const coords &_end) const {

    piece king = piece_at_pos(_start);

    //if it's an horizontal move
    if (_path == path::Horizontal) {

        //if it's castling with the left or right tower (and save the column of the tower)
        int col = _start.second;
        if (get_distance(_start, _end) == -2) {

            col = 0;

        } else if (get_distance(_start, _end) == 2) {

            col = 7;

        }

        piece oth_piece = piece_at_pos(_start.first, col);
        
        //if the oth_piece is a tower
        if (is<tower>(oth_piece)) {

            //if it's the first move for both
            if (king.is_first_move() && oth_piece.is_first_move())
                return std::make_pair(true, std::make_pair(_start.first, col));

        } 

    }

    return std::make_pair(false, std::make_pair(0, 0));
    
}

void chessboard::pawn_eat(const coords &_start, const coords &_end) {

    delete board[_end.first][_end.second];
    board[_end.first][_end.second] = board[_start.first][_start.second];
    board[_start.first][_start.second] = new empty_tile();

}

void chessboard::enpassant(const coords &_eat, const coords &_start, const coords &_end) {

    //move the pieces
    delete board[_eat.first][_eat.second];
    board[_eat.first][_eat.second] = new empty_tile();
    board[_end.first][_end.second] = board[_start.first][_start.second];
    board[_start.first][_start.second] = new empty_tile();

}

void chessboard::castling(const coords &_tower, const coords &_start, const coords &_end) {

    int col = _start.second;

    //find which tower to move (and save the destination column of the tower)
    if (_tower.second == 0) {
        col = 2;
    } else {
        col = 4;
    }

    //move the pieces
    board[_start.first][col] = board[_tower.first][_tower.second];
    board[_end.first][_end.second] = board[_start.first][_start.second];
    board[_tower.first][_tower.second] = new empty_tile();
    board[_start.first][_start.second] = new empty_tile();

}

bool chessboard::move(const coords &_start, const coords &_end) {

    return true;

}

void chessboard::print() const {

    for (int i = 7; i >= 0; i--) {
        std::cout << std::endl;
        for (unsigned int j = 0; j < 8; j++) {
            std::cout << piece_at_pos(std::make_pair(i, j)).get_alias() << " ";
        }
    }

}