#include "utility.h"
#include <vector>

using namespace std;


void get_date(string& date_str) {
    // String is of the form : <<Date>> DD-MM-YYYY
    // Get the date from the string
    int i = 0;
    while (date_str[i] != ' ' && date_str[i] != '\0') {
        i++;
    }
    date_str = date_str.substr(i+1 , date_str.size() - i);
    // Now we have date_str = DD-MM-YYYY
}

log_t get_logs(string& log_str) {
    // String is of the form: Name | Serving size | Calories
    // Get the name from the string
    int i = 0;
    while (log_str[i] != '|' && log_str[i] != '\0') {
        i++;
    }
    string name = log_str.substr(0 , i);
    int offset = i;
    // Trim the leading white-spaces from name
    int len = name.size();
    while (name[len - 1] == ' ') {
        name = name.substr(0 , len - 1);
        len--;
    }
    // Now we get the serving size
    i+=2;
    while(log_str[i] != '|' && log_str[i] != '\0') {
        i++;
    }
    string ser_size = log_str.substr(offset + 2 , i - offset - 2);
    int serving_size = stoi(ser_size);
    // Now we get the calories
    i+=2;
    offset = i;
    while(log_str[i] != '\0') {
        i++;
    }
    string cal = log_str.substr(offset , i-offset);
    float calories = stof(cal);
    // Now we have the name , serving size and calories
    log_t logs = {name , {serving_size , calories}};
    return logs;
}

bool fileExists(const string& filename) {
    ifstream file(filename);
    return file.good();
}

void CreateFile(const string& filename) {
    ofstream file(filename);
    if (!file) {
        cerr << "Error creating file: " << filename << endl;
    }
    file.close();
}

float getfoodbyname(string& name , vector<sfood> const & simpleFood , vector<cfood> const & complexFood) {
    // String is of the form: Name
    // Search in simple foods first
    for (auto i : simpleFood) {
        if (i.name == name) {
            return i.calories;
        }
    }
    // Now search in complex foods
    for (auto i : complexFood) {
        if (i.name == name) {
            return i.calories;
        }
    }
    return -1.0f;
}

