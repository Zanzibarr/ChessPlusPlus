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

bool chessboard::insert_if_legit(std::vector<coords> &_moves, const coords _pos, coords _offset) const {

    coords pos_check = std::make_pair(_pos.first + _offset.first, _pos.second + _offset.second);
    if (pos_check.first < 0 || pos_check.first >= 8 || pos_check.second < 0 || pos_check.second >= 8) return false;
    bool ret = true;

    if ((piece_at_pos(pos_check))->get_alias() == ' ')
        _moves.push_back(pos_check);
    else ret = false;

    if (piece_at_pos(pos_check)->get_side() == opposite_of(piece_at_pos(_pos)->get_side()))
        _moves.push_back(pos_check);

    return ret;

}

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

    if (is_type<pawn>(*piece1)) {

        insert_if_legit(ret, _pos, std::make_pair(1, -1));
        insert_if_legit(ret, _pos, std::make_pair(1, 1));

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
                if (h_l) h_l = insert_if_legit(ret, _pos, std::make_pair(0, -counter));
                //right
                if (h_r) h_r = insert_if_legit(ret, _pos, std::make_pair(0, counter));

            }

            //add vertical move if needed
            if (piece1->is_legit_move(path::Vertical, counter)) {

                //left
                if (v_u) v_u = insert_if_legit(ret, _pos, std::make_pair(counter, 0));
                //right
                if (v_d) v_d = insert_if_legit(ret, _pos, std::make_pair(-counter, 0));
            }

            //add diagonal move if needed
            if (piece1->is_legit_move(path::Diagonal, counter)) {

                //up left
                if (d_1) d_1 = insert_if_legit(ret, _pos, std::make_pair(counter, -counter));
                //up right
                if (d_2) d_2 = insert_if_legit(ret, _pos, std::make_pair(counter, counter));
                //down right
                if (d_3) d_3 = insert_if_legit(ret, _pos, std::make_pair(-counter, counter));
                //down left
                if (d_4) d_4 = insert_if_legit(ret, _pos, std::make_pair(-counter, -counter));
            }

            counter++;
        }

    }
    
    //add the L moves if needed
    if (piece1->is_legit_move(path::L, 3)) {

        insert_if_legit(ret, _pos, std::make_pair(2, 1));
        insert_if_legit(ret, _pos, std::make_pair(2, -1));
        insert_if_legit(ret, _pos, std::make_pair(1, 2));
        insert_if_legit(ret, _pos, std::make_pair(-1, 2));
        insert_if_legit(ret, _pos, std::make_pair(-2, 1));
        insert_if_legit(ret, _pos, std::make_pair(-2, -1));
        insert_if_legit(ret, _pos, std::make_pair(1, -2));
        insert_if_legit(ret, _pos, std::make_pair(-1, -2));

    }
    
    return ret;

}

piece* chessboard::piece_at_pos(const coords &_pos) const {

    return board[_pos.first][_pos.second];

}

piece* chessboard::piece_at_pos(const int i, const int j) const {

    return board[i][j];

}

bool chessboard::is_promotion(const coords &_pos) const {

    piece* p = piece_at_pos(_pos);
    set side = p->get_side();

    if (is_type<pawn>(*p) && ( _pos.first == 0 && side == set::Black || _pos.first == 7 && side == set::White) )
        return true;

    return false;

}

void chessboard::promote(const coords &_pos, const char _piece) {

    set side = piece_at_pos(_pos)->get_side();

    //delete board[_pos.first][_pos.second];

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

    piece* pawn = piece_at_pos(_start);
    piece* oth_piece = piece_at_pos(_end);

    int direction = 0;

    //get the direction of the pawn based on his side
    if (pawn->get_side() == set::White) {
        direction = 1;
    } else  {
        direction = -1;
    }

    //if it's a legal move
    if(_path==path::Diagonal && get_distance(_start, _end) == direction && oth_piece->get_side() == opposite_of(pawn->get_side()))
        return true;

    return false;
    
}

std::pair<bool, coords> chessboard::is_enpassant(const path &_path, const coords &_start, const coords &_end) const {

    piece* pawn1 = piece_at_pos(_start);
    piece* oth_piece = piece_at_pos(last_move.second);

    int direction = 0;
    
    //get the direction of the pawn based on his side
    if (pawn1->get_side() == set::White) {
        direction = 1;
    } else  {
        direction = -1;
    }

    //if the last move was an opposite pawn moving by 2
    if (is_type<pawn>(*oth_piece) && std::abs(get_distance(last_move.first, last_move.second)) == 2) {

        int mid = (last_move.first.first + last_move.first.second)/2;

        //if it's a legal move
        if (_path==path::Diagonal && get_distance(_start, _end) == direction && is_Vertical(last_move.first, _end) && mid == _end.first) {
        
            return std::make_pair(true, last_move.second);
        
        }

    }

    return std::make_pair(false, std::make_pair(0, 0));

}

void chessboard::do_enpassant(const coords &_eat, const coords &_start, const coords &_end) {

    //move the pieces
    //delete board[_end.first][_end.second];
    board[_end.first][_end.second] = new pawn(piece_at_pos(_start)->get_side());
    //delete board[_start.first][_start.second];
    board[_start.first][_start.second] = new empty_tile();
    //delete board[_eat.first][_eat.second];
    board[_eat.first][_eat.second] = new empty_tile();

}

std::pair<bool, coords> chessboard::is_castling(const path &_path, const coords &_start, const coords &_end) const {

    piece* king = piece_at_pos(_start);

    //if it's an horizontal move
    if (_path == path::Horizontal) {

        //if it's castling with the left or right tower (and save the column of the tower)
        int col = _start.second;
        if (get_distance(_start, _end) == -2) {

            if (!is_type<empty_tile>(*piece_at_pos(_start.first, 1)) || !is_type<empty_tile>(*piece_at_pos(_start.first, 2))) return std::make_pair(false, std::make_pair(0, 0));

            col = 0;

        } else if (get_distance(_start, _end) == 2) {
            
            if (!is_type<empty_tile>(*piece_at_pos(_start.first, 4)) || !is_type<empty_tile>(*piece_at_pos(_start.first, 5)) || !is_type<empty_tile>(*piece_at_pos(_start.first, 6))) return std::make_pair(false, std::make_pair(0, 0));

            col = 7;

        }

        piece* oth_piece = piece_at_pos(_start.first, col);
        
        //if the oth_piece is a tower
        if (is_type<tower>(*oth_piece)) {

            //if it's the first move for both
            if (king->is_first_move() && oth_piece->is_first_move())
                return std::make_pair(true, std::make_pair(_start.first, col));

        } 

    }

    return std::make_pair(false, std::make_pair(0, 0));
    
}

void chessboard::do_castling(const coords &_tower, const coords &_start, const coords &_end) {

        //delete board[_end.first][_end.second];
        board[_end.first][_end.second] = new king(piece_at_pos(_start)->get_side());
        //delete board[_start.first][_start.second];
        board[_start.first][_start.second] = new empty_tile();
        int col = 0;
        if (_tower.second == 0) {
            col = 2;
        } else col = 4;

        //delete board[_tower.first][col];
        board[_tower.first][col] = new tower(piece_at_pos(_tower)->get_side());
        //delete board[_tower.first][_tower.second];
        board[_tower.first][_tower.second] = new empty_tile();

}

void chessboard::do_legit(const coords &_start, const coords &_end) {

        piece* piece1 = piece_at_pos(_start);
        set side = piece1->get_side();
        piece* eaten = piece_at_pos(_end);

        if (is_type<pawn>(*piece1)) board[_end.first][_end.second] = new pawn(side);
        if (is_type<tower>(*piece1)) board[_end.first][_end.second] = new tower(side);
        if (is_type<horse>(*piece1)) board[_end.first][_end.second] = new horse(side);
        if (is_type<bishop>(*piece1)) board[_end.first][_end.second] = new bishop(side);
        if (is_type<king>(*piece1)) board[_end.first][_end.second] = new king(side);
        if (is_type<queen>(*piece1)) board[_end.first][_end.second] = new queen(side);
        //delete board[_start.first][_start.second];
        board[_start.first][_start.second] = new empty_tile();

}

void chessboard::undo(const int _special, const coords &_oth_piece, const coords &_start, const coords &_end, const piece* _eaten) {
    
    bool first_move = piece_at_pos(_end)->is_first_move();

    do_legit(_end, _start);

    board[_start.first][_start.second]->set_first_move(first_move);
    
    //delete board[_end.first][_end.second];

    switch(_special) {
        case 0:
            if (is_type<pawn>(*_eaten)) board[_end.first][_end.second] = new pawn(_eaten->get_side());
            if (is_type<tower>(*_eaten)) board[_end.first][_end.second] = new tower(_eaten->get_side());
            if (is_type<horse>(*_eaten)) board[_end.first][_end.second] = new horse(_eaten->get_side());
            if (is_type<bishop>(*_eaten)) board[_end.first][_end.second] = new bishop(_eaten->get_side());
            if (is_type<queen>(*_eaten)) board[_end.first][_end.second] = new queen(_eaten->get_side());
            if (is_type<empty_tile>(*_eaten)) board[_end.first][_end.second] = new empty_tile();
            break;
        case 1:
            //delete board[_oth_piece.first][_oth_piece.second];
            board[_oth_piece.first][_oth_piece.second] = new pawn(_eaten->get_side());
            board[_oth_piece.first][_oth_piece.second]->set_first_move(_eaten->is_first_move());
            break;
        case 2:
            //delete board[_oth_piece.first][_oth_piece.second];
            board[_oth_piece.first][_oth_piece.second] = new tower(_eaten->get_side());
            int col;
            if (get_distance(_start, _oth_piece) < 0) col = 2;
            else col = 4;
            //delete board[_start.first][col];
            board[_start.first][col] = new empty_tile();
            break;
    }

}

bool chessboard::check(const set &_side) const { return false; }

bool chessboard::checkmate(const set &_side) const { return false; }

bool chessboard::draw() const { return false; }

std::pair<bool, bool> chessboard::move(const coords &_start, const coords &_end) {

    piece* piece1 = piece_at_pos(_start);
    set side = piece1->get_side();
    path path1 = get_path(_start, _end);

    piece* eaten = nullptr;

    bool legit = false;
    bool pawn_eat = false;
    bool promotion = false;
    std::pair<bool, coords> enpassant = std::make_pair(false, std::make_pair(0,0));
    std::pair<bool, coords> castling = std::make_pair(false, std::make_pair(0,0));

    /*-- INIZIO CONTROLLI MOSSE SPECIALI O LEGALI --*/

    if (is_type<pawn>(*piece1)) {

        int distance = get_distance(_start, _end);
        legit = piece1->is_legit_move(path1, distance);
        if (legit) {
            legit &= is_type<empty_tile>(*piece_at_pos(_start.first + distance, _start.second));
            if (std::abs(distance)==2)
                legit &= is_type<empty_tile>(*piece_at_pos(_start.first + distance/2, _start.second));
        }
        pawn_eat = is_pawn_eat(path1, _start, _end);
        enpassant = is_enpassant(path1, _start, _end);
        promotion = is_promotion(_end);

    } else {

        std::vector<coords> moves = get_moves(_start);
        for (unsigned int i = 0; i < moves.size(); i++) {
            if (_end == moves.at(i)) {
                legit = true;
                break;
            }
        }
    }
    
    if (is_type<king>(*piece1)) {
        castling = is_castling(path1, _start, _end);
    }

    /*-- FINE CONTROLLI MOSSE SPECIALI O LEGALI --*/

    /*-- INIZIO MOSSE --*/

    if (legit || pawn_eat) {

        std::cout << "--" << piece1->is_first_move();

        eaten = piece_at_pos(_end);
        do_legit(_start, _end);

    } else if (enpassant.first) {

        eaten = piece_at_pos(enpassant.second);
        do_enpassant(enpassant.second, _start, _end);

    } else if (castling.first) {

        eaten = piece_at_pos(castling.second);
        do_castling(castling.second, _start, _end);

    } else {

        std::cout << "<<mossa illegale>>";
        return std::make_pair(false, false);

    }

    /*-- FINE MOSSE --*/

    /* INIZIO CONTROLLO SCACCO/PATTA/SCACCO MATTO --*/

    if (check(side)) {
        int special = 0;
        coords place = _end;
        if (enpassant.first) {
            special = 1;
            place = enpassant.second;
        }
        else if (castling.first) {
            special = 2;
            place = castling.second;
        }
        undo(special, place, _start, _end, eaten);
        return std::make_pair(false, false);
    }

    if (piece1->is_first_move()) piece_at_pos(_end)->moved();
    last_move = std::make_pair(_start, _end);
    
    if (promotion) {

        std::cout << std::endl << "Select the piece you wish to have your pawn promoted to: 't', 'c', 'a', 'd'";
        std::string in;
        std::cin >> in;
        char p = tolower(in[0]);
        promote(_end, p);
        std::cout << std::endl;

    }
    
    if (checkmate(opposite_of(side))) return std::make_pair(true, true);

    if (draw()) return std::make_pair(true, false);

    /* FINE CONTROLLO SCACCO/PATTA/SCACCO MATTO --*/

    //delete eaten;

    return std::make_pair(false, true);

}

void chessboard::print() const {

    for (int i = 7; i >= 0; i--) {
        std::cout << std::endl;
        for (unsigned int j = 0; j < 8; j++) {
            std::cout << piece_at_pos(std::make_pair(i, j))->get_alias() << " ";
        }
    }

}