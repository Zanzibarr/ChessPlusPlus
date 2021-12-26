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
        board[i][j] = nullptr;
    }

}

chessboard::~chessboard(void) {

    for (unsigned int i = 0; i < 8; i++) for (unsigned int j = 0; j < 8; j++) {
        delete board[i][j];
    }

}

bool chessboard::is_promotion(const std::pair<unsigned int, unsigned int> &_pos) const {

    if (is<pawn>(board[_pos.first][_pos.second])) {
        piece *p = board[_pos.first][_pos.second];
        if (_pos.first == 0 && p->get_side() == set::Black || _pos.first == 7 && p->get_side() == set::White) return true;
    }

    return false;

}

void chessboard::promote(const std::pair<unsigned int, unsigned int> &_pos, const char piece) {

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

bool chessboard::pawn_eat(const path &_p, const std::pair<unsigned int, unsigned int> &_start, const std::pair<unsigned int, unsigned int> &_end) const {

    return _p==path::Diagonal && get_distance(_start, _end) == 1 && board[_end.first][_end.second]->get_side() == opposite_of(board[_start.first][_start.second]->get_side());

}

bool chessboard::move(const std::pair<unsigned int, unsigned int> &_start, const std::pair<unsigned int, unsigned int> &_end) {

    if(castling(_start, _end)) {
        
    }

}