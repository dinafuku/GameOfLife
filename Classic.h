#ifndef CLASSIC_H
#define CLASSIC_H

#include "BaseGame.h"

class Classic{
    friend class Process;
    public:
        Classic();                              // constructor
        Classic(bool **board, int h, int w);    // overloaded
        Classic(int h, int w, double p);        // overloaded
        ~Classic();                             // deconstructor

        void neighborChecker();                 // checks neighbors for classic mode
        void classicRun(int choice);            // runs classic mode

    private:
        BaseGame *game;                         // instance of basegame
};

#endif