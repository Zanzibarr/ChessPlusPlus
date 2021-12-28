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

    board[0][0] = new tower(set::Black);
    board[0][1] = new horse(set::Black);
    board[0][2] = new bishop(set::Black);
    board[0][3] = new king(set::Black);
    board[0][4] = new queen(set::Black);
    board[0][5] = new bishop(set::Black);
    board[0][6] = new horse(set::Black);
    board[0][7] = new tower(set::Black);

    for (unsigned int i = 2; i < 6; i++) for (unsigned int j = 0; j < 8; j++) {
        board[i][j] = new empty_tile();
    }

}

chessboard::~chessboard(void) {

    for (unsigned int i = 0; i < 8; i++) for (unsigned int j = 0; j < 8; j++) {
        delete board[i][j];
    }

}
/*
bool chessboard::is_promotion(const coords &_pos) const {

    if (is<pawn>(board[_pos.first][_pos.second])) {
        piece *p = board[_pos.first][_pos.second];
        if (_pos.first == 0 && p->get_side() == set::Black || _pos.first == 7 && p->get_side() == set::White) return true;
    }

    return false;

}

void chessboard::promote(const coords &_pos, const char piece) {

    set side = (_pos.first == 7) ? set::White : set::Black;

    switch(piece) {
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

bool chessboard::is_pawn_eat(const path &_p, const coords &_start, const coords &_end) const {

    int direction = 0;

    if (board[_start.first][_start.second]->get_side() == set::White) {
        direction = 1;
    } else  {
        direction = -1;
    }

    return _p==path::Diagonal && get_distance(_start, _end) == direction && board[_end.first][_end.second]->get_side() == opposite_of(board[_start.first][_start.second]->get_side());
    
}

std::pair<bool, coords> chessboard::is_enpassant(const path &_p, const coords &_start, const coords &_end) const {

    int direction = 0;

    if (board[_start.first][_start.second]->get_side() == set::White) {
        direction = 1;
    } else  {
        direction = -1;
    }

    if (is<pawn>(get(last_move.second)) && std::abs((int)(last_move.second.first - last_move.first.first)) == 2) {
        if (_p==path::Diagonal && get_distance(_start, _end) == direction && last_move.first.second == _end.second && std::min(last_move.first.first, last_move.first.second) + 1 == _end.first) {
            return std::make_pair(true, std::make_pair(std::min(last_move.first.first, last_move.first.second) + 1, _end.second));
        }
    }

    return std::make_pair(false, std::make_pair(0, 0));

}

std::pair<bool, coords> chessboard::is_castling(const path &_p, const coords &_start, const coords &_end) const {

    if (_p==path::Horizontal && get_distance(_start, _end) == -2) {
        if (is<tower>(board[_start.first][0]) && board[_start.first][_start.second]->is_first_move() && board[_start.first][0]->is_first_move()) {
            return std::make_pair(true, std::make_pair(_start.first, 2));
        }
    } else if (_p==path::Horizontal && get_distance(_start, _end) == 2) {
        if (is<tower>(board[_start.first][7]) && board[_start.first][_start.second]->is_first_move() && board[_start.first][7]->is_first_move()) {
            return std::make_pair(true, std::make_pair(_start.first, 4));
        }
    }

    return std::make_pair(false, std::make_pair(0, 0));
    
}

bool chessboard::move(const coords &_start, const coords &_end) {

    delete board[_end.first][_end.second];
    board[_end.first][_end.second] = board[_start.first][_start.second];
    board[_start.first][_start.second] = nullptr;

}
*/
void chessboard::print() const {

    for (unsigned int i = 7; i >= 0; i--) {
        std::cout << std::endl;
        for (unsigned int j = 0; j < 8; j++) {
            std::cout << board[i][j]->get_alias() << " ";
        }
    }

}