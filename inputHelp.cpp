#include <iostream>
#include <string>
#include "inputHelp.h"

using namespace std;

int get_choice(int min, int max) {
    int choice;
    while (1) {
        cin >> choice;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input. Please enter a number between " << min << " and " << max << ":\n";
        }
        else if (choice >= min && choice <= max) return choice;
        else{
            cout << "Please enter a valid choice (" << min << '-' << max << "):\n";
            cin.ignore(1000,'\n');
        }
    }
}

int get_min_choice(int min) {
    int choice;
    while (1) {
        cin >> choice;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input. Please enter a number atleast " << min << ":\n";
        }
        else if (choice >= min) return choice;
        else{
            cout << "Please enter a valid choice (atleast " << min << "):\n";
            cin.ignore(1000,'\n');
        }
    }
}

float get_min_float(int min){
    float choice;
    while (1) {
        cin >> choice;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input. Please enter a number atleast " << min << ":\n";
        }
        else if (choice >=(float) min) return choice;
        else{
            cout << "Please enter a valid choice (atleast " << min << "):\n";
            cin.ignore(1000,'\n');
        }
    }
}

bool get_yes_no() {
    string response;
    while (1) {
        cin >> response;
        if (response == "yes") return true;
        if (response == "no") return false;
        cout << "Please enter a valid choice (yes/no): ";

    }
}

int get_search_key_pref() {
    cout << "Search by:\n";
    cout << "1. All keywords\n";
    cout << "2. Any keyword\n";
    cout << "3. View All\n";
    cout << "Enter your choice (1-3): ";
    int choice = get_choice(1, 3);
    return choice;
}