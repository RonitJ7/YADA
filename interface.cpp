#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cstdio>
#include <map>
#include <filesystem>
#include "Food.h"
#include "inputHelp.h"
#include "profile.h"
#include "DailyLog.h"
#include "utility.h"
#include "Search.h"
#include "interface.h"

using namespace std;

    Interface:: Interface(){
        
        ifstream fin("simpleFood.txt");
        string line;
        while(!fin.eof()){
            int id;
            string name;
            float calories = -1;
            int no_keywords = -1;
            vector<string> keywords;
            float servingSize = -1;
            fin>>id>>name>>calories>>no_keywords;
            for(int i=0;i<no_keywords;i++){
                string s;
                fin>>s;
                keywords.push_back(s);
            }
            fin>>servingSize;
            if(calories == -1 || servingSize == -1 || no_keywords == -1)break;
            sfood f(id,name,calories,keywords,servingSize);
            simpleFood.push_back(f);       
        }
        // cout << "Simple food done" << endl;
        fin.close();
        fin.open("complexFood.txt");
        while(!fin.eof()){
            int id;
            string name;
            float calories = -1;
            int no_keywords = -1;
            vector<string> keywords;
            float servingSize = -1;
            int no_ingredients;
            vector<pair<sfood,int > > ingredients;
            fin>>id>>name>>calories>>no_keywords;
            for(int i=0;i<no_keywords;i++){
                string s;
                fin>>s;
                keywords.push_back(s);
            }
            fin>>no_ingredients;
            for(int i=0;i<no_ingredients;i++){
                int id;
                fin>>id;
                int quantity;
                fin>>quantity;
                ingredients.push_back({simpleFood[id],quantity});
            }
            if(calories == -1 || servingSize == -1 || no_keywords == -1)break;
            cfood f(id,name,keywords,0,ingredients);
            complexFood.push_back(f);
        }
        // cout << "Complex food done" << endl;
        fin.close();
        // Read from Daily Logs
        fin.open(LOGFILE);
        while(getline(fin, line)){
            string date;
            date = line;
            vector<log_t> logs;
            ifstream fin2("./Logs/" + date + ".txt");
            while(!fin2.eof()){
                string log_str;
                getline(fin2,log_str);
                if(log_str == "")break;
                log_t log = get_logs(log_str);
                logs.push_back(log);
            }
            fin2.close();
            dailyLogs.emplace(date, DailyLog(date, logs));
            deleteFile[date] = false;
            updates[date] = 0;
        }
        // cout << "Logs done" << endl;
        fin.close();
        remove(LOGFILE);
        ofstream fout(LOGFILE);
        fout.close();
    }
    vector<sfood> Interface:: getSimpleFood(){
        return this->simpleFood;
    }

    vector<cfood> Interface:: getComplexFood(){
        return this->complexFood;
    }

    void Interface:: addSimpleFood(){
        cout<<"Enter the name of the food:";
        string name;
        cin>>name;
        cout<<"Enter the calories in the food:";
        float calories = get_min_float(0);
        cout<<"Enter the number of keywords:";
        int n = get_min_choice(1);
        vector<string> keywords;
        cout<<"Enter the keywords:";
        for(int i=0;i<n;i++){
            string s;
            cin>>s;
            keywords.push_back(s);
        }
        cout<<"Enter the serving size:(in g)";
        float servingSize = get_min_float(0);
        sfood f(simpleFood.size(),name,calories,keywords,servingSize);
        simpleFood.push_back(f);
        askToSave();
    }

    void Interface:: addComplexFood(){
        cout<<"Enter the name of the food:";
        string name;
        cin>>name;
        cout<<"Enter the number of keywords:";
        int n = get_min_choice(1);
        vector<string> keywords;
        cout<<"Enter the keywords:";
        for(int i=0;i<n;i++){
            string s;
            cin>>s;
            keywords.push_back(s);
        }
        cout<<"Enter the number of ingredients:";
        int m = get_min_choice(1);
        vector<pair<sfood,int> > ingredients;
        for(int i=0;i<m;i++){
            cout<<"Enter the id of the simple food:";
            int id = get_choice(0,simpleFood.size()-1);
            cout<<"Enter the quantity of the food:";
            int quantity = get_min_choice(1);
            ingredients.push_back({simpleFood[id],quantity});
        }
        cfood f(complexFood.size(),name,keywords,0,ingredients);
        complexFood.push_back(f);
        askToSave();
    }

    void Interface:: searchFood(){
        cout<<"How many keywords do you want to search for?";
        int n = get_min_choice(1);
        vector<string> keywords;
        cout<<"Enter the keywords:\n";
        for(int i=0;i<n;i++){
            string s;
            cin>>s;
            keywords.push_back(s);
        }
        cout<<"------------Simple foods----------------\n";
        for(auto i: simpleFood){
            for(auto j: i.keywords){
                bool found = false;
                for(auto k: keywords){
                    if(j == k){
                        i.print();
                        found = true;
                        break;
                    }
                }
                if(found)break;
            }
        }
        cout<<"------------Complex foods----------------\n";
        for(auto i: complexFood){
            for(auto j: i.keywords){
                bool found = false;
                for(auto k: keywords){
                    if(j == k){
                        i.printc();
                        found = true;
                        break;
                    }
                }
                if(found)break;
            }
        }
    }

    void Interface:: askToSave(){
        cout<<"Would you like to save your data?(yes/no)";
        bool c = get_yes_no();
        if(c)saveData();
    }

    void Interface:: saveData(){
        ofstream fout("simpleFood.txt");
        for(auto i: simpleFood){
            i.writeToFile(fout);
        }
        fout.close();
        fout.open("complexFood.txt");
        for(auto i: complexFood){
            i.writeToFilec(fout);
        }
        fout.close();
        fout.open("Profile.txt");
        p.putFile(fout);
        fout.close();
        // Save the daily logs

        fout.open(LOGFILE);
        for(auto& dates : dailyLogs)
        {
            string date = dates.first;
            DailyLog& d = dates.second;
            if(deleteFile[date] == true){
                continue;
            }
            fout<<date<<endl;
            if(updates[date] == 0 ){
                continue;
            }
            if(filesystem::exists("./Logs/" + date + ".txt"))
                remove(("./Logs/" + date + ".txt").c_str());
            ofstream fout1("./Logs/" + date + ".txt");
            for(auto i: d.logs){
                fout1<<i.first<<" | "<<i.second.first<<" | "<<i.second.second<<endl;
            }
            fout1.close();
            
        }
        fout.close();
        for(auto& dates: deleteFile)
        {
            string date = dates.first;
            if(dates.second == true){
                if(filesystem::exists("./Logs/" + date + ".txt"))
                    remove(("./Logs/" + date + ".txt").c_str());
                }
        }
        // reset the updates and deletes
        for(auto& dates: updates)
        {
            dates.second = 0;
        }
        for(auto& dates: deleteFile)
        {
            dates.second = false;
        }
    }

    void Interface:: modifyProfile(){
        cout<<"Enter the new age: (0 if you don't want to change)";
        float age = get_min_float(0);
        cout<<"Enter the new weight(kg):(0 if you don't want to change)";
        float weight = get_min_float(0);
        cout << "Activity Levels:" << endl;
        cout << "1 - SEDENTARY" << endl;
        cout << "2 - LIGHTLY_ACTIVE" << endl;
        cout << "3 - MODERATELY_ACTIVE" << endl;
        cout << "4 - DAILY_ACTIVE" << endl;
        cout << "5 - INTENSE_ACTIVE" << endl;
        cout<<"Enter the new activity level(1-5)(0 if you don't want to change):";
        int activityLevel = get_choice(0,5);
        cout<<"Calorie Calculation methods:\n";
        cout<<"1. Mifflin-St Jeor\n";
        cout<<"2. Harris-Benedict\n";
        cout<<"Enter the new calculation method(0 if you don't want to change):";
        int calcMethod = get_choice(0,2);
        p.modify(age,weight,activityLevel,calcMethod);
        askToSave();
    }

    DailyLog* Interface:: get_inst(string date)
    {
        auto it = dailyLogs.find(date);
        if(it == dailyLogs.end()){
            return NULL ;
        }
        return &it->second;
    }
    
    void Interface:: addToDailyLog(string date , string name , int servings , float calories){
        if(dailyLogs.find(date) == dailyLogs.end()){
            vector<log_t> logs;
            logs.push_back({name , {servings , calories}});
            dailyLogs.emplace(date, DailyLog(date, logs));
            updates[date] += 1;
            deleteFile[date] = false;
            // Add this to undo_stack
            Reverse r(date , name , servings , calories , 'a');
            undostack.push_back(r);
            askToSave();
            return;
        }
        DailyLog* d = get_inst(date);
        log_t log = {name , {servings , calories}};
        d->addLog(log);
        updates[date] += 1;
        // Add this to undo_stack
        Reverse r(date , name , servings , calories , 'a');
        undostack.push_back(r);
        askToSave();
        return;
    }

    void Interface:: DeleteFromDailyLog(string date , string name){
        DailyLog* d = get_inst(date);
        if(d == NULL){
            cout<<"No logs found for the date "<<date<<endl;
            return;
        }
        int servings;
        float calories;
        int ret = d->deletefromLog(name , servings , calories);
        if(ret == -1)
        {
            cout<<"No info found for the food "<<name<<endl;
            return;
        }
        Reverse r(date , name , servings , calories , 'd');
        undostack.push_back(r);
        if(ret == 0){
            deleteFile[date] = true;
            dailyLogs.erase(date);
            updates[date] += 1;
            askToSave();
            return;
        }
        updates[date] += 1;
        askToSave();
        return;
    }

    void Interface:: viewDailyLog(string date){
        DailyLog* d = get_inst(date);
        if(d == NULL){
            cout<<"No logs found for the date "<<date<<endl;
            return;
        }
        d->viewLogs();
    }

    void Interface:: getCalories(string date){
        DailyLog* d = get_inst(date);
        float cal = 0.0f;
        if(d == NULL){
            cout<<"No logs found for the date "<<date<<endl;
            return;
        }
        for(auto i: d->logs){
            cal += i.second.second;
        }
        cout<<"Total calories consumed on "<<date<<" are "<<cal<<endl;
    }

    void Interface:: updatelog(string date , string oldname , string newname , int servings , float calories){
        
        log_t newlog = {newname , {servings , calories}};
        DailyLog* d = get_inst(date);
        if(d == NULL){
            cout<<"No logs found for the date "<<date<<endl;
            return;
        }
        int servings_old;
        float calories_old;
        int ret = d->updateLog(oldname , newlog , servings_old , calories_old);
        if(ret == -1){
            cout<<"No information has been logged for the food "<<oldname<<endl;
            return;
        }
        Reverse r(date , newname , oldname , servings_old , calories_old);
        undostack.push_back(r);
        updates[date] += 1;
        askToSave();
        return;
    }

    void Interface :: undo(){
        if(undostack.size() == 0){
            cout<<"Nothing to undo\n";
            return;
        }
        // cout << "Size:" << undostack.size() << endl;
        Reverse r = undostack.back();
        undostack.pop_back();
        // cout << (r.optype) << endl;
        if (r.optype == Reverse::ADD){
            string date = r.params[0];
            string name = r.params[1];
            int servings = stoi(r.params[2]);
            float calories = stof(r.params[3]);
            add_r(date , name , servings , calories);
        }
        else if (r.optype == Reverse::DELETE){
            string date = r.params[0];
            string name = r.params[1];
            int servings = stoi(r.params[2]);
            float calories = stof(r.params[3]);
            delete_r(date , name , servings , calories);
        }
        else if (r.optype == Reverse::UPDATE){
            string date = r.params[0];
            string oldname = r.params[1];
            string newname = r.params[2];
            int servings = stoi(r.params[3]);
            float calories = stof(r.params[4]);
            update_r(date , oldname , newname , servings , calories);
        }
        return ;
    }

    void Interface:: update_r(string date , string oldname , string newname , int servings , float calories){
        log_t newlog = {newname , {servings , calories}};
        DailyLog* d = get_inst(date);
        int servings_old;
        float calories_old;
        int ret = d->updateLog(oldname , newlog , servings_old , calories_old);
        updates[date] -= 1;
        return ;
    }
    void Interface:: delete_r(string date , string name , int servings , float calories){
        DailyLog* d = get_inst(date);
        if(d == NULL){
            vector<log_t> logs;
            logs.push_back({name , {servings , calories}});
            dailyLogs.emplace(date, DailyLog(date, logs));
            updates[date] -= 1;
            deleteFile[date] = false;
            return;
        }
        log_t log = {name , {servings , calories}};
        d->addLog(log);
        updates[date] -= 1;
        return;
    }
    void Interface:: add_r(string date , string name , int servings , float calories){
        DailyLog* d = get_inst(date);
        int num1;
        float num2;
        int ret = d->deletefromLog(name , num1 , num2);
        if(ret == 0){
            deleteFile[date] = true;
            dailyLogs.erase(date);
            updates[date] -= 1;
            return;
        }
        updates[date] -= 1;
        return;
    }