#ifndef SEARCH_H
#define SEARCH_H

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <set>
#include "Food.h"

using namespace std;

bool is_1_Subset_2(vector<string>& a , vector<string>& b);
bool is_1_disj_2(vector<string> a , vector<string> b);
pair<vector<sfood> , vector<cfood>> search_key_food(bool view_all, vector<string>& keywords, bool any_key, vector<sfood>& simpleFood, vector<cfood>& complexFood);

#endif
