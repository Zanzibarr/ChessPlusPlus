/*
 * Object describing pedestrian piece of chess from Piece.
 *
 * @author: Riccardo Modolo 2009667
 */
#include "../lib/Piece.h"
class pedestrian : public piece {

	private:
		bool first_move {true};

	public:
		pedestrian(set _side = set::Black) : piece(_side){
			valid_path[0] = path::Vertical;
		}
		//A valid Move for king is one space in any Direction
		bool is_valid_move(chessboard b, path _path, int _path_length) const {
			int vp_length = sizeof(valid_path)/sizeof(valid_path[0]);

			for(int i = 0; i < vp_length; i++)
				return (valid_path[i] == _path && (_path_length == 1 || (is_first_move() && _path_length == 2)));

			return false;
		}

		set get_side() const { return side; }
		bool is_first_move() const { return first_move; }
		void moved() { first_move = false; }
};