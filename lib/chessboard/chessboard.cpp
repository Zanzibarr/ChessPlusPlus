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

std::vector<coords> chessboard::get_moves(const coords &_pos) const {

    piece piece1 = piece_at_pos(_pos);
    
    std::vector<coords> ret;
    int distance = 0;

    if (piece1.is_legit_move(path::Horizontal, distance)) {

        for (int i = 1; i < 8; i++) {
            if (_pos.second + i >= 8) break; 
            coords pos_check {_pos.first, _pos.second + i};
            if (is<empty_tile>(piece_at_pos(pos_check))) {
                ret.push_back(pos_check);
            } else if (piece_at_pos(pos_check).get_side() == opposite_of(piece1.get_side())) {
                ret.push_back(pos_check);
                break;
            } else break;
        }

        for (int i = 1; i < 8; i++) {
            if (_pos.second - i < 0) break; 
            coords pos_check {_pos.first, _pos.second - i};
            if (is<empty_tile>(piece_at_pos(pos_check))) {
                ret.push_back(pos_check);
            } else if (piece_at_pos(pos_check).get_side() == opposite_of(piece1.get_side())) {
                ret.push_back(pos_check);
                break;
            } else break;
        }

    }
    
    if (piece1.is_legit_move(path::Vertical, distance)) {

        for (int i = 1; i < 8; i++) {
            if (_pos.first + i >= 8) break; 
            coords pos_check {_pos.first + i, _pos.second};
            if (is<empty_tile>(piece_at_pos(pos_check))) {
                ret.push_back(pos_check);
            } else if (piece_at_pos(pos_check).get_side() == opposite_of(piece1.get_side())) {
                ret.push_back(pos_check);
                break;
            } else break;
        }

        for (int i = 1; i < 8; i++) {
            if (_pos.first - i < 0) break; 
            coords pos_check {_pos.first - i, _pos.second};
            if (is<empty_tile>(piece_at_pos(pos_check))) {
                ret.push_back(pos_check);
            } else if (piece_at_pos(pos_check).get_side() == opposite_of(piece1.get_side())) {
                ret.push_back(pos_check);
                break;
            } else break;
        }

    }
    
    if (piece1.is_legit_move(path::Diagonal, distance)) {

        for (int i = 1; i < 8; i++) {
            if (_pos.first + i >= 8 || _pos.second + i >= 8) break; 
            coords pos_check {_pos.first + i, _pos.second + i};
            if (is<empty_tile>(piece_at_pos(pos_check))) {
                ret.push_back(pos_check);
            } else if (piece_at_pos(pos_check).get_side() == opposite_of(piece1.get_side())) {
                ret.push_back(pos_check);
                break;
            } else break;
        }

        for (int i = 1; i < 8; i++) {
            if (_pos.first + i >= 8 || _pos.second - i < 0) break;
            coords pos_check {_pos.first + i, _pos.second - i};
            if (is<empty_tile>(piece_at_pos(pos_check))) {
                ret.push_back(pos_check);
            } else if (piece_at_pos(pos_check).get_side() == opposite_of(piece1.get_side())) {
                ret.push_back(pos_check);
                break;
            } else break;
        }

        for (int i = 1; i < 8; i++) {
            if (_pos.first - i < 0 || _pos.second + i >= 8) { break; std::cout << "out"; }
            coords pos_check {_pos.first - i, _pos.second + i};
            if (is<empty_tile>(piece_at_pos(pos_check))) {
                ret.push_back(pos_check);
            } else if (piece_at_pos(pos_check).get_side() == opposite_of(piece1.get_side())) {
                ret.push_back(pos_check);
                break;
            } else break;
        }

        for (int i = 1; i < 8; i++) {
            if (_pos.first - i < 0 || _pos.second - i < 0) break;
            coords pos_check {_pos.first - i, _pos.second - i};
            if (is<empty_tile>(piece_at_pos(pos_check))) {
                ret.push_back(pos_check);
            } else if (piece_at_pos(pos_check).get_side() == opposite_of(piece1.get_side())) {
                ret.push_back(pos_check);
                break;
            } else break;
        }

    }
    
    if (piece1.is_legit_move(path::L, distance)) {

        coords pos_check[8] {
                                std::make_pair(_pos.first + 2, _pos.second + 1), std::make_pair(_pos.first + 2, _pos.second - 1),
                                std::make_pair(_pos.first + 1, _pos.second + 2), std::make_pair(_pos.first - 1, _pos.second + 2),
                                std::make_pair(_pos.first - 2, _pos.second + 1), std::make_pair(_pos.first - 2, _pos.second - 1),
                                std::make_pair(_pos.first + 1, _pos.second - 2), std::make_pair(_pos.first - 1, _pos.second - 2),
                            };
        
        for (unsigned int i = 0; i < 8; i++) {
            if (is<empty_tile>(piece_at_pos(pos_check[i])) || piece_at_pos(pos_check[i]).get_side() == opposite_of(piece1.get_side())) {
                ret.push_back(pos_check[i]);
            }
        }

    }

    return ret;

}

piece& chessboard::piece_at_pos(const coords &_pos) const {

    return *board[_pos.first][_pos.second];

}

piece& chessboard::piece_at_pos(const int i, const int j) const {

    return *board[i][j];

}

bool chessboard::is_promotion(const coords &_pos) const {

    piece p = piece_at_pos(_pos);
    set side = p.get_side();

    if (is<pawn>(p) && ( _pos.first == 0 && side == set::Black || _pos.first == 7 && side == set::White) )
        return true;

    return false;

}

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