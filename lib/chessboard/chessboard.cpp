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

//[VV]*/
chessboard::chessboard(void) {

    board[7][0] = new rook(set::Black);
    board[7][1] = new knight(set::Black);
    board[7][2] = new bishop(set::Black);
    board[7][3] = new queen(set::Black);
    board[7][4] = new king(set::Black);
    board[7][5] = new bishop(set::Black);
    board[7][6] = new knight(set::Black);
    board[7][7] = new rook(set::Black);

    for (unsigned int i = 0; i < 8; i++) {
        board[6][i] = new pawn(set::Black);
        board[1][i] = new pawn(set::White);
    }

    board[0][0] = new rook(set::White);
    board[0][1] = new knight(set::White);
    board[0][2] = new bishop(set::White);
    board[0][3] = new queen(set::White);
    board[0][4] = new king(set::White);
    board[0][5] = new bishop(set::White);
    board[0][6] = new knight(set::White);
    board[0][7] = new rook(set::White);

    for (unsigned int i = 2; i < 6; i++)
        for (unsigned int j = 0; j < 8; j++)
            board[i][j] = new empty_tile();

    for (unsigned int i = 0; i < 2; i++) {
        for (unsigned int j = 0; j < 8; j++) {
            add_piece(set::White, std::make_pair(i, j));
            add_piece(set::Black, std::make_pair(i+6, j));
        }
    }

    eaten_piece = new empty_tile();

}

//[?]*/
chessboard::~chessboard(void) {

    for (unsigned int i = 0; i < 8; i++) for (unsigned int j = 0; j < 8; j++) {
        board[i][j] = nullptr;
        delete board[i][j];
    }

    history.clear();
    white_pieces.clear();
    black_pieces.clear();

    history.~vector();
    white_pieces.~vector();
    black_pieces.~vector();

    delete eaten_piece;

}

//[VV]*/
std::vector<coords> chessboard::get_pieces(const set &_set) const {
    
    return (_set == set::White) ? white_pieces : black_pieces;
    
}

//[V]*/
std::vector<coords> chessboard::get_moves(const coords &_pos, const bool with_castling) const {

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

    int counter = 1;

    if (is<king>(*piece1) && with_castling) {

        if (is_castling(_pos, _pos + std::make_pair(0, 2)).first)
            try_add_move(ret, _pos, std::make_pair(0, 2));

        if (is_castling(_pos, _pos + std::make_pair(0, -2)).first)
            try_add_move(ret, _pos, std::make_pair(0, -2));

    }

    if (is<pawn>(*piece1)) {

        int direction = (piece1->get_side() == set::White) ? 1 : -1;
        
        if (is<empty_tile>(*piece_at_pos(_pos + std::make_pair(direction, 0))))
            try_add_move(ret, _pos, std::make_pair(direction, 0));
        if (piece1->is_first_move() && is<empty_tile>(*piece_at_pos(_pos + std::make_pair(direction, 0))) && is<empty_tile>(*piece_at_pos(_pos + std::make_pair(2*direction, 0))))
            try_add_move(ret, _pos, std::make_pair(2*direction, 0));

        if (is_pawn_eat(_pos, _pos + std::make_pair(1*direction, -1)))
            try_add_move(ret, _pos, std::make_pair(1*direction, -1));
        if (is_pawn_eat(_pos, _pos + std::make_pair(1*direction, 1)))
            try_add_move(ret, _pos, std::make_pair(1*direction, 1));

        if (is_enpassant(_pos, _pos + std::make_pair(1*direction, 1)).first)
            try_add_move(ret, _pos, std::make_pair(1*direction, 1));
        if (is_enpassant(_pos, _pos + std::make_pair(1*direction, -1)).first)
            try_add_move(ret, _pos, std::make_pair(1*direction, -1));

    } else if (is<knight>(*piece1)) {

        try_add_move(ret, _pos, std::make_pair(2, 1));
        try_add_move(ret, _pos, std::make_pair(2, -1));
        try_add_move(ret, _pos, std::make_pair(1, 2));
        try_add_move(ret, _pos, std::make_pair(-1, 2));
        try_add_move(ret, _pos, std::make_pair(-2, 1));
        try_add_move(ret, _pos, std::make_pair(-2, -1));
        try_add_move(ret, _pos, std::make_pair(1, -2));
        try_add_move(ret, _pos, std::make_pair(-1, -2));
    
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
    
    return ret;

}

//[V]*/
std::pair<bool, bool> chessboard::move(const set &_turn, const coords &_start, const coords &_end) {

    piece* piece1 = piece_at_pos(_start);
    set side = piece1->get_side();
    
    if (_turn != set::Empty && _turn != side)
        throw illegal_move_exception();

    bool legit;
    std::pair<bool, coords> castling;
    std::pair<bool, coords> enpassant;

    castling = is_castling(_start, _end);
    if (!castling.first) enpassant = is_enpassant(_start, _end);
    if (!castling.first && !enpassant.first) legit = is_legit(_start, _end);

    /*
     If turn == set::Empty, that means the move method is called from the checkmate control method
     If the move method is called from the checkmate control method, I don't need to execute the moves in a copy chessboard
     which is needed to "undo" the move in a check situation, since this is just a control move and is not a final move.
    
    std::vector<piece*> pieces = to_vector();
    //memory leak here
    check_ctrl = new chessboard{pieces, history};

    if (castling.first) check_ctrl->do_castling(castling.second, _start, _end);
    else if (enpassant.first) check_ctrl->do_enpassant(enpassant.second, _start, _end);
    else if (legit) check_ctrl->do_legit(_start, _end);
    else return FAILED;

    if (check_ctrl->check(side))
        return FAILED;
    else if (_turn == set::Empty)
        return SUCCESS;
    */

    int special = 0;
    coords second_piece = ILLEGAL_COORDS;

    if (castling.first) {
        second_piece = castling.second;
        do_castling(castling.second, _start, _end);
        special = 1;
    } else if (enpassant.first) {
        second_piece = enpassant.second;
        do_enpassant(enpassant.second, _start, _end);
        special = 2;
    } else if (legit) do_legit(_start, _end);
    else throw illegal_move_exception();

    bool is_on_check = check(side);
    if (is_on_check || _turn == set::Empty)
        undo(special, _start, _end, second_piece, side);
        
    if (is_on_check)
        return FAILED;
    else if (_turn == set::Empty)
        return SUCCESS;

    piece_at_pos(_end)->moved();

    history.push_back(std::make_pair(_start, _end));
    
    if (is_promotion(_end))
        do_promotion(_end);

    //AGGIUNGERE IN QUALCHE MODO LA PROMOZIONE ALL'HISTORY

    if (check(opposite_of(side))) {

        std::cout << "\nSei sotto scacco.\n";

        if (checkmate(opposite_of(side)))
            return CHECKMATE;

    }

    if (draw(opposite_of(side)))
        return DRAW;

    return SUCCESS;

}

//[VV]*/
void chessboard::print() const {

    std::cout << std::endl << "     --- --- --- --- --- --- --- --- ";

    for (int i = 7; i >= 0; i--) {
        std::cout << std::endl << i + 1 << "   ";

        std::cout << "|";
        for (unsigned int j = 0; j < 8; j++) {
            std::cout << " " << piece_at_pos(i, j)->get_alias() << " ";
            if (j!=7)
                std::cout << "|";
        }
        std::cout << "|" << std::endl << "    ";
        
        if (i!=0)
            std::cout << " --- --- --- --- --- --- --- --- ";

    }
    
    std::cout << " --- --- --- --- --- --- --- --- " << std::endl << std::endl << "     ";
    
    for (unsigned int i = 0; i < 8; i++)
        std::cout << " " << (char) (i + 'A') << "  ";

    std::cout << std::endl << std::endl;

}



//---------------------PRIVATE


//[VV]*/
/*chessboard::chessboard(const std::vector<piece*> &_copy, const std::vector<std::pair<coords, coords>> _history) {

    for (unsigned int i = 0; i < _copy.size(); i++) {

        set side = _copy.at(i)->get_side();

        switch(std::tolower(_copy.at(i)->get_alias())) {
            case ' ':
                board[i/8][i%8] = new empty_tile();
                break;
            case 'p':
                board[i/8][i%8] = new pawn(side);
                break;
            case 't':
                board[i/8][i%8] = new rook(side);
                break;
            case 'c':
                board[i/8][i%8] = new knight(side);
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

        board[i/8][i%8]->set_first_move(_copy.at(i)->is_first_move());

        add_piece(side, std::make_pair(i/8, i%8));

    }

    history = _history;

}*/

//[VV]*/
std::vector<piece*> chessboard::to_vector() const {

    std::vector<piece*> ret;

    for (unsigned int i = 0; i < 64; i++) ret.push_back(piece_at_pos(i/8, i%8));

    return ret;

}

//[VV]*/
bool chessboard::is_out(const coords &_pos) const {
    
    return _pos.first < 0 || _pos.first >= 8 || _pos.second < 0 || _pos.second >= 8;
    
}

//[VV]*/
bool chessboard::opposites(const coords &_pos_1, const coords &_pos_2) const {

    return piece_at_pos(_pos_1)->get_side() == opposite_of(piece_at_pos(_pos_2)->get_side());

}

//[VV]*/
piece* chessboard::piece_at_pos(const coords &_pos) const {

    return board[_pos.first][_pos.second];

}

//[VV]*/
piece* chessboard::piece_at_pos(const int i, const int j) const {

    return board[i][j];

}

//[VV]*/
bool chessboard::contains(const set &_side, const char _piece_alias) const {

    return find(_side, _piece_alias).at(0) != ILLEGAL_COORDS;

}

//[VV]*/
std::vector<coords> chessboard::find(const set &_side, const char _piece_alias) const {

    std::vector<coords> ret {ILLEGAL_COORDS};

    switch(_side) {
        case set::White:

            for (unsigned int i = 0; i < white_pieces.size(); i++)
                if(std::tolower(_piece_alias) == std::tolower(piece_at_pos(white_pieces.at(i))->get_alias())) {
                    ret.clear();
                    ret.push_back(white_pieces.at(i));
                }

            break;

        case set::Black:

            for (unsigned int i = 0; i < black_pieces.size(); i++)
                if(std::toupper(_piece_alias) == piece_at_pos(black_pieces.at(i))->get_alias()) {
                    ret.clear();
                    ret.push_back(black_pieces.at(i));
                }

            break;

    }

    return ret;
    
}

//[VV]*/
void chessboard::edit_pos(const set &_side, const coords &_start, const coords &_end) {

    switch(_side) {
        case set::White:

            for (unsigned int i = 0; i < white_pieces.size(); i++) {
                if (white_pieces.at(i) == _start) {
                    white_pieces.at(i) = _end;
                    break;
                }
            }

            break;

        case set::Black:

            for (unsigned int i = 0; i < black_pieces.size(); i++) {
                if (black_pieces.at(i) == _start) {
                    black_pieces.at(i) = _end;
                    break;
                }
            }

            break;
    }

}

//[VV]*/
void chessboard::eat_piece(const set &_side, const coords &_piece) {

    bool start_moving = false;

    switch(_side) {

        case set::White:

            for (unsigned int i = 0; i < white_pieces.size() - 1; i++) {
                if (white_pieces.at(i) == _piece) start_moving = true;
                if (start_moving) white_pieces.at(i) = white_pieces.at(i+1);
            }
            white_pieces.pop_back();

            break;

        case set::Black:

            for (unsigned int i = 0; i < black_pieces.size() - 1; i++) {
                if (black_pieces.at(i) == _piece) start_moving = true;
                if (start_moving) black_pieces.at(i) = black_pieces.at(i+1);
            }
            black_pieces.pop_back();

            break;
    }

}

//[VV]*/
void chessboard::add_piece(const set &_side, const coords &_piece) {

    switch(_side) {
        case set::White:
            white_pieces.push_back(_piece);
            break;
        case set::Black:
            black_pieces.push_back(_piece);
            break;
    }

}

//[VV]*/
bool chessboard::try_add_move(std::vector<coords> &_moves, const coords &_pos, const coords &_offset) const {

    coords pos_check = _pos + _offset;
    if (is_out(pos_check))
        return false;

    bool ret = true;

    if (is<empty_tile>(*piece_at_pos(pos_check)))
        _moves.push_back(pos_check);
    
    else
        ret = false;

    if (opposites(pos_check, _pos))
        _moves.push_back(pos_check);

    return ret;

}

//[VV]*/
bool chessboard::is_legit(const coords &_start, const coords &_end) const {

    if (is_out(_end))
        return false;

    std::vector<coords> piece_moves = get_moves(_start, false);
    
    for (unsigned int i = 0; i < piece_moves.size(); i++) {
        if (_end == piece_moves.at(i))
            return true;
    }

    return false;

}

//[VV]*/
bool chessboard::is_pawn_eat(const coords &_start, const coords &_end) const {

    piece* piece1 = piece_at_pos(_start);
    if (is_out(_end) || !is<pawn>(*piece1))
        return false;

    path path1 = get_path(_start, _end);

    //get the direction of the pawn based on his side
    int distance = (piece1->get_side() == set::White) ? 1 : -1;

    if (path1==path::Diagonal && get_distance(_start, _end) == distance && opposites(_start, _end))
        return true;

    return false;

}

//[VV]*/
std::pair<bool, coords> chessboard::is_castling(const coords &_start, const coords &_end) const {

    path path1 = get_path(_start, _end);
    piece* piece1 = piece_at_pos(_start);
    const std::pair<bool, coords> FALSE_RET {false, ILLEGAL_COORDS};

    if (!is<king>(*piece1) || path1 != path::Horizontal || is_out(_end) || std::abs(get_distance(_start, _end)) != 2)
        return FALSE_RET;

    int col;
    int col_end;
    if (get_distance(_start, _end) == 2) {

        if (!is<empty_tile>(*piece_at_pos(_start.first, 5)) || !is<empty_tile>(*piece_at_pos(_start.first, 6)))
            return FALSE_RET;

        col = 7;
        col_end = 5;

    } else {
        
        if (!is<empty_tile>(*piece_at_pos(_start.first, 1)) || !is<empty_tile>(*piece_at_pos(_start.first, 2)) || !is<empty_tile>(*piece_at_pos(_start.first, 3)))
            return FALSE_RET;

        col = 0;
        col_end = 3;

    }
    
    if (is_in_danger(piece1->get_side(), _start) || is_in_danger(piece1->get_side(), std::make_pair(_start.first, col_end)) || is_in_danger(piece1->get_side(), _end))
        return FALSE_RET;

    piece* piece2 = piece_at_pos(_start.first, col);
    
    //if the oth_piece is a tower
    if (is<rook>(*piece2) && piece1->is_first_move() && piece2->is_first_move())
        return std::make_pair(true, std::make_pair(_start.first, col));

    return FALSE_RET;
    
}

//[VV]*/
std::pair<bool, coords> chessboard::is_enpassant(const coords &_start, const coords &_end) const {

    std::pair<bool, coords> false_ret = std::make_pair(false, ILLEGAL_COORDS);

    if (history.size() == 0 || is_out(_end) || !is<pawn>(*piece_at_pos(_start)))
        return false_ret;

    path path1 = get_path(_start, _end);
    std::pair<coords, coords> last_move = history.at(history.size() - 1);

    piece* piece1 = piece_at_pos(_start);
    piece* piece2 = piece_at_pos(last_move.second);
    
    int distance = (piece1->get_side() == set::White) ? 1 : -1;

    if (is<pawn>(*piece2) && std::abs(get_distance(last_move.first, last_move.second)) == 2) {

        int mid = (last_move.first.first + last_move.second.first)/2;

        if (path1==path::Diagonal && get_distance(_start, _end) == distance && last_move.first.second == _end.second && mid == _end.first)
            return std::make_pair(true, last_move.second);

    }

    return false_ret;

}

//[VV]*/
bool chessboard::is_promotion(const coords &_pos) const {

    if(is_out(_pos))
        return false;

    piece* p = piece_at_pos(_pos);
    set side = p->get_side();

    if (is<pawn>(*p) && ( _pos.first == 0 && side == set::Black || _pos.first == 7 && side == set::White ))
        return true;

    return false;

}

//[VV]*/
void chessboard::do_legit(const coords &_start, const coords &_end) {

    piece* p1 = piece_at_pos(_start);
    set side = p1->get_side();

    bool eaten = !is<empty_tile>(*piece_at_pos(_end));

    delete eaten_piece;

    if (is<pawn>(*p1)) eaten_piece = new pawn(p1->get_side());
    else if (is<rook>(*p1)) eaten_piece = new rook(p1->get_side());
    else if (is<knight>(*p1)) eaten_piece = new knight(p1->get_side());
    else if (is<bishop>(*p1)) eaten_piece = new bishop(p1->get_side());
    else if (is<queen>(*p1)) eaten_piece = new queen(p1->get_side());
    else if (is<king>(*p1)) eaten_piece = new king(p1->get_side());
    else if (is<empty_tile>(*p1)) eaten_piece = new empty_tile();

    piece* temp = board[_end.first][_end.second];
    board[_end.first][_end.second] = eaten_piece;
    eaten_piece = temp;

    delete board[_start.first][_start.second];
    board[_start.first][_start.second] = new empty_tile();

    if (eaten) eat_piece(opposite_of(side), _end);
    edit_pos(side, _start, _end);

}

//[VV]*/
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

//[VV]*/
void chessboard::do_enpassant(const coords &_eat, const coords &_start, const coords &_end) {

    set side1 = piece_at_pos(_start)->get_side();
    set side2 = piece_at_pos(_eat)->get_side();

    piece* temp = board[_end.first][_end.second];
    board[_end.first][_end.second] = board[_start.first][_start.second];
    board[_start.first][_start.second] = temp;

    delete eaten_piece;
    eaten_piece = new empty_tile();

    temp = eaten_piece;
    eaten_piece = board[_eat.first][_eat.second];
    board[_eat.first][_eat.second] = temp;

    edit_pos(side1, _start, _end);
    eat_piece(side2, _eat);

}

//[VV]*/
void chessboard::do_promotion(const coords &_pos) {

    bool exit_cond = false;

    while(!exit_cond) {

        std::cout << std::endl << "\nSelect the piece you wish to have your pawn promoted to: 't', 'c', 'a', 'd': ";
        std::string in;
        std::cin >> in;
        char piece = std::tolower(in[0]);

        set side = piece_at_pos(_pos)->get_side();

        delete board[_pos.first][_pos.second];

        //promote the piece based on the _piece parameter
        switch(piece) {
            case 't':
                board[_pos.first][_pos.second] = new rook(side);
                exit_cond = true;
                break;
            case 'c':
                board[_pos.first][_pos.second] = new knight(side); 
                exit_cond = true;
                break;
            case 'a':
                board[_pos.first][_pos.second] = new bishop(side);
                exit_cond = true;
                break;
            case 'd':
                board[_pos.first][_pos.second] = new queen(side);
                exit_cond = true;
                break;
        }
        
        std::cout << std::endl;

    }

}

//[VV]*/
bool chessboard::is_in_danger(const set &_side, const coords &_to_check) const {

    if (_to_check == ILLEGAL_COORDS) return false;

    std::vector<coords> danger_zone;

    switch(_side) {

        case set::White:

            for (unsigned int i = 0; i < black_pieces.size(); i++) {

                danger_zone = get_moves(black_pieces.at(i));
                for (unsigned j = 0; j < danger_zone.size(); j++) {

                    if (_to_check == danger_zone.at(j))
                        return true;

                }

            }

            break;

        case set::Black:
            
            for (unsigned int i = 0; i < white_pieces.size(); i++) {

                danger_zone = get_moves(white_pieces.at(i));
                for (unsigned j = 0; j < danger_zone.size(); j++) {

                    if (_to_check == danger_zone.at(j))
                        return true;
                    
                }

            }
            
            break;
    
    }

    return false;

}

//[VV]*/
bool chessboard::check(const set &_side) const {

    return is_in_danger( _side, find(_side, 'r').at(0) );

}

//[VV]*/
bool chessboard::checkmate(const set &_side) {

    int counter = 0;

    std::vector<piece*> board_vector = to_vector();
    std::vector<coords> pieces = (_side == set::White) ? white_pieces : black_pieces;

    while(counter < pieces.size()) {

        std::vector<coords> moves = get_moves(pieces.at(counter), false);

        for (unsigned int i = 0; i < moves.size(); i++) {

            if (move(set::Empty, pieces.at(counter), moves.at(i)).second)
                return false;

        }

        counter++;

    }

    return true;

}

//[?]*/
bool chessboard::draw(const set &_side) {
    
    return (!check(_side) && checkmate(_side)) || draw_for_pieces();
    
}

//[?]*/
bool chessboard::draw_for_pieces() const {

    bool w_bishop_found = contains(set::White, 'a');
    bool b_bishop_found = contains(set::Black, 'a');

    bool w_knight_found = contains(set::White, 'c');
    bool b_knight_found = contains(set::Black, 'c');

    coords w_bishop = find(set::White, 'a').at(0);
    coords b_bishop = find(set::Black, 'a').at(0);

    bool w_knight_numb = find(set::White, 'c').size() == 2;
    bool b_knight_numb = find(set::Black, 'c').size() == 2;

    bool ret = false;
    ret |= (white_pieces.size() == 1 && black_pieces.size() == 1);
    ret |= (white_pieces.size() == 2 && w_bishop_found && black_pieces.size() == 1) || (black_pieces.size() == 2 && b_bishop_found && white_pieces.size() == 1);
    ret |= (white_pieces.size() == 2 && w_knight_found && black_pieces.size() == 1) || (black_pieces.size() == 2 && b_knight_found && white_pieces.size() == 1);
    ret |= (white_pieces.size() == 2 && w_bishop_found && black_pieces.size() == 2 && b_bishop_found && (w_bishop.first + w_bishop.second) % 2 == (b_bishop.first + b_bishop.second) % 2);
    ret |= (white_pieces.size() == 3 && black_pieces.size() == 1 && w_knight_found && w_knight_numb) || (black_pieces.size() == 3 && white_pieces.size() == 1 && b_knight_found && b_knight_numb);

    return ret;

}

void chessboard::undo(const int _move_type, const coords _initial_pos, const coords _final_pos, const coords _oth_pos, const set _side) {

    piece* temp = board[_final_pos.first][_final_pos.second];
    board[_final_pos.first][_final_pos.second] = board[_initial_pos.first][_initial_pos.second];
    board[_initial_pos.first][_initial_pos.second] = temp;
    edit_pos(_side, _final_pos, _initial_pos);

    int column;

    switch(_move_type) {

        //legit
        case 0: 
            temp = eaten_piece;
            eaten_piece = board[_final_pos.first][_final_pos.second];
            board[_final_pos.first][_final_pos.second] = temp;
            if (!is<empty_tile>(*piece_at_pos(_final_pos))) add_piece(opposite_of(_side), _final_pos);
            break;
        
        //castling
        case 1:
            temp = board[_oth_pos.first][_oth_pos.second];
            column = (_final_pos.second - _initial_pos.second < 0) ? 3 : 5;
            board[_oth_pos.first][_oth_pos.second] = board[_oth_pos.first][column];
            board[_oth_pos.first][column] = temp;
            edit_pos(_side, std::make_pair(_oth_pos.first, column), _oth_pos);
            break;

        //enpassant
        case 2:
            temp = eaten_piece;
            eaten_piece = board[_oth_pos.first][_oth_pos.second];
            board[_oth_pos.first][_oth_pos.second] = temp;
            add_piece(opposite_of(_side), _oth_pos);
            break;

    }

}