# ifndef UTIL
# define UTIL

#include "Food.cpp"
#include <iostream>
#include <fstream>
#include <string>

typedef pair<string , pair<int , float>> log_t;
using namespace std;

void get_date(string& date_str);
log_t get_logs(string& log_str);
bool fileExists(const string& filename);
void CreateFile(const string& filename);
float getfoodbyname(string& name , vector<sfood>& simpleFood , vector<cfood>& complexFood);
#endif