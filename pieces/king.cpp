/*
 * Object describing King piece of chess from Piece.
 * @author: Riccardo Modolo 2009667
 */

#include "../lib/piece.h"

class king : public piece {

	private:
		bool first_move;

		bool legal_move(const std::pair<char, int> &cur, const std::pair<char, int> &aim) const {

			int rowDistance = cur.first - aim.first;
			int colDistance = cur.second - aim.second;

			return (std::abs(rowDistance) == 1 && std::abs(colDistance) == 1);

		}

	public:
		king(set _side = set::Black) : first_move { true } { side = _side; }

		//A valid Move for king is one space in any Direction
		bool is_valid_move(const board b, const std::pair<char, int> &cur, const std::pair<char, int> &aim) const {

			if (b.is_reachable(side, aim)) return false;

			bool valid = false;
			valid |= legal_move(cur, aim);
			valid |= 

		}
		void moved() { first_move = false; }

};