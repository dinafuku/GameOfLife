#ifndef SIMULATION_H
#define SIMULATION_H

#include "Process.h"

#include<exception>
using namespace std;

class Simulation{
    public:
        Simulation();               // constructor
        ~Simulation();              // deconstructor
        void simulate();            // runs simulation, runs generations
        int checkInputCorrect(string input, int isDensity);   // make sure user input is correct
};

#endif