/******************************************************************
 * Simon Fraser University
 * ENSC-151 Introduction to Software Development for Engineers
 * Final Assignment
 * main.cpp -- main program
 * 
 * Author: Kevin Poon, Trevor Kwong, Bryan Servin, Max Leung, Samantha Huang
 *
 *******************************************************************/

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <list>
#include <string>
#include <cctype>
#include <vector>

using namespace std;

string measureSystem;
vector<double> userBMI(1);
vector<double> userStats();
// height = 0
// weight = 1

void clrSn() {
    // Clear the console screen
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

double initialization(){
    int choice;
    cout << "Welcome to SyncFit!" << endl;
    cout << "Which measurement system woudl you prefer?\n1) Metric\n2) Imperial" << endl;
    cin >> choice;
    while(true){
        if(choice == 1){
            measureSystem = "metric";
        } else if(choice == 2){
            measureSystem = "imperial";
        } else {
            clrSn();
            cout << "Invalid Choice -- Please enter 1 or 2" << endl;
            cout << "Which measurement system woudl you prefer?\n1) Metric\n2) Imperial" << endl;
            cin >> choice;
        }
    }
    clrSn();
}

double calcBMI(){
}

int main() {
    initialization();
}
