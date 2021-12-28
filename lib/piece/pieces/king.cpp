#include "../piece.h"

class king : public piece {

	public:
		king(set _set) : piece(_set) {
			alias = 'R';

			valid_path.push_back(path::Horizontal);
			valid_path.push_back(path::Vertical);
			valid_path.push_back(path::Diagonal);
		}

		bool is_legit_move(path _path, int distance) const {

			for(int i = 0; i < valid_path.size(); i++) {
				if(valid_path[i] == _path && distance == abs(1)) return true;
			}

			return false;
		}

};