#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <list>
#include <string>
#include <cctype>
#include <vector>
#include <sstream>
#include <fstream>
#include <cmath>

using namespace std;

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
    ifstream exFile("excerciseTrack.txt");
    if (!exFile){
        ofstream exFile("excerciseTrack.txt");
    }
    ifstream sleepFile("sleepTrack.txt");
    if (!sleepFile){
        ofstream sleepFile("sleepTrack.txt");
    }
}

// files
struct logInformation{
    string name, pass, msys, gender;
};

struct statInformation{
    double h, m;
};

struct oneRM{
    string excercise;
    double max;
};

struct statusCheck{
    string loggedInName, status;
};

struct exTrack{
    string split;
    string excercise;
    int reps;
    double repWeight;
};

struct sleepTrack{
    double day;
    double sleepT;
    double wakeT;
    double hours;
};

// struct macroTrack{
//     string foodName;
//     double kCal, protein, fat, carb, fibre, gramsConsumed; 
// };

// struct FoodItem {
//     string macroType, subCategory, name;
//     double kCal, protein, fat, carb, fibre;
// };

// arrays
vector<string> loginInfo(3);
vector<double> statInfo(2);
vector<string> measureUnits(2);
vector<string> measurementSystem(1);
vector<exTrack> exList;
vector<sleepTrack> sleepList;

// prototypes
void registration(); void signUp(); void logIn(); void signOut(); 
void menu(); void oneRep(); void calcBMI();
void excerciseTracker(); void sleepTracker();
void loadExcersises(); void loadSleep();
void saveExcersises(); void saveSleep(); 
void fileInitialize(); void loginCheck(); void clrSn(); void save(); void checkLoggedIn();

// code
void registration(){
    clrSn();
    int choice;
    cout << "--- WELCOME TO SYNCFIT ---" << endl;
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
    cout << "--- SIGNUP ---" << endl;
    cout << "Please enter your username: " << endl;
    cin >> loginInfo[0];
    cout << "Please enter a password: " << endl;
    cin >> loginInfo[1];
    
    // gender
    cout << "Gender: " << endl;
    cin >> loginInfo[2];

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
    save();
    menu();
}

void logIn(){
    string testPass;
    string testName;

    string logName;
    string logPass;
    string logSystem;

    string statName;
    double statH;
    double statM;
    while(true){
        cout << "--- LOGIN ---" << endl;
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
                loginInfo[0] = logName;
                loadExcersises();
                loadSleep();
                measurementSystem[0] = logSystem;
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
    clrSn();
    int choice;
    while(true){
        cout << "--- MAIN MENU ---" << endl;
        cout << "1) One Rep Max\n2) BMI\n3) Excersises\n4) Sleep\n5) Exit\n6) Sign out" << endl;
        cin >> choice;
        while(true){
            if(choice == 1){
                oneRep();
                break;
            } else if(choice == 2){
                calcBMI();
                break;
            } else if(choice == 3){
                excerciseTracker();
                break;
            } else if(choice == 4){
                sleepTracker();
                break;
            } else if(choice == 5){
                ofstream logStat("loggedInStatus.txt", ofstream::trunc);
                logStat << loginInfo[0] << " true" << '\n';
                logStat.close();
                exit(0);
            } else if(choice == 6){
                signOut();
            } else {
                cout << "Invalid Choice" << endl;
                break;
            }
        }
    }
}

void clrSn() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
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
        cout << "--- ONE REP ---" << endl;
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
            clrSn();
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
    if(measurementSystem[0] == "metric"){
        BMI = statInfo[1] / (statInfo[0] * statInfo[0]);
    } else if(measurementSystem[0] == "imperial"){
        BMI = (statInfo[1] * .703)/ (statInfo[0] * statInfo[0]) * 1000;
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
    cout << "Based on your previous stats, your BMI is: " << fixed << setprecision(2) << BMI << ". You are " << result <<"." << endl;
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
    logFile << loginInfo[0] << ' ' << loginInfo[1] << ' ' << measurementSystem[0] << ' ' << loginInfo[2] << '\n';
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

void loadExcersises() {
    ifstream exFile("excerciseTrack.txt");

    string username;
    exTrack entry;

    exList.clear();
    
    while (exFile >> username >> entry.split >> entry.excercise >> entry.reps >> entry.repWeight) {
        if (username == loginInfo[0]) { 
            exList.push_back(entry); 
        }
    }
}

void saveExcersises(){
    ofstream exFile("excerciseTrack.txt", ofstream::trunc); 
    
    for (const auto& entry : exList) {
        exFile << loginInfo[0] << ' ' << entry.split << ' ' << entry.excercise << ' ' << entry.reps << ' ' << entry.repWeight << '\n';
    }
    exFile.close();
}

void excerciseTracker() {
    string choice;
    string bChoice;

    while(true){
        clrSn();
        cout << "--- EXCERCISE TRACKER ---" << endl;
        cout << "1) View All Exercises\n2) Add New Exercise\n3) Save and Return" << endl;
        cin >> choice;

        if (choice == "1") {
            clrSn();
            cout << "--- Your Excercises ---" << endl;
            if (exList.empty()) {
                cout << "No exercises recorded yet." << endl;
            } else {
                for (size_t i = 0; i < exList.size(); ++i) {
                    cout << i + 1 << ". Split: " << exList[i].split << " | Ex: " << exList[i].excercise << " | " << exList[i].reps << " reps @ " << exList[i].repWeight << measureUnits[1] << endl;
                }
            }
            cout << "Back (1) Return (2)" << endl;
            cin >> bChoice;
            if(bChoice == "2"){
                clrSn();
                break;
            }
        } else if (choice == "2") {
            clrSn();
            exTrack newEntry;
            cout << "Enter Split Name (e.g., ChestDay): " << endl;
            cin >> newEntry.split;
            cout << "Enter Exercise Name (No Spaces): " << endl;
            cin >> newEntry.excercise;
            cout << "Enter Reps: "; 
            cin >> newEntry.reps;
            cout << "Enter Weight (" << measureUnits[1] << "): "; 
            cin >> newEntry.repWeight;

            exList.push_back(newEntry);
            cout << "Exercise added successfully." << endl;
        } else if (choice == "3") {
            saveExcersises();
            clrSn();
            break;
        } else {
            cout << "Invalid choice. Please try again." << endl;
        }
    }
}

void checkLoggedIn(){
    string logName;
    string logPass;
    string logSystem;

    string statName;
    double statH;
    double statM;
    string loggedIn, loggedName;
    ifstream statusCheck("loggedInStatus.txt");
    while (statusCheck >> loggedName >> loggedIn){
        if (loggedIn == "true"){
            loginInfo[0] = loggedName;
            clrSn();
            cout << "Welcome Back " << loginInfo[0] <<"!" << endl;
            loadExcersises();
            loadSleep();
            break;
        } else if(loggedIn == "false" || loggedName == " false"){
            statusCheck.close();
            registration();
            return;
        }
    }
    ifstream logFile("logInfo.txt");
    while (logFile >> logName >> logPass >> logSystem){
        if (loggedName == logName){
            measurementSystem[0] = logSystem;
            if (measurementSystem[0] == "metric"){
                measureUnits[0] = "m";
                measureUnits[1] = "kg";
            } else {
                measureUnits[0] = "ft in";
                measureUnits[1] = "lbs";
            }
            break;
        }
    }
    logFile.close();
    ifstream statFile("statInfo.txt");
    while (statFile >> statName >> statH >> statM){
        if (loggedName == statName){
            statInfo[0] = statH;
            statInfo[1] = statM;
        }
    }
    statFile.close();
    menu();
}

void loadSleep(){
    ifstream sleepFile("sleepTrack.txt");

    string username;
    sleepTrack entry;

    sleepList.clear();

    while (sleepFile >> username >> entry.day >> entry.wakeT >> entry.sleepT >> entry.hours) {
        if (username == loginInfo[0]){
            sleepList.push_back(entry);
        }
    }

}

void saveSleep(){
    ofstream sleepFile("sleepTrack.txt", ofstream::trunc);

    for (const auto& entry : sleepList){
        sleepFile << loginInfo[0] << ' ' << entry.day << ' ' << entry.sleepT << ' ' << entry.wakeT << ' ' << entry.hours << '\n';
    }
    sleepFile.close();
}

void sleepTracker() {
    string choice;
    int bChoice;
    string b;

    while(true){
        clrSn();
        cout << "--- SLEEP TRACKER ---" << endl;
        cout << "1) View Sleep\n2) Track Sleep\n3) Save and Return" << endl;
        cin >> choice;

        if (choice == "1"){
            clrSn();
            cout << "--- Tracked Sleep ---" << endl;
            if (sleepList.empty()) {
                cout << "No sleep recorded yet" << endl;
            } else {
                for (size_t i = 0; i < sleepList.size(); ++i) {
                    cout << i + 1 << ". Day: " << sleepList[i].day << " | Slept: " << sleepList[i].sleepT << " | Wake: " << sleepList[i].wakeT << " | Slept For: " << sleepList[i].hours << " hours"<< endl;
                }
            }
            cout << "Back (1) Return (2)" << endl;
            cin >> bChoice;
            if(bChoice == 2){
                saveSleep();
                clrSn();
                break;
            }
        } else if (choice == "2"){
            clrSn();
            sleepTrack newEntry;
            cout << "Enter Day (mm.dd): " << endl;
            cin >> newEntry.day;
            cout << "Enter time slept (hh.mm): " << endl;
            cin >> newEntry.sleepT;
            cout << "Enter time woken up (hh.mm): " << endl;
            cin >> newEntry.wakeT;

            int sHour = newEntry.sleepT;
            double sMin = (newEntry.sleepT - sHour)*100;

            int wHour = newEntry.wakeT;
            double wMin = (newEntry.wakeT - wHour)*100;

            int dHour = wHour+24 - sHour;
            double dMin = sMin - wMin;

            newEntry.hours = dHour - dMin/60;
            sleepList.push_back(newEntry);
            cout << "Sleep Tracked" << endl;
        } else if (choice == "3"){
            saveSleep();
            clrSn();
            break;
        } else {
            cout << "Invalid choice. Please try again." << endl;
        }
    }
}

int main(){ 
    fileInitialize();
    checkLoggedIn();
}