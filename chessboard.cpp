#include "../lib/chessboard.h"

chessboard::chessboard() {
    char row_b[8] {'T', 'C', 'A', 'D', 'R', 'A', 'C', 'T'};
    char row_b_p[8] {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'};
    char row_w[8] {'t', 'c', 'a', 'd', 'r', 'a', 'c', 't'};
    char row_w_p[8] {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'};
    for (unsigned int i = 0; i < 8; i++) {
        for (unsigned int j = 0; j < 8; j++) {
            switch (i) {
                case 0:
                    matrix[i][j].first = row_b[j];
                    matrix.[i][j].second = true;
                    break;
                case 1:
                    matrix[i][j].first = row_b_p[j];
                    matrix.[i][j].second = true;
                    break;
                case 6:
                    matrix[i][j].first = row_w[j];
                    matrix.[i][j].second = true;
                    break;
                case 7:
                    matrix[i][j].first = row_w_p[j];
                    matrix.[i][j].second = true;
                    break;
                default:
                    matrix[i][j].first = ' ';
                    matrix.[i][j].second = false;
            }
        }
    }
}

std::string chessboard::print_chessboard() const {
    for (unsigned int i = 0; i < 64; i++) {
        std::cout << matrix[i/8][i%8].first;
        if ((i + 1)%8 == 0) std::cout << std::endl;
    }
}
bool chessboard::in_chessboard(const std::pair<int, int> &_position) {
    return _position.first >= 0 && _position.first <= 7 && _position.second >= 0 && _position.second <= 7;
}

std::pair<char, bool> chessboard::get_piece(const std::pair<int, int> &_position) const {
    return matrix[_position.first][_position.second]; 
}

bool is_path_legit(path _path, const std::pair<int, int> _start,const std::pair<int, int> _end) const {
    set side = find_side(matrix[_start.first][_start.second]);
    switch (_path) {
        case path::Horizontal:
            int direction = _start.first < _end.first ? 1 : -1;
            int temp_position = _position.first + direction;
            while (in_chessboard(std::make_pair(temp_position, _start.second) && _start != _end) {
                if (find_side(matrix[temp_position][_start.second]) != side) return false;
                temp_position += direction;
            }
            return find_side(matrix[temp_position][_start.second]) != side;
            break;
        case path::Vertical:
            int direction = _start.second < _end.second ? 1 : -1;
            int temp_position = _position.second + direction;
            while (in_chessboard(std::make_pair(_start.first, temp_position) && _start != _end) {
                if (find_side(matrix[_start.first][temp_position]) != side) return false;
                temp_position += direction;
            }
            return find_side(matrix[_start.first][temp_position]) != side;
            break;
    }
}

set chessboard::find_side(char _piece) {
    char pieces[6] = {'t', 'c', 'a', 'd', 'r', 'p'};
    for (unsigned int i = 0; i < 6; i++) {
        if (_piece == pieces[i]) return set::White
    }
    return set::Black;
}