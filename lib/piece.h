#ifndef PIECE_H
#define PIECE_H

/*
 * Interface describing geric piece of chess.
 * @author: Riccardo Modolo 2009667
 */

#include <utility>
#include "board.h"
#include "set.h"

class piece {

	protected:
                set side; //Fazione del pezzo
                char alias; //the letter represent piece (R for Re ecc...)
                path valid_path[3]; //max length (diagonal, vertical, Horizontal)

	public:

<<<<<<< HEAD
        /*
         * Funzione virtuale da implementare nelle rispettive sottoclassi per controllare se una mossa è legale
         * 
         * @param b : board to view for special condition
         * @param cur_row cur_col : Le coordinate iniziali del pezzo
         * @param row col : Le coordinate finali del pezzo
         */
		virtual bool is_valid_move(const std::pair<char, int> &_cur, const std::pair<char, int> &_aim) const = 0;
                virtual set get_side() const = 0;
                virtual char get_alias() const = 0;
=======
            /*
            * Funzione virtuale da implementare nelle rispettive sottoclassi per controllare se una mossa è legale
            * 
            * @param b : board to view for special condition
            * @param cur_row cur_col : Le coordinate iniziali del pezzo
            * @param row col : Le coordinate finali del pezzo
            */
            virtual bool is_valid_move(const std::pair<char, int> &_cur, const std::pair<char, int> &_aim) const = 0;
>>>>>>> a8f0646cb2204069851f1fa546089635bc01759a
		
};

#endif