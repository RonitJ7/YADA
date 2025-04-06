#include "Reverse.h"
#include "utility.h"

using namespace std;
Reverse::Reverse(string date , string name , int servings , float calories , char op_val){
    params.push_back(date);
    params.push_back(name);
    params.push_back(to_string(servings));
    params.push_back(to_string(calories));
    if(op_val == 'a'){
        optype = ADD;
    }
    else
    optype = DELETE;
    
}
Reverse::Reverse(string date , string name , string newname , int servings , float calories){
    params.push_back(date);
    params.push_back(name);
    params.push_back(newname);
    params.push_back(to_string(servings));
    params.push_back(to_string(calories));
    optype = UPDATE;
}
