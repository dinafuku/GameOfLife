#include "Simulation.h"
#include <limits>

Simulation::Simulation(){}

Simulation::~Simulation(){}

void Simulation::simulate(){
    try{
        string mode = "\0";
        string configuration = "\0";
        string numRows = "\0";
        string numCols = "\0";
        string choice = "\0";
        string density = "\0";
        string output = "\0";
        string filePath = "\0";
        Process *process = new Process();

        cout << endl << "Welcome to Game of Life!" << endl;
        cout << "Please provide input specified in parentheses() when given and provide proper input/output files when prompted";

        cout << endl << endl;
        cout << "Random Configuration (type random)" << endl;
        cout << "Specify Configuration (type specify) " << endl;
        cout << "- ";
        cin >> configuration;
        // checks if user input is correct
        while(configuration.compare("random") != 0 && configuration.compare("specify") != 0){
            cout << endl;
            cout << "INVALID INPUT: Please type either random or specify" << endl;
            cout << "- ";
            cin.clear();
            cin >> configuration;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << endl;
        int correct = 0;
        int isDensity = 1;
        // if user wants random, prompt for length, width, density and check for correct inputs
        if(configuration.compare("random") == 0){
            cout << "Input length of the board (integer)" << endl;
            cout << "- ";
            cin >> numRows;
            correct = checkInputCorrect(numRows, isDensity);
            while(correct == 1){
                cout << endl << "INAVLID INPUT: Input integer not string" << endl;
                cout << "Input length of the board" << endl;
                cout << "- ";
                cin >> numRows;
                correct = checkInputCorrect(numRows, isDensity); 
            }
            cout << "Input width of the board" << endl;
            cout << "- ";
            cin >> numCols;
            correct = checkInputCorrect(numCols, isDensity);
            while(correct == 1){
                cout << endl << "INAVLID INPUT: Input integer not string" << endl;
                cout << "Input width of the board" << endl;
                cout << "- ";
                cin >> numCols;
                correct = checkInputCorrect(numCols, isDensity);
            }
            cout << "Input density of the world" << endl;
            cout << "- ";
            cin >> density;
            isDensity = 0;
            correct = checkInputCorrect(density, isDensity);
            while(correct == 1){
                cout << endl << "INAVLID INPUT: Input number between 0 and 1" << endl;
                cout << "Input density of the world" << endl;
                cout << "- ";
                cin >> density;
                correct = checkInputCorrect(density, isDensity);
            }
            while(stod(density) <= 0 || stod(density) > 1){
                if(stod(density) == 1){
                    break;
                }
                cout << endl << "INAVLID INPUT: Input number between 0 and 1" << endl;
                cout << "Input density of the world" << endl;
                cout << "- ";
                cin >> density;
                correct = checkInputCorrect(density, isDensity);
            }
            cout << endl;
        }
        // if user wants to specify configuration, prompt for file path
        else if(configuration.compare("specify") == 0){
            cout << "Input File Path or File Name" << endl;
            cout << "- ";
            getline(cin, filePath);
            cout << endl;
        }

        cout << "Choose Boundary Mode" << endl;
        cout << "Classic (type classic)" << endl;
        cout << "Doughnut (type doughnut)" << endl;
        cout << "Mirror (type mirror)" << endl;
        cout << "- ";
        cin >> mode;
        // make sure user input is correct
        while(mode.compare("classic") != 0 && mode.compare("doughnut") != 0 && mode.compare("mirror") != 0){
            cout << endl;
            cout << "INVALID INPUT: Please type either classic or doughnut or mirror" << endl;
            cout << "- ";
            cin >> mode;
        }

        cout << endl;

        cout << "Pause before generations? (type pause)" << endl;
        cout << "Press enter key to go to next generation? (type enter)" << endl;
        cout << "Output to file (type output)" << endl;
        cout << "- ";
        cin >> choice;
        // checks if user input is correct
        while(choice.compare("pause") != 0 && choice.compare("enter") != 0 && choice.compare("output") != 0){
            cout << endl;
            cout << "INVALID INPUT: Please type either pause or enter or output" << endl;
            cout << "- ";
            cin >> choice;
        }
        // prompt for output file
        if(choice.compare("output") == 0){
            cout << endl;
            cout << "What is the name of your output file?" << endl;
            cout << "- ";
            cin >> output;
            cout << endl;
        }

        int temp = 0;
        if(choice.compare("pause") == 0){
            temp = 1;
        }
        else if (choice.compare("enter") == 0){
            temp = 2;
        }

        if(mode.compare("classic") == 0){
            Classic *classic;
            // create classic mode with random board
            if(configuration.compare("random") == 0){
                classic = new Classic(stoi(numRows), stoi(numCols), stod(density));
            }
            // create classic given file path 
            else{
                classic = new Classic(process->fileProcess(filePath), process->getHeight(), process->getWidth());
            }
            // if user wants to output to file
            if(choice.compare("output") == 0){
                process->outputToFile(classic, output);
            }
            // run classic mode to terminal
            else{
                classic->classicRun(temp);
            }
            delete classic;
        }
        else if(mode.compare("doughnut") == 0){
            Doughnut *doughnut;
            // create doughnut mode with random board
            if(configuration.compare("random") == 0){
                doughnut = new Doughnut(stoi(numRows), stoi(numCols), stod(density));
            }   
            // create doughnut given file path
            else{
                doughnut = new Doughnut(process->fileProcess(filePath), process->getHeight(), process->getWidth());
            }
            // if user wants to output to file
            if(choice.compare("output") == 0){
                process->outputToFile(doughnut, output);
            }
            // run doughnut mode to terminal
            else{
                doughnut->doughnutRun(temp);
            }
            delete doughnut;
        }
        else{
            Mirror *mirror;
            // create mirror mode with random board
            if(configuration.compare("random") == 0){
                mirror = new Mirror(stoi(numRows), stoi(numCols), stod(density));
            }
            // create mirror given file path
            else{
                mirror = new Mirror(process->fileProcess(filePath), process->getHeight(), process->getWidth());
            }
            // if user wants to output to file
            if(choice.compare("output") == 0){
                process->outputToFile(mirror, output);
            }
            // run mirror mode to terminal
            else{
                mirror->mirrorRun(temp);
            }
            delete mirror;
        }

        delete process; 
    }
    catch(runtime_error& excpt){
        cout << excpt.what() << endl;
    }
}

int Simulation::checkInputCorrect(string input, int isDensity){
    int correct = 0;
    // make sure user input isn't a bad char
    for(int i = 0; i < input.length(); i++){
        if(isDensity == 1){
            if(input.at(i) == '.'){
                correct = 1;
            }
        }
        else if(isDensity == 0){
            if(input.length() < 2 && input.at(0) != '1'){
                return 1;
            }
            if(input.at(i) == '.'){
                if(i+1 == input.length()){
                    return 1;
                }
            }
        }
        if(isalpha(input.at(i)) != 0 || input.at(i) == '~' || input.at(i) == '`' || input.at(i) == '!' 
        || input.at(i) == '@' || input.at(i) == '#' || input.at(i) == '$' || input.at(i) == '%' || input.at(i) == '^' 
        || input.at(i) == '&' || input.at(i) == '*' || input.at(i) == '(' || input.at(i) == ')' || input.at(i) == '-' 
        || input.at(i) == '_' || input.at(i) == '+' || input.at(i) == '=' || input.at(i) == '|' || input.at(i) == ':'
        || input.at(i) == ';' || input.at(i) == '<' || input.at(i) == ',' || input.at(i) == '>' || input.at(i) == '?' 
        || input.at(i) == '/' || input.at(i) == '\\' || input.at(i) == '\'' || input.at(i) == '\"'){
            correct = 1;
        }
    }
    return correct;
}