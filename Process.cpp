#include "Process.h"
#include <exception>
#include <algorithm>

Process::Process(){
    height = 0;
    width = 0;
}
Process::~Process(){
    for(int i = 0; i < height; ++i){
        delete[] board[i];
    }
    delete[] board;
}

bool** Process::fileProcess(string input){
    ifstream inputFS;
    string fileData;
    // check for correct file path
    if(input.find(".txt") == string::npos){
        cout << endl;
        throw runtime_error("please provide absolute path (include file name)");
    }
    // open file
    inputFS.open(input);
    // if file isn't open
    if(!inputFS.is_open()){
        cout << endl;
        throw runtime_error("can't open input file or file doesn't exist in path, please provide correct file");
    }

    // convert string height and width to int and store
    getline(inputFS, fileData);
    height = stoi(fileData);
    getline(inputFS, fileData);
    width = stoi(fileData);

    // create a board to store file board in
    board = new bool*[height];
    for(int i = 0; i < height; ++i){
        board[i] = new bool[width];
    }

    // storing provided board into a 2d array
    // get board on the file by reading row by row, or line by line
    getline(inputFS, fileData);
    for(int i = 0; i < height; ++i){
        // if there are spaces in file, remove them from the lines
        remove(fileData.begin(), fileData.end(), ' ');
        // if the current char is an X set the cell to 1, else set to 0
        for(int j = 0; j < width; ++j){
            if(fileData.at(j) == 'X'){
                board[i][j] = 1;
            }
            else if(fileData.at(j) == '-'){
                board[i][j] = 0;
            }
        }
        // get row
        getline(inputFS, fileData);
    }

    // get weird blank lines after board
    while(!inputFS.eof()){
        getline(inputFS, fileData);
    }

    // if didn't reach end of file
    if(!inputFS.eof()){
        throw runtime_error("did not reach end of file");
    }

    // close file
    inputFS.close();

    return board;
}

void Process::outputToFile(Classic *classic, string output){
    ofstream outputFS;
    string row = "";
    // open file
    outputFS.open(output);
    // if file is opened
    if(!outputFS.is_open()){
        cout << endl;
        throw runtime_error("can't open file or file doesn't exist in path");
    }

    int counter = 0;
    // while board isn't empty
    while(!classic->game->checkEmpty()){
        outputFS << "Generation " << counter << endl;
        classic->game->nextToCurrent();
        // iterate through board, get by rows, output by rows to file
        for(int i = 0; i < classic->game->height; ++i){
            for(int j = 0; j < classic->game->width; ++j){
                if(classic->game->currentBoard[i][j] == 1){
                    row.push_back('X');
                }
                else{
                    row.push_back('-');
                }
            }
            outputFS << row << endl;
            row = "";
        }
        // check neighbors
        classic->neighborChecker();
        counter++;
        // check if board is stable
        if(classic->game->checkStable()){
            break;
        }
    }
    cout << "File processed" << endl;

    // close file
    outputFS.close();
}

void Process::outputToFile(Doughnut *doughnut, string output){
    ofstream outputFS;
    string row = "";
    // open file
    outputFS.open(output);
    // if file isn't open
    if(!outputFS.is_open()){
        cout << endl;
        throw runtime_error("can't open file or file doesn't exist in path");
    }

    int counter = 0;
    // while board isn't empty
    while(!doughnut->game->checkEmpty()){
        outputFS << "Generation " << counter << endl;
        doughnut->game->nextToCurrent();
        // iterate through board, get row, output row to file
        for(int i = 0; i < doughnut->game->height; ++i){
            for(int j = 0; j < doughnut->game->width; ++j){
                if(doughnut->game->currentBoard[i][j] == 1){
                    row.push_back('X');
                }
                else{
                    row.push_back('-');
                }
            }
            outputFS << row << endl;
            row = "";
        }
        // check neighbor
        doughnut->neighborChecker();
        counter++;
        // if board is stable
        if(doughnut->game->checkStable()){
            break;
        }
    }
    cout << "File processed" << endl;

    // close file
    outputFS.close();
}

void Process::outputToFile(Mirror *mirror, string output){
    ofstream outputFS;
    string row = "";
    // open file
    outputFS.open(output);
    // if file isn't open
    if(!outputFS.is_open()){
        cout << endl;
        throw runtime_error("can't open file or file doesn't exist in path");
    }

    int counter = 0;
    // while the board isnt empty
    while(!mirror->game->checkEmpty()){
        outputFS << "Generation " << counter << endl;
        // update board
        mirror->game->nextToCurrent();
        // based on board create string of X or -
        for(int i = 0; i < mirror->game->height; ++i){
            for(int j = 0; j < mirror->game->width; ++j){
                if(mirror->game->currentBoard[i][j] == 1){
                    row.push_back('X');
                }
                else{
                    row.push_back('-');
                }
            }
            // output row of X and - to file
            outputFS << row << endl;
            row = "";
        }
        // runs neighbor checkor
        mirror->neighborChecker();
        counter++;
        // check if board is stable
        if(mirror->game->checkStable()){
            break;
        }
    }
    cout << "File processed" << endl;

    // close file
    outputFS.close();
}

int Process::getHeight(){
    return height;
}

int Process::getWidth(){
    return width;
}