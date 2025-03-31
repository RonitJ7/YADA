#ifndef FOOD_H
#define FOOD_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#define endl '\n'
using namespace std;
class sfood{
    public:
    enum {
        SIMPLE,
        COMPLEX
    }type;
    int id;
    string name;
    float calories;
    int no_keywords;
    vector<string> keywords;
    float servingSize;

    sfood(int id,string name, float calories, vector<string> keywords, float servingSize);
    void print();
    void writeToFile(ofstream &fout);
};
class cfood: public sfood{
    public:
    int no_ingredients;
    vector<pair<sfood,int> > ingredients;
    cfood(int id, string name, vector<string> keywords, float servingSize, vector<pair<sfood,int> > ingredients);
    void printc();
    void writeToFilec(ofstream &fout);
};

#endif