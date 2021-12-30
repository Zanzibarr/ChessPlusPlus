#include "../piece.h"

class empty_tile : public piece {

	public:
		empty_tile() : piece(set::Empty) {
			alias = ' ';
			max_distance = 0;
		}

};