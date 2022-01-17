#include "../piece.h"

class empty_tile : public piece {

	public:
		empty_tile(set _set = set::Empty) : piece(_set) {
			alias = ' ';
			max_distance = 0;
		}
		~empty_tile() {
			valid_path.clear();
		}

};