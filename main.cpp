/******************************************************************
 * Simon Fraser University
 * ENSC-151 Introduction to Software Development for Engineers
 * Final Assignment
 * main.cpp -- main program
 * 
 * Author: Kevin Poon, Trevor Kwong, Bryan Servin, Max Leung, Samantha Huang
 * Sources: https://www.nasm.org/resources/one-rep-max-calculator
 *          
 *******************************************************************/

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

string measureSystem;
string unitM;
string unitL;
vector<double> userStats(3);
vector<string> userInfo(2);
vector<double> userBMI(2);

struct userLogIn{
    string username;
    string password;
    string system;
    double height;
    double weight;
    double bmi;  
};

struct excercises{
    string username;
    string excercise;
    int exWeight;
    int exRep;
};

list<userLogIn> login;
list<excercises> workout;

void signUp();
void logIn();
void registration();
void menu();
void excerciseTracker();

void close(){
    ofstream logfile("login_information.txt", ios::app);
    logfile << userInfo[0] << ' ' << userInfo[0] << ' ' << measureSystem << ' ' << userStats[0] << ' ' << userStats[1] << ' '  << userBMI[1] << '\n';
    logfile.close();
    exit(0);
}

void fileCheck(){
    string line;
    ifstream logfile("login_information.txt");
    if (!logfile) {
        ofstream logfile("login_information.txt");
    } else{
        while(getline(logfile, line)){
            stringstream ss(line);
            userLogIn lg;

            ss >> lg.username;
            ss >> lg.password;
            ss >> lg.system;
            ss >> lg.height;
            ss >> lg.weight;
            ss >> lg.bmi;

            login.push_back(lg);
            measureSystem = lg.system;
            userInfo[0] = lg.username;
            userInfo[1] = lg.password;
            userStats[0] = lg.height;
            userStats[1] = lg.weight;
            userBMI[1] = lg.bmi;
        }
        logfile.close();
    }
}

void clrSn() {
    // Clear the console screen
    // #ifdef _WIN32
    //     system("cls");
    // #else
    //     system("clear");
    // #endif
    return;
}

double measurement(){
    int choice;
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
            unitL = "ft";
            break;
        } else {
            clrSn();
            cout << "Invalid Choice -- Please enter 1 or 2" << endl;
            cout << "Which measurement system woudl you prefer?\n1) Metric\n2) Imperial" << endl;
            cin >> choice;
        }
    }
    clrSn();
    registration();
}

double calcBMI(){
    string result;
    int choice;
    string choice1;
    cout << "Your previous BMI was: " << userBMI[1] << "\n "<<endl;
    while(true){
        if(measureSystem == "metric"){
            cout << "Enter your height (cm): " << endl;
            cin >> userStats[0];
            cout << "Enter your weight (kg): " << endl;
            cin >> userStats[1];
            userBMI[0] = userStats[1] / (userStats[0] * userStats[0]) * 10000;
            cout << "metric" << endl;
        } else if(measureSystem == "imperial"){
            cout << "Enter your height (ft in): " << endl;
            cin >> userStats[0] >> userStats[2];
            cout << "Enter your weight (lbs): " << endl;
            cin >> userStats[1];
            userStats[0] = userStats[0] * 12 + userStats[2];
            userBMI[0] = (userStats[1] * .703) / (userStats[0] * userStats[0]) * 1000;
        }
        if(userBMI[0] <= 17){
            result = "underweight";
        } else if(userBMI[0] <= 25){
            result = "normal";
        } else if(userBMI[0] <= 30){
            result = "overweight";
        } else{
            result = "obese";
        }
        cout << "Your BMI is: "<< fixed << setprecision(1) <<userBMI[0] << endl;
        cout << "You are "<< result << endl;
        cout << "\nWould you like to save your BMI? (yes/no)" << endl;
        cin >> choice1;
        if (choice1 == "yes" || choice1 == "Yes" || choice1 == "YES") {
            userBMI[1] = userBMI[0];
        }
        cout << "\nWould you like to calculate again (1) or go back? (2)" << endl;
        cin >> choice;
        if(choice == 1){
            clrSn();
        } else{
            break;
        }
    }
    clrSn();
    return(0);
}

double oneRep(){
    clrSn();
    int choice;
    double repWeight;
    double reps;
    double oneRep;
    while(true){
        cout << "Weight of Working Set: " << endl;
        cin >> repWeight;
        cout << "Amount of repititions: " << endl;
        cin >> reps;
        oneRep = ( ( repWeight * reps ) / 30.48 ) + repWeight;
        cout << "Your one rep max is: "<< fixed << setprecision(1) << oneRep << unitM << endl;
        cout << "\nWould you like to calculate again (1) or go back? (2)" << endl;
        cin >> choice;
        if(choice == 1){
            clrSn();
        } else{
            break;
        }
    }
    clrSn();
    return 0;
}

void logIn(){
    string password;
    string name;
    while(true){
        cout << "Please enter your username: " << endl;
        cin >> name;
        cout << "Please enter a password: " << endl;
        cin >> password;
        for(int i = 0; i < 100; i++){
            for(const userLogIn& lg : login){
                if(name == userInfo[0] && password == userInfo[1]){
                    clrSn();
                    cout << "Welcome Back!" << endl;
                    menu();
                    break;
                }
            }
        }
        
        cout << "Invalid name or password" << endl;
    }
}

void signUp(){
    clrSn();
    string password;
    string name;
    cout << "Please enter your username: " << endl;
    cin >> userInfo[0];
    cout << "Please enter a password: " << endl;
    cin >> userInfo[1];
    clrSn();
    measurement();
}

void registration(){
    int choice;
    cout << "1. Sign Up\n2. Login\n3. Exit" << endl;
    cin >> choice;
    if(choice == 1){
        signUp();
    } else if(choice == 2){
        logIn();
    } else if(choice == 3){
        close();
    }
}

void menu(){
    int choice;
    while(true){
        cout << "Options:\n1) Calculate one rep max\n2) Calculate BMI\n3) Exit" << endl;
        cin >> choice;
        while(true){
            if(choice == 1){
                oneRep();
                break;
            } else if(choice == 2){
                calcBMI();
                break;
            } else if(choice == 3){
                exit(0);
            } else{
                cout << "Invalid Choice" << endl;
            }
        }
    }
}

// void excerciseTracker(){
//     int choice;
//     while(true){
//         cout << ""
//     }
//     menu();
// }

int main() {
    fileCheck();

    cout << "Welcome to SyncFit!" << endl;
    cout << "";
    registration();
}
