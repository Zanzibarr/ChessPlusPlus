#include "../piece.h"

class tower : public piece {

	public:
		tower(set _set) : piece(_set) {
			alias = 'T';

			valid_path.push_back(path::Horizontal);
			valid_path.push_back(path::Vertical);
		}
};