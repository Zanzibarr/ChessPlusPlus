#include "../piece.h"

class bishop : public piece {

	public:
		bishop(set _set) : piece(_set) {
			alias = 'A';
			max_distance = 8;
			valid_path.push_back(path::Diagonal);
		}
		~bishop() {
			valid_path.clear();
		}

};