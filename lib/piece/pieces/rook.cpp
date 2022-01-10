#include "../piece.h"

class rook : public piece {

	public:
		rook(set _set) : piece(_set) {
			alias = 'T';
			max_distance = 8;
			valid_path.push_back(path::Horizontal);
			valid_path.push_back(path::Vertical);
		}
	
};