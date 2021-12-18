/*
 * Object describing pedestrian piece of chess from Piece.
 * @author: Riccardo Modolo 2009667
 */

#include "../lib/Piece.h"
class pedestrian : public piece {

	private:
		bool first_move;

	public:
		pedestrian(set _side = set::Black) : first_move { true } { side = _side; }

		//A valid Move for king is one space in any Direction
		bool is_valid_move(const board b, const std::pair<char, int> &cur, const std::pair<char, int> &aim) const {

			if(b.is_occupied(aim))

			int rowDistance = cur.first - aim.first;
			int colDistance = cur.second - aim.second;

			return (std::abs(rowDistance) == 1 && colDistance == 0);

		}
		void moved() { first_move = false; }

};