#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "Food.cpp"
#include "inputHelp.h"
#include "profile.cpp"
using namespace std;

#define endl '\n'
class Interface{

    vector<sfood> simpleFood;
    vector<cfood> complexFood;
    public:
    Profile p;
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
    }

    void modifyProfile(){
        cout<<"Enter the new age: (0 if you don't want to change)";
        float age = get_min_float(0);
        cout<<"Enter the new weight:(0 if you don't want to change)";
        float weight = get_min_float(0);
        cout << "Activity Levels:" << endl;
        cout << "1 - SEDENTARY" << endl;
        cout << "2 - LIGHTLY_ACTIVE" << endl;
        cout << "3 - MODERATELY_ACTIVE" << endl;
        cout << "4 - DAILY_ACTIVE" << endl;
        cout << "5 - INTENSE_ACTIVE" << endl;
        cout<<"Enter the new activity level(1-5)(0 if you don't want to change):";
        int activityLevel = get_choice(1,5);
        p.modify(age,weight,activityLevel);
        askToSave();
    }
};