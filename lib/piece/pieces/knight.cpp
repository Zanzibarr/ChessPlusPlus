#include "../piece.h"

class knight : public piece {

	public:
		knight(set _set) : piece(_set) {
			alias = 'C';
			max_distance = 3;
			valid_path.push_back(path::L);
		}
		
		bool is_legit_move(path _path, int _distance) const {

			int distance = std::abs(_distance);

			for(int i = 0; i < valid_path.size(); i++) {
				if(valid_path[i] == _path && distance == 3) return true;
			}

			return false;
		}

};