#ifndef PIECES_H
#define PIECES_H

#include "piece.h"

class empty_tile : public piece {
	public:
		empty_tile();
		//use the default version of is_legit_move in piece
};

class bishop : public piece {
	public:
		bishop(set side);
		//use the default version of is_legit_move in piece
};

class queen : public piece {
	public:
		queen(set side);
		//use the default version of is_legit_move in piece
};

class king : public piece {
	public:
		king(set side);
		//use the default version of is_legit_move in piece
};

class rook : public piece {
	public:
		rook(set side);
		//use the default version of is_legit_move in piece
};

class knight : public piece {
	public:
		knight(set side);

		//particular case: is legit when distance is exactly 3 (not <= 3)
		virtual bool is_legit_move(path _path, int distance) const;
};

class pawn : public piece {
	public:
		pawn(set side);

		//particular case: legit move depends by the side of pawn
		virtual bool is_legit_move(path _path, int  distance) const;
};

#endif