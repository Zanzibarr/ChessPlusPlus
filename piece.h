#ifndef PIECE_H
#define PIECE_H

/*
 * Interface describing geric piece of chess.
 * @author: Riccardo Modolo 2009667
 */

class Piece {

	protected:
		enum class side {Black, White};
		side currentSide; 
		bool firstMove;

	public:
		virtual bool isValidMove(char curLet, int curNum, char let, int num) const =0;
		virtual void moved() =0;
		
};

#endif //PIECE_H