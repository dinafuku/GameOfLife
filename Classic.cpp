#include "Classic.h"
#include <fstream>

Classic::Classic(){}

Classic::Classic(bool** board, int h, int w){
    game = new BaseGame(board, h, w);
}

Classic::Classic(int h, int w, double p){
    game = new BaseGame(h, w, p);
}

Classic::~Classic(){
    delete game;
}

void Classic::classicRun(int choice){
    int counter = 0;
    cout << endl;
    // checks if board is empty
    while(!game->checkEmpty() || counter == 0){
        // check if board is stable
        if(counter > 0 && game->checkStable()){
            cout << endl;
            cout << "Board is stable" << endl;
            break;
        } 
        // pauses
        if(choice == 1){
            usleep(500000);
        }
        // press enter
        else if(choice == 2){
            cin.get();
        }
        // update current board
        if(counter > 0){
            game->nextToCurrent();
        }
        cout << "Generation " << counter << endl;
        // print board and check neighbors
        game->printBoard();
        neighborChecker();
        //update current board
        counter++;
    }
    if(game->checkEmpty()){
        cout << endl;
        cout << "Board is empty" << endl;
    }
    // prompt to exit program
    cout << "Press enter to exit program..." << endl;;
    cin.get();
    if (choice != 2){
        cin.get();
    }
}

void Classic::neighborChecker(){
    int neighborCount;
    for(int i = 0; i < game->height; ++i){
        for(int j = 0; j < game->width; ++j){
            neighborCount = 0;
            bool current = game->currentBoard[i][j];
            // make cell check all 8 surrounding cells if applicable
            // above row neighbors
            if(i-1 >= 0){
                // above
                if(game->currentBoard[i-1][j] == 1){
                    neighborCount++;
                }
                if(j-1 >= 0){
                    // above left
                    if(game->currentBoard[i-1][j-1] == 1){
                        neighborCount++;
                    }
                }
                if(j+1 < game->width){
                    // above right
                    if(game->currentBoard[i-1][j+1] == 1){
                        neighborCount++;
                    }
                }
            }

            // same row neighbors
            if(j-1 >= 0){
                // left
                if(game->currentBoard[i][j-1] == 1){
                    neighborCount++;
                }
            }
            if(j+1 < game->width){
                // right
                if(game->currentBoard[i][j+1] == 1){
                    neighborCount++;
                }
            }

            // below row neighbors
            if(i+1 < game->height){
                // below
                if(game->currentBoard[i+1][j] == 1){
                    neighborCount++;
                }
                if(j-1 >= 0){
                    // below left
                    if(game->currentBoard[i+1][j-1] == 1){
                        neighborCount++;
                    }
                }
                if(j+1 < game->width){
                    // below right
                    if(game->currentBoard[i+1][j+1] == 1){
                        neighborCount++;
                    }
                }
            }
            
            // decide which cells live or die basd on neighborCount
            if(neighborCount <= 1 || neighborCount >= 4){
                game->nextBoard[i][j] = 0;
            }
            else if(neighborCount == 3 && current == 0){
                game->nextBoard[i][j] = 1;
            }
        }
    }
}