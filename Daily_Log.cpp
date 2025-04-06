#include <iostream>

#include <string>
#include <vector>
#include <fstream>
#include "Food.h"
#include "Search.h"
#include "DailyLog.h"
#include "Reverse.h"
using namespace std;


    // {{Name , {Serving size , Calories}}
    DailyLog:: DailyLog(string date ,  vector<pair<string , pair<int , float>>>logs_inp){
        this->date = date;
        this->logs = logs_inp;
    }
    
    void DailyLog:: addLog(log_t log){
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

    int DailyLog:: deletefromLog(string name , int& servings , float& calories){
        // Check if name exists
        bool exists = false;
        auto it = this->logs.begin();
        for(; it != this->logs.end(); it++){
            if(it->first == name){
                exists = true;
                break;
            }
        }
        if(!exists){
            return -1;
        }
        servings = it->second.first;
        calories = it->second.second;
        if(this->logs.size() == 1){
            this->logs.clear();
            return 0;
        }
        // Simply delete that log.
        this->logs.erase(it);
        return 1;
    }

    void DailyLog:: viewLogs(){
        cout<<"Date: "<<this->date<<endl;
        cout<<"Name | Serving size | Calories"<<endl;
        for(auto i: this->logs){
            cout<<i.first<<" | "<<i.second.first<<" | "<<i.second.second<<endl;
        }
        cout<<endl;
    }

    int DailyLog:: updateLog(string oldname, log_t newlog , int& servings , float& calories){
        auto it = this->logs.begin();
        bool exists = false;
        for(; it != this->logs.end(); it++){
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
        servings = it->second.first;
        calories = it->second.second;
        *it = newlog;
        return 0;
    }


