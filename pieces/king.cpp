#include "../lib/Piece.h"

/*
 * Object describing King piece of chess from Piece.
 * @author: Riccardo Modolo 2009667
 */
class King : public piece {
 

	public:
		King(void) { side = set::Black; }
		King(side _side) { currentSide = _side; }
		~King(void) {}

		//A valid Move for king is one space in any Direction
		bool isValidMove(char let, int num) const { 
			int letDistance = let - coordinate.first;
			int numDistance = num - coordinate.second;

			return ((letDistance == 1 || letDistance == -1) && (numDistance == 1 || numDistance == -1));
		}
		void moved() { firstMove = false; }

};