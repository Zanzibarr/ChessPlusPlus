/*
 * Object describing pedestrian piece of chess from Piece.
 *
 * @author: Riccardo Modolo 2009667
 */

#include "../lib/Piece.h"
using namespace std;
class pedestrian : public piece {

	private:
		bool is_generic_valid(path _path, int _path_length) const {
			int vp_length = sizeof(valid_path)/sizeof(valid_path[0]);

			for(int i = 0; i < vp_length; i++)
				return (valid_path[i] == _path && _path_length == 1);

			return false;
		}
		bool is_eatable(chessboard b, path _path, int _path_length) const{
			return false;
		}

	public:
		pedestrian(set _side = set::Black) : piece(_side){
			valid_path[1] = path::Vertical;
		}

		//A valid Move for king is one space in any Direction
		bool is_valid_move(chessboard b, path _path, int _path_length) const {
			return (is_generic_valid(_path, _path_length) || is_eatable(b, _path, _path_length)); 
		}

};