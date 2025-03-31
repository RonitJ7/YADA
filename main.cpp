#include <iostream>
#include <string>
#include "interface.h"
#include "inputHelp.h"
#include "utility.h"
#include "Search.h"

using namespace std;

signed main()
{
    Interface inter;
    while (1)
    {
        cout << "\n------------Select Section----------------\n";
        cout << "1. Add or search food\n";
        cout << "2. Profile\n";
        cout << "3. Daily log\n";
        cout << "4. Exit\n";
        cout << "What is your choice(1-4)? ";
        int n = get_choice(1, 4);
        cout << "\n------------Select Choice----------------\n";
        if (n == 1)
        {
            cout << "1. Add a new simple food.\n";
            cout << "2. Add a new complex food.\n";
            cout << "3. Search food using keywords.\n";
            cout << "4. Back\n";
            cout << "What is your choice(1-4)?";
            int choice = get_choice(1, 4);
            if (choice == 1)
                inter.addSimpleFood();
            else if (choice == 2)
                inter.addComplexFood();
            else if (choice == 3)
                inter.searchFood();
            else if (choice == 4)
                continue;
        }
        else if (n == 2)
        {
            cout << "1. View profile.\n";
            cout << "2. Change profile.\n";
            cout << "3. Back\n";
            cout << "What is your choice(1-3)? ";
            int choice = get_choice(1, 3);
            if (choice == 1)
                inter.p.print();
            else if (choice == 2)
                inter.modifyProfile();
            else if (choice == 3)
                continue;
        }
        else if (n == 3)
        {
            string date = "", name = "";
            bool right = false;
            float calories = 0.0f;
            cout << "1. Add food to log.\n";
            cout << "2. Delete food from log.\n";
            cout << "3. Get calorie status for today\n";
            cout << "4. Search for food using keywords.\n";
            cout << "5. Back\n";
            cout << "What is your choice(1-5)? ";
            int choice = get_choice(1, 5);
            if (choice == 1)
            {
                cout << "Enter the date(DD-MM-YYYY) Leave blank if logs are wanted for the current day:";
                cin >> date;
                cout << "Enter the name of the food:";
                string name;
                cin >> name;
                calories = getfoodbyname(name, inter.simpleFood, inter.complexFood);
                if (calories == -1)
                {
                    cout << "No food found with the name " << name << endl;
                    continue;
                }
                cout << "Enter the number of servings:";
                int servings = get_min_choice(1);

                inter.addToDailyLog(date, name, servings, calories);
            }
            else if (choice == 2)
            {
                cout << "Enter the date(DD-MM-YYYY):";
                string date;
                cin >> date;
                cout << "Enter the name of the food:";
                string name;
                cin >> name;
                inter.DeleteFromDailyLog(date, name);
            }
            else if (choice == 3)
            {
                cout << "Enter the date(DD-MM-YYYY):";
                string date;
                cin >> date;
                inter.viewDailyLog(date);
            }
            else if (choice == 4)
            {
                bool any_key = false;
                bool view_all = false;
                cout << "How many keywords do you want to search for?";
                int n = get_min_choice(1);
                vector<string> keywords;
                cout << "Enter the keywords:\n";
                for (int i = 0; i < n; i++)
                {
                    string s;
                    cin >> s;
                    keywords.push_back(s);
                }
                int keypref = get_search_key_pref();
                if (keypref == 2)
                    any_key = true;
                else if (keypref == 3)
                    view_all = true;
                else;
                pair<vector<sfood>, vector<cfood>> result = search_key_food(view_all, keywords, any_key, inter.simpleFood, inter.complexFood);

                vector<sfood> simpleResult = result.first;
                vector<cfood> complexResult = result.second;

                cout << "------------Simple foods----------------\n";
                for (auto i : simpleResult)
                {
                    i.print();
                }
                if(simpleResult.size() == 0)
                    cout << "No simple food found with the given keywords.\n";
                
                cout << "------------Complex foods----------------\n";
                for (auto i : complexResult)
                {
                    i.printc();
                }
                if(complexResult.size() == 0)
                    cout << "No complex food found with the given keywords.\n";
                cout << "------------------------------------------\n";
            }
            else if (choice == 5)
                continue;
        }
        else if (n == 4)
        {
            cout << "Are you sure you want to exit?(yes/no)";
            bool texit = get_yes_no();
            if (texit)
            {
                inter.saveData();
                exit(0);
            }
        }
    }
}
