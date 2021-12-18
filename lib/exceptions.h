#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <iostream>
#include <string>

class illegal_move_exception {
    public:
        std::string message {"[ILLEGAL MOVE EXCEPTION]"};
        illegal_move_exception(std::string _message = "") { what(_message); }
        void what(std::string _message) {
            message += ": " + _message + "\n";
            std::cout << message;
        }
};

class out_of_bounds_exception {
    public:
        std::string message {"[OUT OF BOUNDS EXCEPTION]"};
        out_of_bounds_exception(std::string _message = "") { what(_message); }
        void what(std::string _message) {
            message += ": " + _message + "\n";
            std::cout << message;
        }
};

#endif