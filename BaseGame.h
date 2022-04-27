#ifndef BASEGAME_H
#define BASEGAME_H

#include <iostream>
#include <unistd.h>
using namespace std;

class BaseGame{
    // allow access to private member variables to these classes
    friend class Classic;
    friend class Doughnut;
    friend class Mirror;
    friend class Process;

    public:
        BaseGame();                                 // constructor
        BaseGame(bool** board, int h, int w);       // overloaded
        BaseGame(int h, int w, double p);           // overloaded
        ~BaseGame();                                // destructor

        void generateRandomBoard();                 // creates board
        void currentToNext();                       // copies current board to next board
        void copyInput(bool** board);               // copies given board to next and current boards
        void printBoard();                          // prints board
        void nextToCurrent();                       // copies next to current board
        bool** getBoard();                          // gets board
        bool checkStable();                         // checks if board is stable
        bool checkEmpty();                          // check if board is empty
 
    private:
        int height;                                 // height of board
        int width;                                  // width of board
        double population;                          // density of board
        bool **currentBoard;                        // current board generation
        bool **nextBoard;                           // updated board generation
};

#endif