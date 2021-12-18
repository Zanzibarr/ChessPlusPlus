#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "piece.h"

class player {

	private:
    //Nome del giocatore
		std::string name;

    public:
        /*
         *Funzione virtuale da implementare nelle rispettive sottoclassi per muovere una pedina
         */
        virtual void make_move(const std::pair<char, int> &_cur, const std::pair<char, int> &_aim) const = 0;

};

#endif