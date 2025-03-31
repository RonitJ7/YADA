#ifndef PROFILE_H
#define PROFILE_H

#include <iostream>
#include <string>
#include <fstream>

using namespace std;
#define endl '\n'
enum activityLevel{
    SEDENTARY = 1,
    LIGHTLY_ACTIVE = 2,
    MODERATELY_ACTIVE = 3,
    DAILY_ACTIVE = 4,
    INTENSE_ACTIVE = 5
};
class Profile{
    public:
    bool female;
    float height;
    float age;
    float weight;
    enum activityLevel level;
    float targetIntake;
    int calcMethod;

    Profile();
    void modify(float age, float weight, int activityLevel,int calcMethod);
    void print();
    void calculateIntake();
    void putFile(ofstream &fout);
    float Mifflin_St_Jeor();
    float Harris_Benedict();
};

# endif