#ifndef PIECE_H
#define PIECE_H

/*
 * Interface describing geric piece of chess.
 * @author: Riccardo Modolo 2009667
 */

#include <utility>
#include "board.h"
class piece {

	protected:
		enum class set {White, Black};
        //Fazione del pezzo
		set side;

	public:

        /*
         * Funzione virtuale da implementare nelle rispettive sottoclassi per controllare se una mossa è legale
         * 
         * @param b : board to view for special condition
         * @param cur_row cur_col : Le coordinate iniziali del pezzo
         * @param row col : Le coordinate finali del pezzo
         */
		virtual bool is_valid_move(const board b, const std::pair<char, int> &_cur, const std::pair<char, int> &_aim) const = 0;
		
};

#endif