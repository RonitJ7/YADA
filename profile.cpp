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

    Profile(){
        bool female;
        float age,height,weight;
        int alevel;
        int calcMethod;
        float targetIntake;
        ifstream fin("Profile.txt");
        fin>>female>>height>>age>>weight>>alevel>>calcMethod;
        fin.close();
        // cout<<female<<" "<<height<<" "<<age<<" "<<weight<<" "<<alevel<<'\n';
        this->female = female;
        this->age = age;
        this->height = height;
        this->weight = weight;
        this->level = (enum activityLevel)alevel;
        this->calcMethod = calcMethod;
        calculateIntake();
    }
    void modify(float age, float weight, int activityLevel,int calcMethod){
        if(age > 0)this->age = age;
        if(weight > 0)this->weight = weight;
        if(activityLevel > 0)this->level = (enum activityLevel)activityLevel;
        if(calcMethod > 0)this->calcMethod = calcMethod;
        calculateIntake();
    }
    void print(){
        string gender = "Male";
        if(female)gender = "Female";
        cout<<"Age:"<<age<<endl;
        cout<<"Gender: "<<gender<<endl;
        cout<<"Weight:"<<weight<<endl;
        cout<<"Height:"<<height<<endl;
        cout<<"Activity level: ";
        switch(level){
            case SEDENTARY:cout<<"Sedentary\n";break;
            case LIGHTLY_ACTIVE:cout<<"Lightly active\n";break;
            case MODERATELY_ACTIVE:cout<<"Moderately active\n";break;
            case DAILY_ACTIVE:cout<<"Daily active\n";break;
            case INTENSE_ACTIVE:cout<<"Intense active\n";break;
        }
        cout<<"Calorie intake:"<<targetIntake<<endl;
        cout<<"Calculation method: ";
        switch(calcMethod){
            case 1: cout<<"Mifflin-St Jeor\n";break;
            case 2: cout<<"Harris-Benedict\n";break;
        }
    }

    void putFile(ofstream& fout){
        fout<<female<<" "<<height<<" "<<age<<" "<<weight<<" "<<level<<" "<<calcMethod<<'\n';
    }
    
    void calculateIntake(){
        switch(calcMethod){
            case 1: targetIntake =  Mifflin_St_Jeor(); break;
            case 2: targetIntake =  Harris_Benedict();
        }
    }

    float Mifflin_St_Jeor(){
        float cal = 10*weight + 6.25*height - 5*age;
        if(female)cal -= 161;
        else cal += 5;
        float multiply[6] = {1,1.2,1.375,1.55,1.725,1.9};
        cal *= multiply[level];
        cal*=0.8;
        return cal;
    }
    float Harris_Benedict(){
        float cal;
        if(!female)cal = 13.397*weight + 4.799*height - 5.677*age + 88.362;
        else cal = 9.247*weight + 3.098*height - 4.330*age + 447.593;
        float multiply[6] = {1,1.2,1.375,1.55,1.725,1.9};
        cal *= multiply[level];
        cal*=0.8;
        return cal;
    }
};