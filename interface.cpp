#include <iostream>
using namespace std;
class Interface{
public:
    void showMenu(){
        // cout<<"1. Add a new simple food.\n";
        // cout<<"2. Add a new complex food.\n";
        // cout<<"3.View profile.\n";
        // cout<<"4. Change profile.\n";
        // cout<<"5. Add food to log.\n";
        // cout<<"6. Delete food from log.\n";
        // cout<<"7. Search food in keyboard.\n";
        // cout<<"8. Get calorie status for today\n";
        // cout<<"9. Undo\n";
        cout<<"------------Select Section----------------\n";
        cout<<"1. Add or search food\n";
        cout<<"2. Profile\n";
        cout<<"3. Daily log\n";
        cout<<"4. Exit";
        cout<<"What is your choice(1-4)?";
        int n;
        while(1){
            cin>>n;
            if(n>=1 && n<=4)break;
            else cout<<"Please enter a valid choice(1-4)\n";
        }
        if(n == 1){
            cout<<"1. Add a new simple food.\n";
            cout<<"2. Add a new complex food.\n";
            cout<<"3. Search food in keyboard.\n";
            cout<<"4. Back\n";
            int choice;
            while(1){
                cin>>choice;
                if(choice>=1 && choice<=4)break;
                else cout<<"Please enter a valid choice(1-4)\n";
            }
            if(choice == 1)
            else if(choice == 2)
            else if(choice == 3)
            else if(choice == 4)
        }
        else if(n == 2){
            cout<<"1. View profile.\n";
            cout<<"2. Change profile.\n";
            cout<<"3. Back\n";
            int choice;
            while(1){
                cin>>choice;
                if(choice>=1 && choice<=3)break;
                else cout<<"Please enter a valid choice(1-4):";
            }
            if(choice == 1)
            else if(choice == 2)
            else if(choice == 3)
        }
        else if(n == 3){
            cout<<"1. Add food to log.\n";
            cout<<"2. Delete food from log.\n";
            cout<<"3. Get calorie status for today\n";
            cout<<"4. Undo\n";
            cout<<"5. Back\n";
        }
        else if(n == 4){
            cout<<"Are you sure you want to exit?(y/n)";
            char c;
            while(1){
                cin>>c;
                if(c == 'y' || c == 'n')break;
                else cout<<"Please enter a valid choice(y/n)\n";
            }
            if(c == 'y')exit(0);
        }
    }
};