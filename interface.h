#ifndef INTERFACE_H
#define INTERFACE_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cstdio>
#include <map>
#include "Food.h"
#include "DailyLog.h"
#include "profile.h"
#include "Reverse.h"

#define endl '\n'
using namespace std;

class Interface{
    map<string, DailyLog> dailyLogs;
    map<string , int> updates;
    map<string , bool> deleteFile;
    vector<Reverse> undostack;

    public:
    Profile p;
    string latest_date;
    vector<sfood> simpleFood;
    vector<cfood> complexFood;

    Interface();
    void addSimpleFood();
    vector<sfood> getSimpleFood();
    vector<cfood> getComplexFood();
    void addComplexFood();
    void searchFood();
    void modifyProfile();
    void addToDailyLog(string date , string name , int servings , float calories);
    void DeleteFromDailyLog(string date , string name);
    void viewDailyLog(string date);
    void askToSave();
    DailyLog* get_inst(string date);
    void getCalories(string date);
    void updatelog(string date , string oldname , string newname , int servings , float calories);
    void saveData();
    void undo();
    void update_r(string date , string oldname , string newname , int servings , float calories);
    void delete_r(string date , string name , int servings , float calories); ;
    void add_r(string date , string name , int servings , float calories);
};

#endif