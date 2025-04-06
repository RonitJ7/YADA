#ifndef REV_H
#define REV_H

#include "Food.h"
#include "DailyLog.h"
#include "profile.h"
#include "utility.h"

using namespace std;

class Reverse{
    public:
    enum {
        ADD,
        DELETE,
        UPDATE
    }optype;
    vector<string> params;

    Reverse(string date , string name , int servings , float calories , char op_val); // for add and delete
    Reverse(string date , string name , string newname , int servings , float calories);// for update

};

#endif 