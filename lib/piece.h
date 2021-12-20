#ifndef PIECE_H
#define PIECE_H

/*
 * Interface describing geric piece of chess.
 * @author: Riccardo Modolo 2009667
 */

#include <stdlib.h>
#include "chessboard.h"
#include "detail.h"
class piece {

	protected:
                set side; //Fazione del pezzo
                path valid_path[3]; //max length (diagonal, vertical, Horizontal)

	public:

                piece(set _side  = set::Black); 
        /*
         * Funzione virtuale da implementare nelle rispettive sottoclassi per controllare se una mossa è legale
         * 
         * @param b : board to view for special condition
         * @param cur_row cur_col : Le coordinate iniziali del pezzo
         * @param row col : Le coordinate finali del pezzo
         */
		virtual bool is_valid_move(path _path, int _path_length) const = 0;
                virtual set get_side() const = 0;
		
};

#endif