#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <iostream>
#include <string>

class illegal_move_exception {
    public:
        std::string message {"[ILLEGAL MOVE EXCEPTION]"};
        illegal_move_exception(std::string message_ = "") { what(message_); }
        void what(std::string message_) {
            message += ": " + message_ + "\n";
            std::cout << message;
        }
};

class out_of_bounds_exception {
    public:
        std::string message {"[OUT OF BOUNDS EXCEPTION]"};
        out_of_bounds_exception(std::string message_ = "") { what(message_); }
        void what(std::string message_) {
            message += ": " + message_ + "\n";
            std::cout << message;
        }
};

#endif