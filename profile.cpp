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

    Profile(){
        bool female;
        float age,height,weight;
        int alevel;
        ifstream fin("Profile.txt");
        fin>>female>>height>>age>>weight>>alevel;
        fin.close();
        // cout<<female<<" "<<height<<" "<<age<<" "<<weight<<" "<<alevel<<'\n';
        this->female = female;
        this->age = age;
        this->height = height;
        this->weight = weight;
        this->level = (enum activityLevel)alevel;
    }
    void modify(float age, float weight, int activityLevel){
        if(age > 0)this->age = age;
        if(weight > 0)this->weight = weight;
        if(activityLevel > 0)this->level = (enum activityLevel)activityLevel;
    }
    void print(){
        cout<<"Age:"<<age<<endl;
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
    }
    void putFile(ofstream& fout){
        fout<<female<<" "<<height<<" "<<age<<" "<<weight<<" "<<level<<'\n';
    }
};