#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "Food.h"
#include "Search.h"
#include "DailyLog.h"

#define endl '\n'
#define LOGFILE "log.txt"
using namespace std;

typedef pair<string , pair<int , float>> log_t;

class DailyLog{
    public:
    string date;

    vector<pair<string , pair<int , float>>> logs;
    // {{Name , {Serving size , Calories}}
    DailyLog(string date ,  vector<pair<string , pair<int , float>>> logs){
        this->date = date;
        this->logs = logs;
    }
    
    void addLog(log_t log){
        for(auto it = this->logs.begin(); it != this->logs.end(); it++){
            if(it->first == log.first){
                it->second.first += log.second.first;
                it->second.second += log.second.second;
                return;
            }
        }
        this->logs.push_back(log);
        return;
        
    }

    int deletefromLog(string name){
        // Check if name exists
        bool exists = false;
        auto it = this->logs.begin();
        for(it ; it != this->logs.end(); it++){
            if(it->first == name){
                exists = true;
                break;
            }
        }
        if(!exists){
            return -1;
        }
        if(this->logs.size() == 1){
            // Save it onto the undo stack before deleting
            this->logs.clear();
            return 0;
        }
        // Simply delete that log.
        this->logs.erase(it);
        return 1;
    }

    void viewLogs(){
        cout<<"Date: "<<this->date<<endl;
        cout<<"Name | Serving size | Calories"<<endl;
        for(auto i: this->logs){
            cout<<i.first<<" | "<<i.second.first<<" | "<<i.second.second<<endl;
        }
        cout<<endl;
    }

    int updateLog(string oldname, log_t newlog){
        auto it = this->logs.begin();
        bool exists = false;
        for(it ; it != this->logs.end(); it++){
            if(it->first == oldname){
                exists = true;
                break;
            }
        }
        if(!exists){
            return -1;
        }
        // Now we have to update the log
        // Save the old log onto the undo stack
        *it = newlog;
        return 0;
    }



};