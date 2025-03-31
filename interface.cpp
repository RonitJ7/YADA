#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cstdio>
#include <map>
#include "Food.h"
#include "inputHelp.h"
#include "profile.h"
#include "DailyLog.h"
#include "utility.h"
#include "Search.h"

using namespace std;

#define endl '\n'
class Interface{

    // Changes start
    map<string, DailyLog> dailyLogs;
    map<string , int> updates;
    map<string , bool> deleteFile;

    public:
    Profile p;
    vector<sfood> simpleFood;
    vector<cfood> complexFood;
    string latest_date;
    Interface(){
        
        ifstream fin("simpleFood.txt");
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
        fin.close();
        // Read from Daily Logs
        fin.open(LOGFILE);
        while(!fin.eof()){
            string date;
            getline(fin,date);
            get_date(date);
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
            DailyLog d(date,logs);
            dailyLogs[date] = d;
            latest_date = date;
        }
        fin.close();
    }
    vector<sfood> getSimpleFood(){
        return this->simpleFood;
    }

    vector<cfood> getComplexFood(){
        return this->complexFood;
    }

    void addSimpleFood(){
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

    void addComplexFood(){
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

    void searchFood(){
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

    void askToSave(){
        cout<<"Would you like to save your data?(yes/no)";
        bool c = get_yes_no();
        if(c)saveData();
    }

    void saveData(){
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
    }

    void modifyProfile(){
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

    DailyLog* get_inst(string date)
    {
        if(dailyLogs.find(date) == dailyLogs.end()){
            return NULL ;
        }
        return &(dailyLogs[date]);
    }
    
    void addToDailyLog(string date , string name , int servings , float calories){
        if(dailyLogs.find(date) == dailyLogs.end()){
            vector<log_t> logs;
            logs.push_back({name , {servings , calories}});
            DailyLog d(date,logs);
            dailyLogs[date] = d;
            if(latest_date < date){
                latest_date = date;
            }
            updates[date] += 1;
            deleteFile[date] = false;
            return;
        }
        DailyLog* d = get_inst(date);
        log_t log = {name , {servings , calories}};
        d->addLog(log);
        updates[date] += 1;
        return;
    }

    void DeleteFromDailyLog(string date , string name){
        DailyLog* d = get_inst(date);
        if(d == NULL){
            cout<<"No logs found for the date "<<date<<endl;
            return;
        }
        int ret = d->deletefromLog(name);
        if(ret == -1)
        {
            cout<<"No info found for the food "<<name<<endl;
            return;
        }
        if(ret == 0){
            deleteFile[date] = true;
            dailyLogs.erase(date);
            updates[date] += 1;
            return;
        }
        updates[date] += 1;
        return;
    }

    void viewDailyLog(string date){
        DailyLog* d = get_inst(date);
        if(d == NULL){
            cout<<"No logs found for the date "<<date<<endl;
            return;
        }
        d->viewLogs();
    }

    void getCalories(string date){
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

    void updatelog(string date , string oldname , string newname , int servings , float calories){
        
        log_t newlog = {newname , {servings , calories}};
        DailyLog* d = get_inst(date);
        if(d == NULL){
            cout<<"No logs found for the date "<<date<<endl;
            return;
        }
        int ret = d->updateLog(oldname , newlog);
        if(ret == -1){
            cout<<"No info found for the food "<<oldname<<endl;
            return;
        }
        updates[date] += 1;
        return;
    }

    void undo(){

    }
};