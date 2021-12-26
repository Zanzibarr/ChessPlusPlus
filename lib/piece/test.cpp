#include <iostream>
#include "piece.cpp"
#include "pieces/king.cpp"
#include "pieces/queen.cpp"
#include "pieces/tower.cpp"
#include "pieces/pawn.cpp"
#include "pieces/bishop.cpp"
#include "pieces/horse.cpp"
using namespace std;

void printPiece(piece *p, path _path, int l) {

	cout<<p->get_alias()<<"\n";

	if(p->is_legit_move(_path, l)) cout<<"LEGIT MOVE\n";
	else { cout<<"NO NO NO son of a bitchhh\n"; }
	cout<<"******************************\n";
}

int main (void) {

	piece *p = new king(set::Black);
	piece *p1 = new queen(set::White);
	piece *p2 = new tower(set::Black);
	piece *p3 = new pawn(set::White);
	piece *p4 = new bishop(set::Black);
	piece *p5 = new horse(set::White);

	printPiece(p, path::Vertical, 5);
	printPiece(p1, path::Vertical, 5);
	printPiece(p2, path::Diagonal, 1);
	printPiece(p3, path::Vertical, 2);
	printPiece(p4, path::Diagonal, 3);
	printPiece(p5, path::L, 4);

	return 0;
}