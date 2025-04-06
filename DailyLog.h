#ifndef DLOG_H
#define DLOG_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "Food.h"

#define endl '\n'
#define LOGFILE "log.txt"
using namespace std;

typedef pair<string , pair<int , float>> log_t;

class DailyLog{
    public:
    string date;

    vector<pair<string , pair<int , float>>> logs;
    // {{Name , {Serving size , Calories}}
    DailyLog(string date ,  vector<pair<string , pair<int , float>>>logs_inp);
    void addLog(log_t log);
    int deletefromLog(string name , int& servings , float& calories);
    void viewLogs();
    int updateLog(string oldname, log_t newlog , int& servings , float& calories);
};

#endif