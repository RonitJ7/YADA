#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#define endl '\n'
using namespace std;

class sfood{
    public:
    int id;
    string name;
    float calories;
    int no_keywords;
    vector<string> keywords;
    float servingSize;

    sfood(int id,string name, float calories, vector<string> keywords, float servingSize){
        this->id = id;
        this->name = name;
        this->calories = calories;
        this->no_keywords = keywords.size();
        this->keywords = keywords;
        this->servingSize = servingSize;
    }
    void print(){
        cout<<"ID:"<<id<<'\n';
        cout<<"Name:"<<name<<endl;
        cout<<"Calories:"<<calories<<endl;
        cout<<"Serving size:"<<servingSize<<"\n\n";
    }
    void writeToFile(ofstream &fout){
        fout<<id<<' '<<name<<' '<<calories<<' '<<no_keywords<<' ';
        for(auto i:keywords){
            fout<<i<<' ';
        }
        fout<<servingSize<<'\n';
    }
};
class cfood: public sfood{
    public:
    int no_ingredients;
    vector<pair<sfood,int> > ingredients;
    cfood(int id, string name, vector<string> keywords, float servingSize, vector<pair<sfood,int> > ingredients):sfood(id,name,0,keywords,servingSize){
        this->no_ingredients = ingredients.size();
        this->ingredients = ingredients;
        for(auto i:ingredients){
            this->calories += i.first.calories;
        }
    }
    void printc(){
        cout<<"ID:"<<id<<'\n';
        cout<<"Name:"<<name<<endl;
        cout<<"Calories:"<<calories<<endl;
        cout<<"Serving size:"<<servingSize<<endl;
        cout<<"Ingredients:"<<endl;
        for(auto i:ingredients){
            i.first.print();
            cout<<"Quantity:"<<i.second<<endl;
        }
        cout<<'\n';
    }
    void writeToFilec(ofstream &fout){
        fout<<id<<' '<<name<<' '<<calories<<' '<<no_keywords<<' ';
        for(auto i:keywords){
            fout<<i<<' ';
        }
        fout<<no_ingredients<<' ';
        for(auto i:ingredients){
            fout<<i.first.id<<' '<<i.second<<' ';
        }
        fout<<servingSize<<'\n';
        fout<<'\n';
    }
};