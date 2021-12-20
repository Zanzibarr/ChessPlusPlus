/*
 * Object describing King piece of chess from Piece.
 * @author: Riccardo Modolo 2009667
 */

#include "../lib/piece.h"
using namespace std;
class king : public piece {
	
	private:
		bool first_move {true};

	public:
		king(set _side) : piece(_side) {
			valid_path[0] = path::Vertical;
			valid_path[1] = path::Horizontal;
			valid_path[2] = path::Diagonal;
		}

		bool is_valid_move(path _path, int _path_length) const {
			int vp_length = sizeof(valid_path)/sizeof(valid_path[0]);

			for(int i = 0; i < vp_length; i++)
				return (valid_path[i] == _path && _path_length == abs(1));

			return false;
		}

		set get_side() const { return side; }
		bool is_first_move() const { return first_move; }
		void moved() { first_move = false; }

};