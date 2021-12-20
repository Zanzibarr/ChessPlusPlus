/*
 * Object describing King piece of chess from Piece.
 * @author: Riccardo Modolo 2009667
 */

#include "../lib/piece.h"

template< typename Type, typename DataType >
bool is( const DataType& data ){
	if( &data == NULL ) return false;
    return typeid( data ) == typeid( Type );
}

class king : public piece {

	private:
		bool first_move;

		bool legal_move(const std::pair<char, int> &_cur, const std::pair<char, int> &_aim) const {

			int rowDistance = _cur.first - _aim.first;
			int colDistance = _cur.second - _aim.second;

			return (std::abs(rowDistance) == 1 && std::abs(colDistance) == 1);

		}

		bool castling(const board &_b, const std::pair<char, int> &_cur, const std::pair<char, int> &_aim) const {
			
			if (!first_move) return false;
			if (_aim.first != _cur.first) return false;

			std::pair<piece, bool> piece_left = _b.get_piece(std::make_pair(_cur.first, 0));
			std::pair<piece, bool> piece_right = _b.get_piece(std::make_pair(_cur.first, 7));

			if (_cur.first == 'a') {
   				if(is<tower>(piece_left.first) && piece_left.second && _aim.second == 1) return true;
   				if(is<tower>(piece_right.first) && piece_left.second && _aim.second == 5) return true;
			} else {
   				if(is<tower>(piece_left.first) && piece_left.second && _aim.second == 1) return true;
   				if(is<tower>(piece_right.first) && piece_left.second && _aim.second == 5) return true;
			}

			return false;

		}

	public:
		king(set _side = set::Black) : first_move { true } {
			side = _side;
		}

		bool is_valid_move(const board &_b, const std::pair<char, int> &_cur, const std::pair<char, int> &_aim) const {

			if (!_b.is_reachable(_cur, _aim)) return false;
			if (_b.is_danger(side, _aim)) return false;

			bool valid = false;
			valid |= legal_move(_cur, _aim);
			valid |= castling(_b, _cur, _aim);

			return valid;

		}

		void moved() { first_move = false; }

};