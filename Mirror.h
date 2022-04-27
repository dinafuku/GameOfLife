#ifndef MIRROR_H
#define MIRROR_H

#include "BaseGame.h"

class Mirror{
    friend class Process;
    public:
        Mirror();                                   // constructor
        Mirror(bool **board, int h, int w);         // overloaded
        Mirror(int h, int w, double p);             // overloaded
        ~Mirror();                                  // deconstructor

        void neighborChecker();                     // checks neighbor with mirror mode
        void mirrorRun(int choice);                 // runs game based on mirror mode

    private:
        BaseGame *game;                             // instance of base game

};

#endif