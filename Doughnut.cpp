#include "Doughnut.h"

Doughnut::Doughnut(){}

Doughnut::Doughnut(bool **board, int h, int w){
    game = new BaseGame(board, h, w);
}

Doughnut::Doughnut(int h, int w, double p){
    game = new BaseGame(h, w, p);
}

Doughnut::~Doughnut(){
    delete game;
}

void Doughnut::doughnutRun(int choice){
    int counter = 0;
    cout << endl;
    // while board is not empty
    while(!game->checkEmpty() || counter == 0){
        // check if game is stable, if so, exit
        if(counter > 0 && game->checkStable()){
            cout << endl;
            cout << "Board is stable" << endl;
            break;
        } 
        // pause
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
    cout << "Press enter to exit program..." << endl;;
    cin.get();
    if (choice != 2){
        cin.get();
    }
}

void Doughnut::neighborChecker(){
    int neighborCount;
    // 1 x 1 board
    if(game->height == 1 && game->width == 1){
        game->nextBoard[0][0] = 0;
    }
    // 1 x 2, 3 x 1, dimension 1 boards
    else if(game->height == 1 || game->width == 1){
        for(int i = 0; i < game->height; ++i){
            for(int j = 0; j < game->width; ++j){
                neighborCount = 0;
                // if cell occupied, 2 neighbors
                if(game->currentBoard[i][j] == 1){
                    neighborCount += 2;
                }
                // row
                if(i-1 < 0 && i+1 == game->height){
                    // left side || right side
                    if(j-1 < 0 || j+1 == game->width){
                        if(j-1 < 0){
                            // right
                            if(game->currentBoard[i][j+1] == 1){
                                neighborCount += 3;
                            }
                            // opposite end
                            if(game->currentBoard[i][game->width-1] == 1){
                                neighborCount += 3;
                            }
                        }
                        // right side
                        else if (j+1 == game->width){
                            // left
                            if(game->currentBoard[i][j-1] == 1){
                                neighborCount += 3;
                            }
                            // opposite end
                            if(game->currentBoard[i][0] == 1){
                                neighborCount += 3;
                            }
                        }
                    }
                    // in middle of row
                    else{
                        // check left
                        if(game->currentBoard[i][j-1] == 1){
                            neighborCount += 3;
                        }
                        // check right
                        if(game->currentBoard[i][j+1] == 1){
                            neighborCount += 3;
                        }
                    }
                }
                // column of 1 dimension
                else if(j-1 < 0 && j+1 == game->width){
                    // top
                    if(i-1 < 0){
                        // check below
                        if(game->currentBoard[i+1][j] == 1){
                            neighborCount += 3;
                        }
                        // check opposite
                        if(game->currentBoard[game->height-1][j] == 1){
                            neighborCount += 3;
                        }
                    }
                    // bottom
                    else if(i == game->height-1){
                        // check above
                        if(game->currentBoard[i-1][j] == 1){
                            neighborCount += 3;
                        }
                        // check opposite
                        if(game->currentBoard[0][j] == 1){
                            neighborCount += 3;
                        }
                    }
                    // between
                    else{
                        // check above
                        if(game->currentBoard[i-1][j] == 1){
                            neighborCount += 3;
                        }
                        // check below
                        if(game->currentBoard[i+1][j] == 1){
                            neighborCount += 3;
                        }
                    }
                } 
                // decide which cells live or die basd on neighborCount
                if(neighborCount <= 1 || neighborCount >= 4){
                    game->nextBoard[i][j] = 0;
                }
                else if(neighborCount == 3 && game->currentBoard[i][j] == 0){
                    game->nextBoard[i][j] = 1;
                }
            }
        }
    }
    else{
        for(int i = 0; i < game->height; ++i){
            for(int j = 0; j < game->width; ++j){
                neighborCount = 0;
                bool current = game->currentBoard[i][j];
                // make cell check all 8 surrounding cells
                // different cases 
                // corners
                if(i-1 < 0){
                    // top left corner
                    if(j-1 < 0){
                        // check bottom right corner
                        if(game->currentBoard[game->height-1][game->width-1] == 1){
                            neighborCount++;
                        }
                        // check opposite end right side
                        if(game->currentBoard[i][game->width-1] == 1){
                            neighborCount++;
                        } 
                        // check opposite end right side + 1
                        if(game->currentBoard[i+1][game->width-1] == 1){
                            neighborCount++;
                        }
                        // check opposite end bottom side
                        if(game->currentBoard[game->height-1][j] == 1){
                            neighborCount++;
                        } 
                        // check opposite end bottom side + 1
                        if(game->currentBoard[game->height-1][j+1] == 1){
                            neighborCount++;
                        }
                        // check directly right
                        if(game->currentBoard[i][j+1] == 1){
                            neighborCount++;
                        }
                        // check directly below
                        if(game->currentBoard[i+1][j] == 1){
                            neighborCount++;
                        }
                        // check directly diagonal bottom right
                        if(game->currentBoard[i+1][j+1] == 1){
                            neighborCount++;
                        }
                    }
                    // top right corner
                    else if(j+1 == game->width){
                        // check bottom left corner
                        if(game->currentBoard[game->height-1][0] == 1){
                            neighborCount++;
                        }
                        // check opposite end left side
                        if(game->currentBoard[i][0] == 1){
                            neighborCount++;
                        }
                        // check opposite end left side + 1
                        if(game->currentBoard[i+1][0] == 1){
                            neighborCount++;
                        }
                        // check opposite end bottom side
                        if(game->currentBoard[game->height-1][j] == 1){
                            neighborCount++;
                        }
                        // check opposite end bottom side - 1
                        if(game->currentBoard[game->height-1][j-1] == 1){
                            neighborCount++;
                        }
                        // check directly left
                        if(game->currentBoard[i][j-1] == 1){
                            neighborCount++;
                        }
                        // check directly below
                        if(game->currentBoard[i+1][j] == 1){
                            neighborCount++;
                        }
                        // check directly diagonal bottom left
                        if(game->currentBoard[i+1][j-1] == 1){
                            neighborCount++;
                        }
                    }
                    // cell is on top edge of board
                    else{
                        // check opposite end bottom - 1
                        if(game->currentBoard[game->height-1][j-1] == 1){
                            neighborCount++;
                        }
                        // check opposite end bottom
                        if(game->currentBoard[game->height-1][j] == 1){
                            neighborCount++;
                        }
                        // check opposite end bottom + 1
                        if(game->currentBoard[game->height-1][j+1] == 1){
                            neighborCount++;
                        }
                        // check directly left
                        if(game->currentBoard[i][j-1] == 1){
                            neighborCount++;
                        }
                        // check directly right
                        if(game->currentBoard[i][j+1] == 1){
                            neighborCount++;
                        }
                        // check directly below
                        if(game->currentBoard[i+1][j] == 1){
                            neighborCount++;
                        }
                        // check directly diagonal bottom left
                        if(game->currentBoard[i+1][j-1] == 1){
                            neighborCount++;
                        }
                        // check directly diagonal bottom right
                        if(game->currentBoard[i+1][j+1] == 1){
                            neighborCount++;
                        }
                    }
                }
                else if(i+1 == game->height){
                    // bottom left corner
                    if(j-1 < 0){
                        // check top right corner
                        if(game->currentBoard[0][game->width-1] == 1){
                            neighborCount++;
                        }
                        // check opposite end top side
                        if(game->currentBoard[0][j] == 1){
                            neighborCount++;
                        }
                        // check opposite end top side + 1
                        if(game->currentBoard[0][j+1] == 1){
                            neighborCount++;
                        }
                        // check opposite end right side
                        if(game->currentBoard[i][game->width-1] == 1){
                            neighborCount++;
                        }
                        // check opposite end right side - 1
                        if(game->currentBoard[i-1][game->width-1] == 1){
                            neighborCount++;
                        }
                        // check directly above
                        if(game->currentBoard[i-1][j] == 1){
                            neighborCount++;
                        }
                        // check directly right
                        if(game->currentBoard[i][j+1] == 1){
                            neighborCount++;
                        }
                        // check directly diagonal top right
                        if(game->currentBoard[i-1][j+1] == 1){
                            neighborCount++;
                        }
                    } 
                    // bottom right corner
                    else if(j+1 == game->width){
                        // check top left corner
                        if(game->currentBoard[0][0] == 1){
                            neighborCount++;
                        }
                        // check opposite end top
                        if(game->currentBoard[0][j] == 1){
                            neighborCount++;
                        }
                        // check opposite end top -1
                        if(game->currentBoard[0][j-1] == 1){
                            neighborCount++;
                        }
                        // check opposite end left 
                        if(game->currentBoard[i][0] == 1){
                            neighborCount++;
                        }
                        // check opposite enf left - 1
                        if(game->currentBoard[i-1][0] == 1){
                            neighborCount++;
                        }
                        // check directly above
                        if(game->currentBoard[i-1][j] == 1){
                            neighborCount++;
                        }
                        // check directly left
                        if(game->currentBoard[i][j-1] == 1){
                            neighborCount++;
                        }
                        // check directly diagonal top left
                        if(game->currentBoard[i-1][j-1] == 1){
                            neighborCount++;
                        }
                    }
                    // cell is on the bottom edge of the board but not a corner
                    else{
                        // check opposite end top - 1
                        if(game->currentBoard[0][j-1] == 1){
                            neighborCount++;
                        }
                        // check opposite end top
                        if(game->currentBoard[0][j] == 1){
                            neighborCount++;
                        }
                        // check opposite end top + 1
                        if(game->currentBoard[0][j+1] == 1){
                            neighborCount++;
                        }
                        // check directly left
                        if(game->currentBoard[i][j-1] == 1){
                            neighborCount++;
                        }
                        // check directly right
                        if(game->currentBoard[i][j+1] == 1){
                            neighborCount++;
                        }
                        // check directly above
                        if(game->currentBoard[i-1][j] == 1){
                            neighborCount++;
                        }
                        // check directly diagonal top left
                        if(game->currentBoard[i-1][j-1] == 1){
                            neighborCount++;
                        }
                        // check directly diagonal top right
                        if(game->currentBoard[i-1][j+1] == 1){
                            neighborCount++;
                        }
                    }
                }
                // cell on left edge
                else if(j-1 < 0){
                    // check oppsite end right side - 1
                    if(game->currentBoard[i-1][game->width-1] == 1){
                        neighborCount++;
                    }
                    // check opposite end right side 
                    if(game->currentBoard[i][game->width-1] == 1){
                        neighborCount++;
                    }
                    // check opposite end right side + 1
                    if(game->currentBoard[i+1][game->width-1] == 1){
                        neighborCount++;
                    }
                    // check directly above
                    if(game->currentBoard[i-1][j] == 1){
                        neighborCount++;
                    }
                    // check directly right
                    if(game->currentBoard[i][j+1] == 1){
                        neighborCount++;
                    }
                    // check directly directly below
                    if(game->currentBoard[i+1][j] == 1){
                        neighborCount++;
                    }
                    // check directly diagonal top right
                    if(game->currentBoard[i-1][j+1] == 1){
                        neighborCount++;
                    }
                    // check directly diagonal bottom right
                    if(game->currentBoard[i+1][j+1] == 1){
                        neighborCount++;
                    }
                }
                // cell on right edge
                else if(j+1 == game->width){
                    // check opposite end left side - 1
                    if(game->currentBoard[i-1][0] == 1){
                        neighborCount++;
                    }
                    // check opposite end left side
                    if(game->currentBoard[i][0] == 1){
                        neighborCount++;
                    }
                    // check opposite end left side + 1
                    if(game->currentBoard[i+1][0] == 1){
                        neighborCount++;
                    }
                    // check directly left
                    if(game->currentBoard[i][j-1] == 1){
                        neighborCount++;
                    }
                    // check directly above
                    if(game->currentBoard[i-1][j] == 1){
                        neighborCount++;
                    }
                    // check directly below
                    if(game->currentBoard[i+1][j] == 1){
                        neighborCount++;
                    }
                    // check directly diagonal top left
                    if(game->currentBoard[i-1][j-1] == 1){
                        neighborCount++;
                    }
                    // check directly diagonal bottom left
                    if(game->currentBoard[i+1][j-1] == 1){
                        neighborCount++;
                    }
                }
                // all neighbors adjacent on flat board, no need to wrap 
                else{
                    // check directly above
                    if(game->currentBoard[i-1][j] == 1){
                        neighborCount++;
                    }
                    // check directly below
                    if(game->currentBoard[i+1][j] == 1){
                        neighborCount++;
                    }
                    // check directly left
                    if(game->currentBoard[i][j-1] == 1){
                        neighborCount++;
                    }
                    // check directly right
                    if(game->currentBoard[i][j+1] == 1){
                        neighborCount++;
                    }
                    // check directly diagonal top left
                    if(game->currentBoard[i-1][j-1] == 1){
                        neighborCount++;
                    }
                    // check directly diagonal top right
                    if(game->currentBoard[i-1][j+1] == 1){
                        neighborCount++;
                    }
                    // check directly diagonal bottom left
                    if(game->currentBoard[i+1][j-1] == 1){
                        neighborCount++;
                    }
                    // check directly diagonal bottom right
                    if(game->currentBoard[i+1][j+1] == 1){
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