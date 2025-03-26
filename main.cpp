#include <iostream>
#include <string>
#include "interface.cpp"
#include "inputHelp.h"
using namespace std;

signed main(){
    Interface i;
    while(1){
        cout<<"\n------------Select Section----------------\n";
        cout<<"1. Add or search food\n";
        cout<<"2. Profile\n";
        cout<<"3. Daily log\n";
        cout<<"4. Exit\n";
        cout<<"What is your choice(1-4)? ";
        int n = get_choice(1, 4);
        cout<<"\n------------Select Choice----------------\n";
        if(n == 1){
            cout<<"1. Add a new simple food.\n";
            cout<<"2. Add a new complex food.\n";
            cout<<"3. Search food in keyboard.\n";
            cout<<"4. Back\n";
            cout<<"What is your choice(1-4)?";
            int choice = get_choice(1, 4);
            if(choice == 1)i.addSimpleFood();
            else if(choice == 2)i.addComplexFood();
            else if(choice == 3)i.searchFood();
            else if(choice == 4)continue;
        }
        else if(n == 2){
            cout<<"1. View profile.\n";
            cout<<"2. Change profile.\n";
            cout<<"3. Back\n";
            cout<<"What is your choice(1-3)? ";
            int choice = get_choice(1, 3);
            if(choice == 1);
            else if(choice == 2);
            else if(choice == 3)continue;
        }
        else if(n == 3){
            cout<<"1. Add food to log.\n";
            cout<<"2. Delete food from log.\n";
            cout<<"3. Get calorie status for today\n";
            cout<<"4. Back\n";
            cout<<"What is your choice(1-4)? ";
            int choice = get_choice(1, 4);
            if(choice == 1);
            else if(choice == 2);
            else if(choice == 3);
            else if(choice == 4)continue;
        }
        else if(n == 4){
            cout<<"Are you sure you want to exit?(yes/no)";
            bool texit = get_yes_no();
            if(texit){
                i.saveData();
                exit(0);
            }
        }
    }
}
