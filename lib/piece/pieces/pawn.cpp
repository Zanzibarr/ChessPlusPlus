#include "../piece.h"

class pawn : public piece {

	public:
		pawn(set _set) : piece(_set) {
			alias = 'P';
			max_distance = 1;
			valid_path.push_back(path::Vertical);
		}

		bool is_legit_move(path _path, int _distance) const {

			int side_multiplier = 0;

			if(side == set::Black) side_multiplier = -1;
			else if(side == set::White) side_multiplier = 1;

			bool normal_condition = (valid_path[0] == _path && _distance == (side_multiplier));
			bool first_condition = (valid_path[0] == _path && _distance == (2*side_multiplier) && first_move);

			return normal_condition || first_condition;
			
		}

};