#include "../piece.h"

class queen : public piece {

	public:
		queen(set _set) : piece(_set) {
			alias = 'D';
			max_distance = 8;
			valid_path.push_back(path::Vertical);
			valid_path.push_back(path::Horizontal);
			valid_path.push_back(path::Diagonal);
		}

};