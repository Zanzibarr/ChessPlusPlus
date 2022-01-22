#ifndef PIECES_H
#define PIECES_H

#include "piece.h"

/**
 * 
 * @file pieces.h
 * @author Riccardo Modolo (riccardo.modolo.1@studenti.unipd.it)
 * 
 * @brief The interface consists in creation of specific pieces. 
 * 
 * @version 0.4
 * @date 2022-01-15
 * 
 */

//empty tile is not a real piece but just a white space non movable
class empty_tile : public piece {
	public:
		empty_tile();
		//use the default version of is_legit_move in piece
};

//the bishop can move only diagonally without distance limit (max distance: 8)
class bishop : public piece {
	public:
		bishop(set side);
		//use the default version of is_legit_move in piece
};

//the queen, most powerful piece, can move diagonally, vertically and horizontally without distance limit (max distance: 8)
class queen : public piece {
	public:
		queen(set side);
		//use the default version of is_legit_move in piece
};

//the king can move diagonally, vertically and horizontally only in range of 1 tile (max distance: 1)
class king : public piece {
	public:
		king(set side);
		//use the default version of is_legit_move in piece
};

//the rook can move vertically and horizontally without distance limit (max distance: 8)
class rook : public piece {
	public:
		rook(set side);
		//use the default version of is_legit_move in piece
};

//the knight can move only in L path with rigid range of 3 tiles (only valid distance: 3)
class knight : public piece {
	public:
		knight(set side);

		//particular case: is legit when distance is exactly 3 (not <= 3)
		virtual bool is_legit_move(path _path, int distance) const;
};

//the pawn can move only in vertical (except the eating condition) in a range of 1 tile exept for first move(2 tiles) in only one direction
class pawn : public piece {
	public:
		pawn(set side);

		//particular case: legit move depends by the side of pawn
		virtual bool is_legit_move(path _path, int  distance) const;
};

#endif