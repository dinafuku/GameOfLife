#include "BaseGame.h"
#include <stdlib.h>
#include <time.h>

BaseGame::BaseGame(){}

BaseGame::BaseGame(bool **board, int h, int w){
    // sets variables, created board (pointer to pointer), and copies input board to current and next boards
    height = h;
    width = w;
    currentBoard = new bool*[height];
    nextBoard = new bool*[height];
    for(int i = 0; i < height; ++i){
        currentBoard[i] = new bool[width];
        nextBoard[i] = new bool[width];
    }
    copyInput(board);
}

BaseGame::BaseGame(int h, int w, double p){
    // sets variables, creates board (point to pointer), and generates random board
    height = h;
    width = w;
    population = p;
    currentBoard = new bool*[height];
    nextBoard = new bool*[height];
    for(int i = 0; i < height; ++i){
        currentBoard[i] = new bool[width];
        nextBoard[i] = new bool[width];
    }
    generateRandomBoard();
}

BaseGame::~BaseGame(){
    for(int i = 0; i < height; ++i){
        delete[] currentBoard[i];
        delete[] nextBoard[i];
    }
    delete[] currentBoard;
    delete[] nextBoard;
}

bool** BaseGame::getBoard(){
    return currentBoard;
}

void BaseGame::copyInput(bool **board){
    // copies board
    for(int i = 0; i < height; ++i){
        for(int j = 0; j < width; ++j){
            currentBoard[i][j] = board[i][j];
            nextBoard[i][j] = board[i][j];
        }
    }
}

void BaseGame::currentToNext(){
    // copies board from current to next
    for(int i = 0; i < height; ++i){
        for(int j = 0; j < width; ++j){
            nextBoard[i][j] = currentBoard[i][j];
        }
    }
}

void BaseGame::generateRandomBoard(){
    int random = 0; // number between 1 and 10
    int totalCells = height * width;
    int cellsToOccupy = totalCells * population; // gets number of cells to occupy
    int occupyCell = population * 100; // get number between 0 - 100, use for randomness factor
    int occupied = 0;
    srand(time(NULL));

    while(occupied != cellsToOccupy){
        // randomize filling of cells
        for(int i = 0; i < height; ++i){
            if(occupied == cellsToOccupy){
                break;
            }
            for(int j = 0; j < width; ++j){
                // number between 1 and 100
                random = rand() % 100 + 1;
                // if the current cell is unoccupied
                if(currentBoard[i][j] == 0){
                    if(random <= occupyCell){
                    // mark cell as occupied, bool is set to 1
                    currentBoard[i][j] = 1;
                    occupied++;
                    }
                }
                if(occupied == cellsToOccupy){
                    break;
                }
            }
        }
    }
    currentToNext();
}

void BaseGame::printBoard(){
    // prints board
    for(int i = 0; i < height; ++i){
        for(int j = 0; j < width; ++j){
            if(currentBoard[i][j] == 1){
                cout << 'X';
            }
            else{
                cout << '-';
            }
        }
        cout << endl;
    }
}

void BaseGame::nextToCurrent(){
    // copies next board to current board
    for(int i = 0; i < height; ++i){
        for(int j = 0; j < width; ++j){
            currentBoard[i][j] = nextBoard[i][j];
        }
    }
}

bool BaseGame::checkStable(){
    // checks if board is stable
    for(int i = 0; i < height; ++i){
        for(int j = 0; j < width; ++j){
            if(currentBoard[i][j] != nextBoard[i][j]){
                return false;
            }
        }
    }
    return true;
}

bool BaseGame::checkEmpty(){
    // check if board is empty
    for(int i = 0; i < height; ++i){
        for(int j = 0; j < width; ++j){
            if(currentBoard[i][j] == 1){
                return false;
            }
        }
    }
    return true;
}