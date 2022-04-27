#ifndef DOUGHNUT_H
#define DOUGHNUT_H

#include "BaseGame.h"

class Doughnut{
    friend class Process;
    public:
        Doughnut();                                 // constructor
        Doughnut(bool **board, int h, int w);       // overloaded
        Doughnut(int h, int w, double p);           // overloaded
        ~Doughnut();                                // deconstructor

        void neighborChecker();                     // checks neighbors for doughnut mode (wrap)
        void doughnutRun(int choice);               // runs doughnut mode
    private:
        BaseGame *game;                             // instance of base game
};

#endif