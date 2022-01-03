#include "../piece.h"

class king : public piece {

	public:
		king(set _set) : piece(_set) {
			alias = 'R';
			max_distance = 1;
			valid_path.push_back(path::Horizontal);
			valid_path.push_back(path::Vertical);
			valid_path.push_back(path::Diagonal);
		}

};