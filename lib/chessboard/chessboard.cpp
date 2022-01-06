/**
 * @file chessboard.cpp
 * @author Zanella Matteo (matteo.zanella.3@studenti.unipd.it)
 * @brief Implementation of the chessboard
 * @version 0.1
 * @date 2021-12-26
 *  
 */

#include "chessboard.h"

//---------------------PUBLIC

//[V]
chessboard::chessboard(void) {

    board[7][0] = new tower(set::Black);
    board[7][1] = new horse(set::Black);
    board[7][2] = new bishop(set::Black);
    board[7][3] = new queen(set::Black);
    board[7][4] = new king(set::Black);
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
    board[0][3] = new queen(set::White);
    board[0][4] = new king(set::White);
    board[0][5] = new bishop(set::White);
    board[0][6] = new horse(set::White);
    board[0][7] = new tower(set::White);

    for (unsigned int i = 2; i < 6; i++) for (unsigned int j = 0; j < 8; j++)
        board[i][j] = new empty_tile();

    for (unsigned int i = 0; i < 2; i++) {
        for (unsigned int j = 0; j < 8; j++) {
            white.push_back(std::make_pair(i, j));
        }
    }

    for (unsigned int i = 6; i < 8; i++) {
        for (unsigned int j = 0; j < 8; j++) {
            black.push_back(std::make_pair(i, j));
        }
    }

    eaten = new empty_tile();
    moves.clear();

}

//[V]
chessboard::~chessboard(void) {

    for (unsigned int i = 0; i < 8; i++) for (unsigned int j = 0; j < 8; j++) {
        delete board[i][j];
    }
    delete eaten;

}

//[V]
std::vector<coords> chessboard::get_pieces(const set &_set) const {

    if (_set == set::White) return white;
    else return black;

}

//[V]
std::vector<coords> chessboard::get_moves(const coords &_pos) const {

    piece* piece1 = piece_at_pos(_pos);
    
    std::vector<coords> ret;

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

    //for check and checkmate alghoritms purpose, se consider only the pawn eating moves here
    if (is<pawn>(*piece1)) {

        int direction = (piece1->get_side() == set::White) ? 1 : -1;

        try_add_move(ret, _pos, std::make_pair(1*direction, -1));
        try_add_move(ret, _pos, std::make_pair(1*direction, 1));

    } else {
        
        while (counter <= piece1->get_max_distance() && (h_l || h_r || d_1 || d_2 || d_3 || d_4 || v_u || v_d)) {

            if (h_l) h_l = _pos.second - counter >= 0;
            if (h_r) h_r = _pos.second + counter < 8;
            if (d_1) d_1 = _pos.first + counter < 8 && _pos.second - counter >= 0;
            if (d_2) d_2 = _pos.first + counter < 8 && _pos.second + counter < 8;
            if (d_3) d_3 = _pos.first - counter >= 0 && _pos.second + counter < 8;
            if (d_4) d_4 = _pos.first - counter >= 0 && _pos.second - counter >= 0;
            if (v_u) v_u = _pos.first + counter < 8;
            if (v_d) v_d = _pos.first - counter >= 0;

            //add horizontal move if needed
            if (piece1->is_legit_move(path::Horizontal, counter)) {

                //left
                if (h_l) h_l = try_add_move(ret, _pos, std::make_pair(0, -counter));
                //right
                if (h_r) h_r = try_add_move(ret, _pos, std::make_pair(0, counter));

            }

            //add vertical move if needed
            if (piece1->is_legit_move(path::Vertical, counter)) {

                //up
                if (v_u) v_u = try_add_move(ret, _pos, std::make_pair(counter, 0));
                //down
                if (v_d) v_d = try_add_move(ret, _pos, std::make_pair(-counter, 0));
            }

            //add diagonal move if needed
            if (piece1->is_legit_move(path::Diagonal, counter)) {

                //up left
                if (d_1) d_1 = try_add_move(ret, _pos, std::make_pair(counter, -counter));
                //up right
                if (d_2) d_2 = try_add_move(ret, _pos, std::make_pair(counter, counter));
                //down right
                if (d_3) d_3 = try_add_move(ret, _pos, std::make_pair(-counter, counter));
                //down left
                if (d_4) d_4 = try_add_move(ret, _pos, std::make_pair(-counter, -counter));
            }

            counter++;
        }

    }
    
    //add the L moves if needed
    if (piece1->is_legit_move(path::L, 3)) {

        try_add_move(ret, _pos, std::make_pair(2, 1));
        try_add_move(ret, _pos, std::make_pair(2, -1));
        try_add_move(ret, _pos, std::make_pair(1, 2));
        try_add_move(ret, _pos, std::make_pair(-1, 2));
        try_add_move(ret, _pos, std::make_pair(-2, 1));
        try_add_move(ret, _pos, std::make_pair(-2, -1));
        try_add_move(ret, _pos, std::make_pair(1, -2));
        try_add_move(ret, _pos, std::make_pair(-1, -2));

    }
    
    return ret;

}

/**/std::pair<bool, bool> move(const set &_turn, const coords &_start, const coords &_end) {}
        
//[V]
void chessboard::print() const {

    for (int i = 7; i >= 0; i--) {
        std::cout << std::endl << i + 1 << "   ";

        for (unsigned int j = 0; j < 8; j++) {
            std::cout << " " << piece_at_pos(i, j)->get_alias();
            if (j!=7)
                std::cout << " |";
        }
        std::cout << std::endl << "    ";
        
        if (i!=0)
            std::cout << "-------------------------------";

    }
    
    std::cout << "\n    ";
    for (unsigned int i = 0; i < 8; i++)
        std::cout << " " << (char) (i + 'A') << "  ";

}



//---------------------PRIVATE

//[V]
bool chessboard::is_out(const coords &_pos) const{

    return _pos.first < 0 || _pos.first >= 8 || _pos.second < 0 || _pos.second >= 8;

}

//[V]
bool chessboard::opposites(const coords &_c1, const coords &_c2) const {

    return piece_at_pos(_c1)->get_side() == opposite_of(piece_at_pos(_c2)->get_side());

}

//[V]
piece* chessboard::piece_at_pos(const coords &_pos) const {

    return board[_pos.first][_pos.second];

}

//[V]
piece* chessboard::piece_at_pos(const int i, const int j) const {

    return board[i][j];

}

/**/coords chessboard::find(const set &_side, const piece* _piece) const {}

/**/coords chessboard::find(const set &_side, const char _piece) const {}

//[V]
void chessboard::edit_white_pos(const coords &_start, const coords &_end) {

    for (unsigned int i = 0; i < white.size(); i++) {
        if (white.at(i) == _start) {
            white.at(i) = _end;
            break;
        }
    }

}

//[V]
void chessboard::edit_black_pos(const coords &_start, const coords &_end) {

    for (unsigned int i = 0; i < black.size(); i++) {
        if (black.at(i) == _start) {
            black.at(i) = _end;
            break;
        }
    }

}

//[V]
void chessboard::eat_piece(const set &_side, const coords &_piece) {

    bool start_move = false;

    switch(_side) {
        case set::White:
            for (unsigned int i = 0; i < white.size() - 1; i++) {
                if (white.at(i) == _piece) start_move = true;
                if (start_move) white.at(i) = white.at(i+1);
            }
            white.pop_back();
        case set::Black:
            for (unsigned int i = 0; i < black.size() - 1; i++) {
                if (black.at(i) == _piece) start_move = true;
                if (start_move) black.at(i) = black.at(i+1);
            }
            black.pop_back();
    }

}

/**/void chessboard::add_piece(const set &_side, const coords &_piece) {}

//[V]
bool chessboard::try_add_move(std::vector<coords> &_moves, const coords _pos, coords _offset) const {

    coords pos_check = _pos + _offset;
    if (is_out(pos_check)) return false;

    bool ret = true;

    if (is<empty_tile>(*piece_at_pos(pos_check)))
        _moves.push_back(pos_check);
    
    else
        ret = false;

    if (opposites(pos_check, _pos))
        _moves.push_back(pos_check);

    return ret;

}

//[?]
bool chessboard::is_promotion(const coords &_pos) const {

    piece* p = piece_at_pos(_pos);
    set side = p->get_side();

    return is<pawn>(*p) && ( _pos.first == 0 && side == set::Black || _pos.first == 7 && side == set::White );

}

//[V]
bool chessboard::is_pawn_eat(const path &_path, const coords &_start, const coords &_end) const {

    piece* pawn = piece_at_pos(_start);
    piece* oth_piece = piece_at_pos(_end);

    //get the direction of the pawn based on his side
    int distance = (pawn->get_side() == set::White) ? 1 : -1;

    return _path==path::Diagonal && get_distance(_start, _end) == distance && opposites(_start, _end);

}

//[V]
std::pair<bool, coords> chessboard::is_enpassant(const path &_path, const coords &_start, const coords &_end) const {

    if (moves.size() == 0) return std::make_pair(false, std::make_pair(0, 0));
    std::pair<coords, coords> last_move = moves.at(moves.size() - 1);

    piece* pawn1 = piece_at_pos(_start);
    piece* oth_piece = piece_at_pos(last_move.second);
    
    //get the direction of the pawn based on his side
    int distance = (pawn1->get_side() == set::White) ? 1 : -1;

    //if the last move was an opposite pawn moving by 2
    if (is<pawn>(*oth_piece) && std::abs(get_distance(last_move.first, last_move.second)) == 2) {

        int mid = (last_move.first.first + last_move.second.first)/2;

        //if it's a legal move
        if (_path==path::Diagonal && get_distance(_start, _end) == distance && is_Vertical(last_move.first, _end) && mid == _end.first) {
        
            return std::make_pair(true, last_move.second);
        
        }

    }

    return std::make_pair(false, std::make_pair(0, 0));

}

//[V]
std::pair<bool, coords> chessboard::is_castling(const path &_path, const coords &_start, const coords &_end) const {

    piece* king = piece_at_pos(_start);

    //if it's an horizontal move
    if (_path == path::Horizontal) {

        //if it's castling with the left or right tower (and save the column of the tower)
        int col = _start.second;
        int col_end = _start.second;
        if (get_distance(_start, _end) == 2) {

            if (!is<empty_tile>(*piece_at_pos(_start.first, 5)) || !is<empty_tile>(*piece_at_pos(_start.first, 6)))
                return std::make_pair(false, std::make_pair(0, 0));

            col = 7;
            col_end = 5;

        } else if (get_distance(_start, _end) == -2) {
            
            if (!is<empty_tile>(*piece_at_pos(_start.first, 1)) || !is<empty_tile>(*piece_at_pos(_start.first, 2)) || !is<empty_tile>(*piece_at_pos(_start.first, 3)))
                return std::make_pair(false, std::make_pair(0, 0));

            col = 0;
            col_end = 3;

        }

        piece* oth_piece = piece_at_pos(_start.first, col);
        
        //if the oth_piece is a tower
        if (is<tower>(*oth_piece)) {

            //if it's the first move for both
            if (king->is_first_move() && oth_piece->is_first_move() && !is_in_danger(oth_piece->get_side(), std::make_pair(_start.first, col_end)))
                return std::make_pair(true, std::make_pair(_start.first, col));

        } 

    }

    return std::make_pair(false, std::make_pair(0, 0));
    
}

/**/void chessboard::do_legit(const coords &_start, const coords &_end) {}

/**/void chessboard::promote(const coords &_pos, const char piece) {}

/**/void chessboard::do_enpassant(const coords &_eat, const coords &_start, const coords &_end) {}

/**/void chessboard::do_castling(const coords &_tower, const coords &_start, const coords &_end) {}

/**/bool chessboard::is_in_danger(const set &_side, const coords &_to_check) const {}

/**/bool chessboard::check(const set &_side) const {}

/**/bool chessboard::checkmate(const set &_side) {}

/**/bool chessboard::checkmate_control(const coords &_start, const coords &_end) {}

/**/bool chessboard::draw() const {}

/**/void chessboard::undo(const int _special, const coords &_oth_piece, const coords &_start, const coords &_end, const piece* _eaten) {}