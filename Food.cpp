#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "Food.h"
#include "colors.h"
#define endl '\n'
using namespace std;



    sfood:: sfood(int id,string name, float calories, vector<string> keywords, float servingSize){
        this->id = id;
        this->name = name;
        this->calories = calories;
        this->no_keywords = keywords.size();
        this->keywords = keywords;
        this->servingSize = servingSize;
        this->type = SIMPLE;
    }
    void sfood::print() {
        cout << RED << "ID:" << id << RESET << '\n';
        cout << GREEN << "Name:" << name << RESET << endl;
        cout << YELLOW << "Calories:" << calories << RESET << endl;
        cout << BLUE << "Serving size(in g):" << servingSize << RESET << "\n\n";
    }
    void sfood:: writeToFile(ofstream &fout){
        fout<<id<<' '<<name<<' '<<calories<<' '<<no_keywords<<' ';
        for(auto i:keywords){
            fout<<i<<' ';
        }
        fout<<servingSize<<'\n';
    }

    cfood:: cfood(int id, string name, vector<string> keywords, float servingSize, vector<pair<sfood,int> > ingredients):sfood(id,name,0,keywords,servingSize){
        this->no_ingredients = ingredients.size();
        this->ingredients = ingredients;
        for(auto i:ingredients){
            this->calories += i.first.calories * i.second;
        }
        this->type = COMPLEX;
    }
    void cfood::printc() {
        cout << RED << "ID:" << id << RESET << '\n';
        cout << GREEN << "Name:" << name << RESET << endl;
        cout << YELLOW << "Calories:" << calories << RESET << endl;
        cout << BLUE << "Serving size(in g):" << servingSize << RESET << endl;
        cout << "\nIngredients:" << "\n\n";
        for (auto i : ingredients) {
            i.first.print();
            cout << "Quantity:" << i.second << endl;
        }
        cout << '\n';
    }
    void cfood:: writeToFilec(ofstream &fout){
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