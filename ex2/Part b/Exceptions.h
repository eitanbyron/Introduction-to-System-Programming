//
// Created by BBIRONN on 15/06/2021.
//

#ifndef SNIPER_CPP_EXCEPTION_H
#define SNIPER_CPP_EXCEPTION_H

namespace mtm {

class Exceptions: public std::exception{};

class IllegalArgument: public Exceptions{
public:
        const char *what() const noexcept override{
            return "A game related error has occurred: IllegalArgument";
        }
    };
    class IllegalCell: public Exceptions{
    public:
        const char *what() const noexcept override {
            return "A game related error has occurred: IllegalCell";
        }
    };
    class CellEmpty: public Exceptions{
    public:
        const char *what() const noexcept override {
            return "A game related error has occurred: CellEmpty";
        }
    };
    class MoveTooFar: public Exceptions{
    public:
        const char *what() const noexcept override {
            return "A game related error has occurred: MoveTooFar";
        }
    };
    class CellOccupied: public Exceptions{
    public:
        const char *what() const noexcept override {
            return "A game related error has occurred: CellOccupied";
        }
    };
    class OutOfRange: public Exceptions{
    public:
        const char *what() const noexcept override {
            return "A game related error has occurred: OutOfRange";
        }
    };
    class OutOfAmmo: public Exceptions{
    public:
            const char *what() const noexcept override {
            return "A game related error has occurred: OutOfAmmo";
        }
    };
    class IllegalTarget: public Exceptions{
    public:
        const char *what() const noexcept override {
            return "A game related error has occurred: IllegalTarget";
        }
    };

}


#endif //SNIPER_CPP_EXCEPTION_H
