#ifndef UTIL
#define UTIL

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <iomanip>
#include <sstream>
#include "Food.h"

typedef pair<string , pair<int , float>> log_t;
using namespace std;

log_t get_logs(string& log_str);
bool fileExists(const string& filename);
void CreateFile(const string& filename);
float getfoodbyname(string name , vector<sfood>& simpleFood , vector<cfood>& complexFood);
string get_current_date();

#endif