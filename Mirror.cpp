#include "Mirror.h"

Mirror::Mirror(){}

Mirror::Mirror(bool **board, int h, int w){
    game = new BaseGame(board, h, w);
}

Mirror::Mirror(int l, int w, double p){
    game = new BaseGame(l, w, p);
}

Mirror::~Mirror(){
    delete game;
}

void Mirror::mirrorRun(int choice){
    int counter = 0;
    cout << endl;
    // checks if board is empty
    while(!game->checkEmpty() || counter == 0){
        // check if board is stable, if so, exit
        if(counter > 0 && game->checkStable()){
            cout << endl;
            cout << "Board is stable" << endl;
            break;
        } 
        // pauses
        if(choice == 1){
            usleep(500000);
        }
        // user presses enter
        else if(choice == 2){
            cin.get();
        }
        // update current board
        if(counter > 0){
            game->nextToCurrent();
        }
        cout << "Generation " << counter << endl;
        // print board and check neighbors with mirror mode
        game->printBoard();
        neighborChecker();
        //update current board
        counter++;
    }
    if(game->checkEmpty()){
        cout << endl;
        cout << "Board is empty" << endl;
    }
    cout << "Press enter to exit program..." << endl;;
    cin.get();
    if (choice != 2){
        cin.get();
    }
}

void Mirror::neighborChecker(){
    int neighborCount;
    bool current;
    if(game->height == 1|| game->width == 1){
        for(int i = 0; i < game->height; ++i){
            for(int j = 0; j < game->width; ++j){
                neighborCount = 0;
                if(game->currentBoard[i][j] == 1){
                    neighborCount += 2;
                }
                // row
                if(i-1 < 0 && i+1 == game->height){
                    // left side || right side
                    if(j-1 < 0 || j+1 == game->width){    
                        neighborCount += 5;
                    }
                    else{
                        // left
                        if(game->currentBoard[i][j-1] == 1){
                            neighborCount += 3;
                        }
                        // right
                        if(game->currentBoard[i][j+1] == 1){
                            neighborCount += 3;
                        }
                    }
                }
                // column
                if(j-1 < 0 && j+1 == game->width){
                    // left side || right side
                    if(i-1 < 0 || i+1 == game->height){    
                        neighborCount += 5;
                    }
                    else{
                        // above
                        if(game->currentBoard[i-1][j] == 1){
                            neighborCount += 3;
                        }
                        // below
                        if(game->currentBoard[i+1][j] == 1){
                            neighborCount += 3;
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
    else{
        for(int i = 0; i < game->height; ++i){
            for(int j = 0; j < game->width; ++j){
                neighborCount = 0;
                current = game->currentBoard[i][j];
                // if current cell is a corner
                // top left corner
                if(i-1 < 0 && j-1 < 0){
                    if(current == 1){
                        neighborCount += 3;
                    }
                    // right
                    if(game->currentBoard[i][j+1] == 1){
                        neighborCount += 2;
                    }
                    // below
                    if(game->currentBoard[i+1][j] == 1){
                        neighborCount += 2;
                    }
                    // bottom right
                    if(game->currentBoard[i+1][j+1] == 1){
                        neighborCount++;
                    }
                }
                // top right corner
                else if(i-1 < 0 && j+1 == game->width){
                    if(current == 1){
                        neighborCount += 3;
                    }
                    // left
                    if(game->currentBoard[i][j-1] == 1){
                        neighborCount += 2;
                    }
                    // below
                    if(game->currentBoard[i+1][j] == 1){
                        neighborCount += 2;
                    }
                    // bottom left
                    if(game->currentBoard[i+1][j-1] == 1){
                        neighborCount++;
                    }
                }
                // bottom left corner
                else if(i+1 == game->height && j-1 < 0){
                    if(current == 1){
                        neighborCount += 3;
                    }
                    // above
                    if(game->currentBoard[i-1][j] == 1){
                        neighborCount += 2;
                    }
                    // right
                    if(game->currentBoard[i][j+1] == 1){
                        neighborCount += 2;
                    }
                    // top right
                    if(game->currentBoard[i-1][j+1] == 1){
                        neighborCount++;
                    }
                }
                // bottom right corner
                else if(i+1 == game->height && j+1 == game->width){
                    if(current == 1){
                        neighborCount += 3;
                    }
                    // left
                    if(game->currentBoard[i][j-1] == 1){
                        neighborCount += 2;
                    }
                    // above
                    if(game->currentBoard[i-1][j] == 1){
                        neighborCount += 2;
                    }
                    // top left
                    if(game->currentBoard[i-1][j-1] == 1){
                        neighborCount++;
                    }
                }
                // top edge
                else if(i-1 < 0){
                    if(current == 1){
                        neighborCount++;
                    }
                    // left
                    if(game->currentBoard[i][j-1] == 1){
                        neighborCount += 2;
                    }
                    // right
                    if(game->currentBoard[i][j+1] == 1){
                        neighborCount += 2;
                    }
                    // bottom
                    if(game->currentBoard[i+1][j] == 1){
                        neighborCount++;
                    }
                    // diagonal bottom left
                    if(game->currentBoard[i+1][j-1] == 1){
                        neighborCount++;
                    }
                    // diagonal bottom right
                    if(game->currentBoard[i+1][j+1] == 1){
                        neighborCount++;
                    }
                }
                // bottom edge
                else if(i+1 == game->height){
                    if(current == 1){
                        neighborCount++;
                    }
                    // left
                    if(game->currentBoard[i][j-1]){
                        neighborCount += 2;
                    }
                    // right
                    if(game->currentBoard[i][j+1]){
                        neighborCount += 2;
                    }
                    // top
                    if(game->currentBoard[i-1][j]){
                        neighborCount++;
                    }
                    // diagonal top left
                    if(game->currentBoard[i-1][j-1]){
                        neighborCount++;
                    }
                    // diagonal top right
                    if(game->currentBoard[i-1][j+1]){
                        neighborCount++;
                    }
                }
                // left edge
                else if(j-1 < 0){
                    if(current == 1){
                        neighborCount++;
                    }
                    // top
                    if(game->currentBoard[i-1][j]){
                        neighborCount += 2;
                    }
                    // bottom
                    if(game->currentBoard[i+1][j]){
                        neighborCount += 2;
                    }
                    // right
                    if(game->currentBoard[i][j+1]){
                        neighborCount++;
                    }
                    // diagonal top right
                    if(game->currentBoard[i-1][j+1]){
                        neighborCount++;
                    }
                    // diagonal bottom right
                    if(game->currentBoard[i+1][j+1]){
                        neighborCount++;
                    }
                }
                // right edge
                else if(j+1 == game->width){
                    if(current == 1){
                        neighborCount++;
                    }
                    // top
                    if(game->currentBoard[i-1][j]){
                        neighborCount += 2;
                    }
                    // bottom
                    if(game->currentBoard[i+1][j]){
                        neighborCount += 2;
                    }
                    // left
                    if(game->currentBoard[i][j-1]){
                        neighborCount++;
                    }
                    // diagonal top left
                    if(game->currentBoard[i-1][j-1]){
                        neighborCount++;
                    }
                    // diagonal bottom left
                    if(game->currentBoard[i+1][j-1]){
                        neighborCount++;
                    }
                }
                // not on edge
                else{
                    // top
                    if(game->currentBoard[i-1][j]){
                        neighborCount++;
                    }
                    // bottom
                    if(game->currentBoard[i+1][j]){
                        neighborCount++;
                    }
                    // left
                    if(game->currentBoard[i][j-1]){
                        neighborCount++;
                    }
                    // right
                    if(game->currentBoard[i][j+1]){
                        neighborCount++;
                    }
                    // diagonal top left
                    if(game->currentBoard[i-1][j-1]){
                        neighborCount++;
                    }
                    // diagonal top right
                    if(game->currentBoard[i-1][j+1]){
                        neighborCount++;
                    }
                    // diagonal bottom left
                    if(game->currentBoard[i+1][j-1]){
                        neighborCount++;
                    }
                    // diagonal bottom right
                    if(game->currentBoard[i+1][j+1]){
                        neighborCount++;
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
}