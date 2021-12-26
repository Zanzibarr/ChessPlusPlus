#include "../piece.h"

class bishop : public piece {

	public:
		bishop(set _set) : piece(_set) {
			alias = 'A';

			valid_path.push_back(path::Diagonal);
		}
};