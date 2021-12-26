#include "../piece.h"

class pawn : public piece {

	public:
		pawn(set _set) : piece(_set) {
			alias = 'P';
			valid_path.push_back(path::Vertical);
		}

		bool is_legit_move(path _path, int distance) const {

			int side_multiplier = 0;

			if(side == set::Black) side_multiplier = -1;
			else if(side == set::White) side_multiplier = 1;

			for(int i = 0; i < valid_path.size(); i++) {
				bool normal_condition = (valid_path[i] == _path && distance == (1*side_multiplier));
				bool first_condition = (valid_path[i] == _path && distance == (2*side_multiplier) && is_first_move());

				if(normal_condition || first_condition) return true;
			}

			return false;
		}

};