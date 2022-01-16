#include "chessboard.cpp"
#include <regex>
#include <iostream>
#include <string>
#include <stdlib.h>

#define LETTERA 'A'

//coordinate converter
std::pair<char, int> matrix_to_chess(std::pair<int,int> matrix_coords) {

	char letter = matrix_coords.second + 'A';
	int number = matrix_coords.first + 1;

	return std::pair<char,int>{letter, number};
};

int main(void) {

    chessboard scacchiera{};

    std::vector<std::string> names {"Colla", "Riccardo"};
    std::vector<set> turn {set::White, set::Black};
    int counter = 0;
			
    std::regex reg1("^([A-H]){1}([1-8]){1} ([A-H]){1}([1-8]){1}$");
    std::smatch match;

    int tries = 0;
    int bot_average = 0;
    int rounds = 0;

    std::cout << scacchiera;

    std::vector<coords> pc;

    while (true) {

        //if (rounds > 100) break;

        bool failed;

        failed = true;

        while(failed) {

            std::cout << std::endl << names[counter] + " inserisci una mossa: ";
            std::string input;
			std::getline(std::cin, input);

            if (input.compare("XX XX") == 0) {
                std::cout << scacchiera;
                continue;
            }

            coords start;
            coords target;

            if (std::regex_search(input, match, reg1) && match.size() >=5) {

                //coordinate iniziali
                start.first = std::stoi(match.str(2)) -1;
                start.second =  match.str(1)[0] - LETTERA;

                //coordinate finali					
                target.first = std::stoi(match.str(4)) -1;
                target.second =  match.str(3)[0] - LETTERA;

            }

            std::pair<bool, bool> result;

            try {
                result = scacchiera.move(turn[counter], start, target);
            } catch (illegal_move_exception) { continue; }

            if (result.first && result.second) {

                std::cout << scacchiera;
                std::cout << "Scacco matto!";
                goto exit;

            } else if(result.first && !result.second) {

                std::cout << scacchiera;
                std::cout << "Patta!";
                goto exit;

            } else
                failed = (!result.first && !result.second);

            if (!failed) {

                std::cout << "Mossa a buon fine";

                if (scacchiera.is_promotion(target)) {

                    char piece;
                    bool exit_cond = false;

                    while(!exit_cond) {

                        std::cout << std::endl << "\nSelect the piece you wish to have your pawn promoted to: 't', 'c', 'a', 'd': ";
                        std::string in;
                        std::cin >> in;
                        piece = std::tolower(in[0]);

                        exit_cond = piece == 'a' || piece == 'c' || piece == 'd' || piece == 't';
                    
                    }

                    scacchiera.do_promotion(target, piece);

                }
                //scacchiera.print();
                counter = (counter + 1)%2;
            }

        }

        failed = true;
        tries = 0;

        pc = scacchiera.get_pieces(turn[counter]);
        std::vector<std::pair<coords, coords>> all_moves;

        for (int i = 0; i < pc.size(); i++) {
            std::vector<coords> mv = scacchiera.get_moves(pc.at(i), true);
            for (int j = 0; j < mv.size(); j++) all_moves.push_back(std::make_pair(pc.at(i), mv.at(j)));
        }

        while(failed) {

            tries++;

            std::srand(time(0));
            int rand_index = std::rand()%all_moves.size();

            coords start = all_moves.at(rand_index).first;
            coords target = all_moves.at(rand_index).second;

            std::pair<bool, bool> result;

            try {
                result = scacchiera.move(turn[counter], start, target);
            } catch (illegal_move_exception) {
                all_moves.erase(all_moves.begin() + rand_index);
                continue;
            }

            if (result.first && result.second) {

                std::cout << scacchiera;
                std::cout << "Scacco matto!";
                goto exit;

            } else if(result.first && !result.second) {

                std::cout << scacchiera;
                std::cout << "Patta!";
                goto exit;

            } else
                failed = (!result.first && !result.second);

            if (!failed) {
                std::pair<char, int> coords_s = matrix_to_chess(start);
                std::pair<char, int> coords_f = matrix_to_chess(target);
                std::cout << "\nTentativo n. " << tries << " del bot " << counter << ": ";
                std::cout << coords_s.first << ";" << coords_s.second << " -> " << coords_f.first << ";" << coords_f.second;

                if (scacchiera.is_promotion(target)) {

                    std::vector<char> pieces{'t', 'c', 'a', 'd'};

                    std::srand(time(0));
                    char piece = pieces.at(std::rand()%4);

                    scacchiera.do_promotion(target, piece);

                }

                std::cout << scacchiera;

                counter = ( counter + 1) % 2;
                bot_average += tries;
                rounds++;
            } else
                all_moves.erase(all_moves.begin() + rand_index);

        }

        /*
        std::string wait;
        std::cin >> wait;
        std::cin.ignore();
        */

    }

    exit:

    std::cout << (double)bot_average / rounds << " average tries per move.";

}
