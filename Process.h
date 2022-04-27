#ifndef PROCESS_H
#define PROCESS_H

#include "BaseGame.h"
#include "Classic.h"
#include "Doughnut.h"
#include "Mirror.h"
#include<fstream>
using namespace std;

class Process{
    public:
        Process();                                                      // constructor
        ~Process();                                                     // deconstructor
        bool** fileProcess(string input);                               // file processing given input file
        void outputToFile(Classic *classic, string output);             // output classic mode to file
        void outputToFile(Doughnut *doughnut, string output);           // output doughnut mode to file
        void outputToFile(Mirror *mirror, string output);               // output mirror mode to file
        int getHeight();                                                // returns height of board
        int getWidth();                                                 // returns width of board
        
    private:
        int height;                                                     // height
        int width;                                                      // width
        bool **board;                                                   // board
};

#endif