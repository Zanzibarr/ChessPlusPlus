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
            white_pieces.push_back(std::make_pair(i, j));
            black_pieces.push_back(std::make_pair(i+6, j));
        }
    }

}

//[V]
chessboard::~chessboard(void) {

    for (unsigned int i = 0; i < 8; i++) for (unsigned int j = 0; j < 8; j++) {
        board[i][j] = 0;
        delete board[i][j];
    }

    history.clear();
    white_pieces.clear();
    black_pieces.clear();

}

//[V]
chessboard::chessboard(const std::vector<piece*> &_copy) {

    for (unsigned int i = 0; i < _copy.size(); i++) {

        set side = _copy.at(i)->get_side();
        char p = tolower(_copy.at(i)->get_alias());

        switch(tolower(_copy.at(i)->get_alias())) {
            case ' ':
                board[i/8][i%8] = new empty_tile();
                break;
            case 'p':
                board[i/8][i%8] = new pawn(side);
                break;
            case 't':
                board[i/8][i%8] = new tower(side);
                break;
            case 'c':
                board[i/8][i%8] = new horse(side);
                break;
            case 'a':
                board[i/8][i%8] = new bishop(side);
                break;    
            case 'd':
                board[i/8][i%8] = new queen(side);
                break;
            case 'r':
                board[i/8][i%8] = new king(side);
                break;
        }

        switch(_copy.at(i)->get_side()) {
            case set::White: white_pieces.push_back(std::make_pair(i/8, i%8));
            case set::Black: black_pieces.push_back(std::make_pair(i/8, i%8));
        }

    }

}

//[V]
std::vector<coords> chessboard::get_pieces(const set &_set) const {

    return (_set == set::White) ? white_pieces : black_pieces;

}

//[V]
std::vector<coords>& chessboard::get_moves(const coords &_pos) const {

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

    if (is<king>(*piece1)) {

        if (is_castling(path::Horizontal, _pos, _pos + std::make_pair(0, 2)).first)
            try_add_move(ret, _pos, std::make_pair(0, 2));

        if (is_castling(path::Horizontal, _pos, _pos + std::make_pair(0, -2)).first)
            try_add_move(ret, _pos, std::make_pair(0, -2));

    }

    if (is<pawn>(*piece1)) {

        int direction = (piece1->get_side() == set::White) ? 1 : -1;
        
        if (is<empty_tile>(*piece_at_pos(_pos + std::make_pair(1*direction, 0))))
            try_add_move(ret, _pos, std::make_pair(1*direction, 0));
        if (piece1->is_first_move() && is<empty_tile>(*piece_at_pos(_pos + std::make_pair(2*direction, 0))))
            try_add_move(ret, _pos, std::make_pair(2*direction, 0));

        if (is_pawn_eat(path::Diagonal, _pos, _pos + std::make_pair(1*direction, -1)))
            try_add_move(ret, _pos, std::make_pair(1*direction, -1));
        if (is_pawn_eat(path::Diagonal, _pos, _pos + std::make_pair(1*direction, 1)))
            try_add_move(ret, _pos, std::make_pair(1*direction, 1));

        if (is_enpassant(path::Diagonal, _pos, _pos + std::make_pair(1*direction, 1)).first)
            try_add_move(ret, _pos, std::make_pair(1*direction, 1));
        if (is_enpassant(path::Diagonal, _pos, _pos + std::make_pair(1*direction, -1)).first)
            try_add_move(ret, _pos, std::make_pair(1*direction, -1));

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

//[V]
std::pair<bool, bool> chessboard::move(const set &_turn, const coords &_start, const coords &_end) {

    piece* piece1 = piece_at_pos(_start);
    set side = piece1->get_side();
    path path1 = get_path(_start, _end);
    
    if (_turn != set::Empty && _turn != side) {
        std::cout << "\nMossa illegale: " << _start.first << ";" << _start.second << " -> " << _end.first << ";" << _end.second << "\n";
        throw illegal_move_exception();
    }

    bool legit = false;
    std::pair<bool, coords> enpassant = std::make_pair(false, std::make_pair(0,0));
    std::pair<bool, coords> castling = std::make_pair(false, std::make_pair(0,0));

    std::vector<coords> piece_moves = get_moves(_start);
    
    for (unsigned int i = 0; i < piece_moves.size(); i++) {
        if (_end == piece_moves.at(i)) {
            legit = true;
            break;
        }
    }

    enpassant = is_enpassant(path1, _start, _end);
    castling = is_castling(path1, _start, _end);

    if (_turn != set::Empty) {

        std::vector<piece*> pieces = to_vector();
        chessboard check_ctrl {pieces};

        if (legit) check_ctrl.do_legit(_start, _end);
        else if (enpassant.first) check_ctrl.do_enpassant(enpassant.second, _start, _end);
        else if (castling.first) check_ctrl.do_castling(castling.second, _start, _end);
        else {
            std::cout << "\nMossa illegale: " << _start.first << ";" << _start.second << " -> " << _end.first << ";" << _end.second << "\n";
            throw illegal_move_exception();
        }

        /**/if (check_ctrl.check(side)) return std::make_pair(false, false);

    }

    if (enpassant.first) do_enpassant(enpassant.second, _start, _end);
    else if (castling.first) do_castling(castling.second, _start, _end);
    else if (legit) do_legit(_start, _end);
    else {
        std::cout << "\nMossa illegale: " << _start.first << ";" << _start.second << " -> " << _end.first << ";" << _end.second << "\n";
        throw illegal_move_exception();
    }

    if (_turn == set::Empty) {
        if (check(side)) return std::make_pair(false, false);
        else return std::make_pair(false, true);
    }

    if(piece1->is_first_move()) piece_at_pos(_end)->moved();
    history.push_back(std::make_pair(_start, _end));
    
    if (is_promotion(_end)) promote(_end);

    if (check(opposite_of(side))) {

        std::cout << "\nAttenzione: ";
    
        if (checkmate(opposite_of(_turn))) {
            std::cout << "Scacco matto\n";
            return std::make_pair(true, true);
        } else std::cout << "Scacco\n";

    }

    if (draw(opposite_of(side))) return std::make_pair(true, false);

    return std::make_pair(false, true);

}
        
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
std::vector<piece*> chessboard::to_vector() const {

    std::vector<piece*> ret;

    for (unsigned int i = 0; i < 64; i++) ret.push_back(piece_at_pos(i/8, i%8));

    return ret;

}

//[V]
bool chessboard::is_out(const coords &_pos) const{

    return _pos.first < 0 || _pos.first >= 8 || _pos.second < 0 || _pos.second >= 8;

}

//[V]
bool chessboard::opposites(const coords &_pos_1, const coords &_pos_2) const {

    return piece_at_pos(_pos_1)->get_side() == opposite_of(piece_at_pos(_pos_2)->get_side());

}

//[V]
piece* chessboard::piece_at_pos(const coords &_pos) const {

    return board[_pos.first][_pos.second];

}

//[V]
piece* chessboard::piece_at_pos(const int i, const int j) const {

    return board[i][j];

}

//[V]
coords chessboard::find(const set &_side, const piece* _piece) const {

    return find(_side, _piece->get_alias());

}

//[V]
coords chessboard::find(const set &_side, const char _piece) const {

    switch(_side) {
        case set::White:
            for (unsigned int i = 0; i < white_pieces.size(); i++) {
                if(tolower(_piece) == tolower(piece_at_pos(white_pieces.at(i))->get_alias())) return white_pieces.at(i);
            }
            break;
        case set::Black:
            for (unsigned int i = 0; i < black_pieces.size(); i++) {
                if(toupper(_piece) == piece_at_pos(black_pieces.at(i))->get_alias()) return black_pieces.at(i);
            }
            break;
    }

    return std::make_pair(0, 0);
    
}

//[V]
void chessboard::edit_pos(const set &_side, const coords &_start, const coords &_end) {

    switch(_side) {
        case set::White:
            for (unsigned int i = 0; i < white_pieces.size(); i++) {
                if (white_pieces.at(i) == _start) {
                    white_pieces.at(i) = _end;
                    break;
                }
            }
        case set::Black:
            for (unsigned int i = 0; i < black_pieces.size(); i++) {
                if (black_pieces.at(i) == _start) {
                    black_pieces.at(i) = _end;
                    break;
                }
            }
    }
}

//[V]
void chessboard::eat_piece(const set &_side, const coords &_piece) {

    bool start_move = false;

    switch(_side) {
        case set::White:
            for (unsigned int i = 0; i < white_pieces.size() - 1; i++) {
                if (white_pieces.at(i) == _piece) start_move = true;
                if (start_move) white_pieces.at(i) = white_pieces.at(i+1);
            }
            white_pieces.pop_back();
        case set::Black:
            for (unsigned int i = 0; i < black_pieces.size() - 1; i++) {
                if (black_pieces.at(i) == _piece) start_move = true;
                if (start_move) black_pieces.at(i) = black_pieces.at(i+1);
            }
            black_pieces.pop_back();
    }

}

//[V]
void chessboard::add_piece(const set &_side, const coords &_piece) {

    switch(_side) {
        case set::White: white_pieces.push_back(_piece);
        case set::Black: black_pieces.push_back(_piece);
    }

}

//[V]
bool chessboard::try_add_move(std::vector<coords> &_moves, const coords &_pos, const coords &_offset) const {

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

    if(is_out(_pos)) return false;

    piece* p = piece_at_pos(_pos);
    set side = p->get_side();

    return is<pawn>(*p) && ( _pos.first == 0 && side == set::Black || _pos.first == 7 && side == set::White );

}

//[V]
bool chessboard::is_pawn_eat(const path &_path, const coords &_start, const coords &_end) const {

    piece* piece1 = piece_at_pos(_start);

    if (is_out(_end) || !is<pawn>(*piece1)) return false;

    piece* piece2 = piece_at_pos(_end);

    //get the direction of the pawn based on his side
    int distance = (piece1->get_side() == set::White) ? 1 : -1;

    return _path==path::Diagonal && get_distance(_start, _end) == distance && opposites(_start, _end);

}

//[V]
std::pair<bool, coords> chessboard::is_enpassant(const path &_path, const coords &_start, const coords &_end) const {

    std::pair<bool, coords> false_ret = std::make_pair(false, std::make_pair(0, 0));

    if (history.size() == 0 || is_out(_end) || !is<pawn>(*piece_at_pos(_start))) return false_ret;

    std::pair<coords, coords> last_move = history.at(history.size() - 1);

    piece* piece1 = piece_at_pos(_start);
    piece* piece2 = piece_at_pos(last_move.second);
    
    int distance = (piece1->get_side() == set::White) ? 1 : -1;

    if (is<pawn>(*piece2) && std::abs(get_distance(last_move.first, last_move.second)) == 2) {

        int mid = (last_move.first.first + last_move.second.first)/2;

        if (_path==path::Diagonal && get_distance(_start, _end) == distance && last_move.first.second == _end.second && mid == _end.first)
            return std::make_pair(true, last_move.second);

    }

    return false_ret;

}

//[V]
std::pair<bool, coords> chessboard::is_castling(const path &_path, const coords &_start, const coords &_end) const {

    std::pair<bool, coords> false_ret = std::make_pair(false, std::make_pair(0, 0));

    piece* piece1 = piece_at_pos(_start);

    if (_path != path::Horizontal || is_out(_end) || std::abs(get_distance(_start, _end)) != 2 || !is<king>(*piece1)) return false_ret;

    int col;
    int col_end;
    if (get_distance(_start, _end) == 2) {

        if (!is<empty_tile>(*piece_at_pos(_start.first, 5)) || !is<empty_tile>(*piece_at_pos(_start.first, 6)))
            return false_ret;

        col = 7;
        col_end = 5;

    } else {
        
        if (!is<empty_tile>(*piece_at_pos(_start.first, 1)) || !is<empty_tile>(*piece_at_pos(_start.first, 2)) || !is<empty_tile>(*piece_at_pos(_start.first, 3)))
            return false_ret;

        col = 0;
        col_end = 3;

    }
    
    if (is_in_danger(piece1->get_side(), _start) || is_in_danger(piece1->get_side(), std::make_pair(_start.first, col_end)) || is_in_danger(piece1->get_side(), std::make_pair(_start.first, (_start.second + col_end) / 2)))
        return false_ret;

    piece* piece2 = piece_at_pos(_start.first, col);
    
    //if the oth_piece is a tower
    if (is<tower>(*piece2) && piece1->is_first_move() && piece2->is_first_move())
        return std::make_pair(true, std::make_pair(_start.first, col));

    return false_ret;
    
}

//[V]
void chessboard::do_legit(const coords &_start, const coords &_end) {

    piece* p1 = piece_at_pos(_start);
    set side = p1->get_side();

    bool eaten = !is<empty_tile>(*piece_at_pos(_end));
    
    delete board[_end.first][_end.second];

    if (is<pawn>(*p1)) board[_end.first][_end.second] = new pawn(p1->get_side());
    else if (is<tower>(*p1)) board[_end.first][_end.second] = new tower(p1->get_side());
    else if (is<horse>(*p1)) board[_end.first][_end.second] = new horse(p1->get_side());
    else if (is<bishop>(*p1)) board[_end.first][_end.second] = new bishop(p1->get_side());
    else if (is<queen>(*p1)) board[_end.first][_end.second] = new queen(p1->get_side());
    else if (is<king>(*p1)) board[_end.first][_end.second] = new king(p1->get_side());
    else if (is<empty_tile>(*p1)) board[_end.first][_end.second] = new empty_tile();

    delete board[_start.first][_start.second];
    board[_start.first][_start.second] = new empty_tile();

    if (eaten) eat_piece(opposite_of(side), _end);
    edit_pos(side, _start, _end);

}

//[V]
void chessboard::promote(const coords &_pos) {

    std::cout << std::endl << "Select the piece you wish to have your pawn promoted to: 't', 'c', 'a', 'd'";
    std::string in;
    std::cin >> in;
    char piece = tolower(in[0]);

    set side = piece_at_pos(_pos)->get_side();

    delete board[_pos.first][_pos.second];

    //promote the piece based on the _piece parameter
    switch(piece) {
        case 't':
            board[_pos.first][_pos.second] = new tower(side);
        case 'c':
            board[_pos.first][_pos.second] = new horse(side); 
        case 'a':
            board[_pos.first][_pos.second] = new bishop(side);
        case 'd':
            board[_pos.first][_pos.second] = new queen(side);
    }
    
    std::cout << std::endl;

}

//[V]
void chessboard::do_enpassant(const coords &_eat, const coords &_start, const coords &_end) {

    set side1 = piece_at_pos(_start)->get_side();
    set side2 = piece_at_pos(_eat)->get_side();

    piece* temp = board[_end.first][_end.second];
    board[_end.first][_end.second] = board[_start.first][_start.second];
    board[_start.first][_start.second] = temp;

    delete board[_eat.first][_eat.second];
    board[_eat.first][_eat.second] = new empty_tile();

    edit_pos(side1, _start, _end);
    eat_piece(side2, _eat);

}

//[V]
void chessboard::do_castling(const coords &_tower, const coords &_start, const coords &_end) {

    set side = piece_at_pos(_start)->get_side();

    int col = (_tower.second == 0) ? 3 : 5;

    piece* empty1 = board[_end.first][_end.second];
    piece* empty2 = board[_start.first][col];
    board[_end.first][_end.second] = board[_start.first][_start.second];
    board[_start.first][col] = board[_tower.first][_tower.second];
    board[_start.first][_start.second] = empty1;
    board[_tower.first][_tower.second] = empty2;

    edit_pos(side, _start, _end);
    edit_pos(side, _tower, std::make_pair(_tower.first, col));
    
}

//[V]
bool chessboard::is_in_danger(const set &_side, const coords &_to_check) const {

    std::vector<coords> danger_zone;

    switch(_side) {
        case set::White:
            for (unsigned int i = 0; i < black_pieces.size(); i++) {
                danger_zone = get_moves(black_pieces.at(i));
                for (unsigned j = 0; j < danger_zone.size(); j++) {
                    if (_to_check == danger_zone.at(j)) return true;
                }
                danger_zone.clear();
            }
            break;
        case set::Black:
            for (unsigned int i = 0; i < white_pieces.size(); i++) {
                danger_zone = get_moves(white_pieces.at(i));
                for (unsigned j = 0; j < danger_zone.size(); j++) {
                    if (_to_check == danger_zone.at(j)) return true;
                }
                danger_zone.clear();
            }
            break;
    }

    return false;

}

//[V]
bool chessboard::check(const set &_side) const {

    return is_in_danger(_side, find(_side, 'r'));

}

//[V]
bool chessboard::checkmate(const set &_side) const {

    int counter = 0;

    std::vector<piece*> board_vector = to_vector();
    std::vector<coords> pieces = (_side == set::White) ? white_pieces : black_pieces;

    while(counter < pieces.size()) {

        std::vector<coords> moves = get_moves(pieces.at(counter));

        for (unsigned int i = 0; i < moves.size(); i++) {

            chessboard check_ctrl {board_vector};

            if (check_ctrl.move(set::Empty, pieces.at(counter), moves.at(i)).second)
                return false;

        }

        counter++;

    }

    return true;

}

//[?]
bool chessboard::draw(const set &_side) const {
    
    return !check(_side) && checkmate(_side);
    
}