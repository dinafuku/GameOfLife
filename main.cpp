#include "Simulation.h"

int main(int argc, char **argv){
    // checks argument count
    if(argc != 1){
        cout << endl << "invalid number of command line arguments" << endl;
        cout << "vaild command line argument: ./assignment3.out" << endl;
        return -1;
    }
    // runs simulation
    Simulation *simulation = new Simulation();
    simulation->simulate();
    delete simulation;
    return 0;
}
