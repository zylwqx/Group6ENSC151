#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <list>
#include <string>
#include <cctype>
#include <vector>
#include <sstream>
#include <fstream>

using namespace std;

// prototypes
void registration();
void signUp();
void logIn();
void menu();
void fileInitialize();
void loginCheck();

// arrays
vector<string> loginInfo(2);
vector<double> statInfo(2);
vector<string> measureUnits(2);
vector<string> measurementSystem(1);

// open/create files
void fileInitialize(){
    ifstream logFile("logInfo.txt");
    if (!logFile){
        ofstream logFile("logInfo.txt");
    }
    ifstream statFile("statInfo.txt");
    if (!statFile){
        ofstream statFile("statInfo.txt");
    }
}



// files
struct logInformation{
    string name;
    string pass;
    string mSys;
};

struct statInformation{
    double h;
    double m;
};

// list
list<logInformation> login;
list<statInformation> stats;

// code
void registration(){
    int choice;
    cout << "1. Sign Up\n2. Login\n3. Exit" << endl;
    cin >> choice;
    if(choice == 1){
        signUp();
    } else if(choice == 2){
        logIn();
    } else if(choice == 3){
        exit(0);
    }
}

void signUp(){
    string password;
    string name;
    string measureSystem;
    string unitM;
    string unitL;
    int choice;
    
    // making an account
    cout << "Please enter your username: " << endl;
    cin >> loginInfo[0];
    cout << "Please enter a password: " << endl;
    cin >> loginInfo[1];
    
    // choosing a measurment system
    cout << "Which measurement system woudl you prefer?\n1) Metric\n2) Imperial" << endl;
    cin >> choice;
    while(true){
        if(choice == 1){
            measureSystem = "metric";
            unitM = "kg";
            unitL = "m";
            break;
        } else if(choice == 2){
            measureSystem = "imperial";
            unitM = "lbs";
            unitL = "ft in";
            break;
        } else {
            cout << "Invalid Choice -- Please enter 1 or 2" << endl;
            cout << "Which measurement system woudl you prefer?\n1) Metric\n2) Imperial" << endl;
            cin >> choice;
        }
    }   

    // user measurements
    cout << "What is your height?(" << unitL << "):" << endl;
    cin >> statInfo[0];
    cout << "What is your weight?(" << unitM << "):" << endl;
    cin >> statInfo[1];

    // saving information
    ofstream logFile("logInfo.txt", ios::app);
    logFile << loginInfo[0] << ' ' << loginInfo[1] << ' ' << measureSystem << '\n';
    logFile.close();
    ofstream statFile("statInfo.txt", ios::app);
    statFile << loginInfo[0] << ' ' << statInfo[0] << ' ' << statInfo[1] << '\n';
    statFile.close();
    measurementSystem[0] = measureSystem;
    measureUnits[0] = unitL;
    measureUnits[1] = unitM;

    // finished signup
    menu();
}

void logIn(){
    // loginCheck();
    string testName;
    string testPass;
    while(true){
        cout << "Please enter your username: " << endl;
        cin >> testName;
        cout << "Please enter a password: " << endl;
        cin >> testPass;
        ifstream logFile("logInfo.txt");
        ifstream statFile("statInfo.txt");
        
        bool found = false;
        string logName;
        string logPass;
        string logSystem;

        string statName;
        double statH;
        double statM;

        while (logFile >> logName >> logPass >> logSystem){
            if (testName == logName && testPass == logPass){
                found = true;
                cout << "Welcome Back!" << endl;
                measurementSystem[0] = logSystem;
                break;
                // while (statFile >> statName >> statH >> statM){

                // }
            }
        }

        logFile.close();
        statFile.close();

        if (!found){
            cout << "Invalid username or password." << endl;
        } else {
            menu();
        }
    }
}

// void loginCheck(){
//     ifstream logFile("logInfo.txt");
//     string line;
// }

void menu(){
    int choice;
    while(true){
        cout << "Options:\n1) Calculate one rep max\n2) Calculate BMI\n3) Exit" << endl;
        cin >> choice;
        while(true){
            if(choice == 1){
                // oneRep();
                break;
            } else if(choice == 2){
                // calcBMI();
                break;
            } else if(choice == 3){
                exit(0);
            } else{
                cout << "Invalid Choice" << endl;
            }
        }
    }
}

int main(){
    fileInitialize();
    registration();
}