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
void clrSn();
void oneRep();
void calcBMI();
void save();
void checkLoggedIn();
void signOut();

// arrays
vector<string> loginInfo(2);
vector<double> statInfo(2);
vector<string> measureUnits(2);
vector<string> measurementSystem(1);

// global variables
string logName;
string logPass;
string logSystem;

string statName;
double statH;
double statM;

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
    ifstream maxFile("oneRepMax.txt");
    if (!maxFile){
        ofstream maxFile("oneRepMax.txt");
    }
    ifstream logStat("loggedInStatus.txt");
    if (!maxFile){
        ofstream logStat("loggedInStatus.txt");
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

struct oneRM{
    string excercise;
    double max;
};

struct statusCheck{
    string loggedInName;
    string status;
};

// list
list<logInformation> login;
list<statInformation> stats;
list<oneRM> oneMax;

// code
void registration(){
    clrSn();
    int choice;
    cout << "1. Sign Up\n2. Login\n3. Exit" << endl;
    cin >> choice;
    if(choice == 1){
        clrSn();
        signUp();
    } else if(choice == 2){
        clrSn();
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
    if(measureSystem == "imperial"){
        int ft;
        double in;
        cin >> ft >> in;
        statInfo[0] = ft * 12 + in;
    } else {
        cin >> statInfo[0];
    }
    cout << "What is your weight?(" << unitM << "):" << endl;
    cin >> statInfo[1];

    // saving locally
    measurementSystem[0] = measureSystem;
    measureUnits[0] = unitL;
    measureUnits[1] = unitM;

    // finished signup
    menu();
}

void logIn(){
    string testPass;
    string testName;
    while(true){
        cout << "Please enter your username: " << endl;
        cin >> testName;
        cout << "Please enter a password: " << endl;
        cin >> testPass;
        ifstream logFile("logInfo.txt");
        ifstream statFile("statInfo.txt");
        clrSn();
        bool found = false;

        while (logFile >> logName >> logPass >> logSystem){
            if (testName == logName && testPass == logPass){
                found = true;
                cout << "Welcome Back!" << endl;
                measurementSystem[0] = logSystem;
                loginInfo[0] = logName;
                if(measurementSystem[0] == "metric"){
                    measureUnits[0] = "m";
                    measureUnits[1] = "kg";
                } else {
                    measureUnits[0] = "ft in";
                    measureUnits[1] = "lbs";
                }
                while (statFile >> statName >> statH >> statM){
                    if (testName == statName){
                        statInfo[0] = statH;
                        statInfo[1] = statM;
                        break;
                    }
                }
                break;
            }
        }

        logFile.close();
        statFile.close();

        if (!found){
            string choice;
            clrSn();
            cout << "Invalid username or password. Would you like to return? (y/n)" << endl;
            cin >> choice;
            if(choice == "y"){
                registration();
            } 
            clrSn();
        } else {
            menu();
        }
    }
}

void menu(){
    int choice;
    while(true){
        cout << "Options:\n1) Calculate one rep max\n2) Calculate BMI\n3) Exit\n4) Sign out" << endl;
        cin >> choice;
        while(true){
            if(choice == 1){
                oneRep();
                break;
            } else if(choice == 2){
                calcBMI();
                break;
            } else if(choice == 3){
                save();
                ofstream logStat("loggedInStatus.txt", ofstream::trunc);
                logStat << loginInfo[0] << " true" << '\n';
                logStat.close();
                exit(0);
            } else if(choice == 4){
                signOut();
            } else {
                cout << "Invalid Choice" << endl;
            }
        }
    }
}

void clrSn() {
    // #ifdef _WIN32
    //     system("cls");
    // #else
    //     system("clear");
    // #endif
    return;
}

void oneRep(){
    clrSn();
    int choice;
    string yn;
    string name;
    double repWeight;
    double reps;
    double oneRep;
    bool save = false;
    while(true){
        cout << "1) Calculate for one rep max\n2) View one rep max(es)\n3) return" << endl;
        cin >> choice;
        if(choice == 1){
            clrSn();
            while(true){
                cout << "Weight of Working Set (" << measureUnits[1] << "): " << endl;
                cin >> repWeight;
                cout << "Amount of repititions: " << endl;
                cin >> reps;
                oneRep = ( ( repWeight * reps ) / 30.48 ) + repWeight;
                cout << "Your one rep max is: "<< fixed << setprecision(1) << oneRep << measureUnits[1] << endl;
                cout << "Would you like to save your one rep max? (y/n)" << endl;
                cin >> yn;
                if(yn == "y"){
                    save = true;
                    cout << "What excercise is this?" << endl;
                    cin.ignore();
                    getline(cin, name);
                }
                if(save){
                    ofstream maxFile("oneRepMax.txt", ios::app);
                    maxFile << loginInfo[0] << ' ' << oneRep << ' ' << name << '\n';
                    maxFile.close();
                }   
                clrSn();
                cout << "\nWould you like to calculate again (1) or go back? (2)" << endl;
                cin >> choice;
                if(choice == 1){
                    clrSn();
                } else {
                    clrSn();
                    break;
                }
                break;
            }
        } else if(choice == 2){
            clrSn();
            string name;
            string weight;
            string excerciseName;
            ifstream maxFile("oneRepMax.txt");
            cout << "\n--- Your One Rep Maxes ---\n";
            while (maxFile >> name >> weight) {
                char c = maxFile.peek();
                if (isspace(c)) {
                    maxFile.ignore();
                }
                if (getline(maxFile, excerciseName)) {
                    cout << excerciseName << ": " << weight << endl;
                }
            }
            string re;
            cout << "\nEnter 1 to return" << endl;
            cin >> re;
            clrSn();
        } else{
            return;
        }
    }
}

void calcBMI(){
    clrSn();
    string choice;
    string result;
    double BMI;
    double height;
    double weight;
    cout << measurementSystem[0];
    if(measurementSystem[0] == "metric"){
        cout << "calculating";
        BMI = statInfo[1] / (statInfo[0] * statInfo[0]);
        cout << "Loaded Stats: " << statInfo[0] << " " << statInfo[1] << endl;
    } else if(measurementSystem[0] == "imperial"){
        cout << "calculating";
        cout << "Loaded Stats: " << statInfo[0] << " " << statInfo[1] << endl;
        BMI = (statInfo[1] * .703)/ (statInfo[0] * statInfo[0]) * 1000;
    }
    cout << "Based on your previous stats, your BMI is: " << fixed << setprecision(2) << BMI << endl;
    while(true){
        cout << "Would you like to calculate a new BMI? (y/n)" << endl;
        cin >> choice;
        if(choice == "y"){
            clrSn();
            if(measurementSystem[0] == "metric"){
                cout << "Please enter your height (m): " << endl;
                cin >> height;
                cout << "Please enter your weight (kgs): " << endl;
                cin >> weight;
                BMI = weight / (height * height);
            } else {
                int ft;
                int in;
                cout << "Please enter your height (ft in): " << endl;
                cin >> ft >> in;
                height = ft * 12 + in;
                cout << "Please enter your weight (lbs): " << endl;
                cin >> weight;
                BMI = (weight * .703)/ (height * height) * 1000;
            }
            if(BMI <= 17){
                result = "underweight";
            } else if(BMI <= 25){
                result = "normal";
            } else if(BMI <= 30){
                result = "overweight";
            } else{
                result = "obese";
            }
            cout << "Calculated BMI: " << BMI << ". You are " << result << endl;
        } else {
            clrSn();
            break;
        }
    }
}

void save(){
    // saving information
    ofstream logFile("logInfo.txt", ios::app);
    logFile << loginInfo[0] << ' ' << loginInfo[1] << ' ' << measurementSystem[0] << '\n';
    logFile.close();
    ofstream statFile("statInfo.txt", ios::app);
    statFile << loginInfo[0] << ' ' << statInfo[0] << ' ' << statInfo[1] << '\n';
    statFile.close();
}

void signOut(){
    ofstream logStat("loggedInStatus.txt", ofstream::trunc);
    logStat << loginInfo[0] << " false" << '\n';
    logStat.close();
    registration();
}

void checkLoggedIn(){
    string loggedIn, loggedName;
    ifstream statusCheck("loggedInStatus.txt");
    ifstream logFile("logInfo.txt");
    ifstream statFile("statInfo.txt");
    while (statusCheck >> loggedName >> loggedIn){
        if (loggedIn == "true"){
            loginInfo[0] = loggedName;
            cout << "Welcome Back " << loginInfo[0] <<"!" << endl;
            break;
        } else if(loggedIn == "false"){
            registration();
        }
    }
    while (logFile >> logName >> logPass >> logSystem){
        cout << logName << " " << logPass << " " << logSystem;
        if (loggedName == logName){
            measurementSystem[0] = logSystem;
            if(measurementSystem[0] == "metric"){
            measureUnits[0] = "m";
            measureUnits[1] = "kg";
            } else {
                measureUnits[0] = "ft in";
                measureUnits[1] = "lbs";
            }
        }
    }
    while (statFile >> statName >> statH >> statM){
        if (loggedName == statName){
            statInfo[0] = statH;
            statInfo[1] = statM;
            cout << "Loaded Stats: " << statInfo[0] << " " << statInfo[1] << endl; // Added label for clarity
            break;
        }
    }
    statFile.close();
    logFile.close();
    menu();
}


int main(){
    fileInitialize();
    checkLoggedIn();
}