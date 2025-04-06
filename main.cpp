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
            // bool right = false;
            float calories = 0.0f;
            cout << "1. Add food to log.\n";
            cout << "2. Delete food from log.\n";
            cout << "3. Get calorie status for any day\n";
            cout << "4. Search for food using keywords.\n";
            cout << "5. View daily log.\n";
            cout << "6. Update Logs.\n";
            cout << "7. Undo Changes.\n";
            cout << "8. Back\n";
            cout << "What is your choice(1-8)? ";
            int choice = get_choice(1, 8);
            if (choice == 1)
            {
                cout << "Enter the date(DD-MM-YYYY) \n(Enter the string \"today\" for current day):";
                cin >> date;
                if (date == "today")
                {
                    date = get_current_date();
                }
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
                cout << "Enter the date(DD-MM-YYYY)\n(Enter the string \"today\" for current day):";
                string date;
                cin >> date;
                if (date == "today")
                {
                    date = get_current_date();
                }
                cout << "Enter the name of the food:";
                string name;
                cin >> name;
                inter.DeleteFromDailyLog(date, name);
            }
            else if (choice == 3)
            {
                cout << "Enter the date(DD-MM-YYYY)\n(Enter the string \"today\" for current day):";
                string date;
                cin >> date;
                if (date == "today")
                {
                    date = get_current_date();
                }
                inter.getCalories(date);
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
                else
                    ;
                pair<vector<sfood>, vector<cfood>> result = search_key_food(view_all, keywords, any_key, inter.simpleFood, inter.complexFood);

                vector<sfood> simpleResult = result.first;
                vector<cfood> complexResult = result.second;

                cout << "------------Simple foods----------------\n";
                for (auto i : simpleResult)
                {
                    i.print();
                }
                if (simpleResult.size() == 0)
                    cout << "No simple food found with the given keywords.\n";

                cout << "------------Complex foods----------------\n";
                for (auto i : complexResult)
                {
                    i.printc();
                }
                if (complexResult.size() == 0)
                    cout << "No complex food found with the given keywords.\n";
                cout << "------------------------------------------\n";
            }
            else if (choice == 5)
            {
                cout << "Enter the date(DD-MM-YYYY)\n(Enter the string \"today\" for current day):";
                string date;
                cin >> date;
                if (date == "today")
                {
                    date = get_current_date();
                }
                inter.viewDailyLog(date);
            }
            else if (choice == 6)
            {
                cout << "Enter the date(DD-MM-YYYY) you would like to change the logs for.\n(Enter the string \"today\" for current day):";
                string date;
                cin >> date;
                if (date == "today")
                {
                    date = get_current_date();
                }
                cout << "Enter the name of the food whose log you would like to alter:";
                string name;
                cin >> name;
                cout << "Enter the new name of the food (if any changes , else type \"none\"):";
                string newname;
                cin >> newname;
                if (newname == "none")
                    newname = name;
                calories = getfoodbyname(newname, inter.simpleFood, inter.complexFood);
                if (calories == -1)
                {
                    cout << "No food found with the name " << newname << endl;
                    continue;
                }
                cout << "Enter the number of servings:";
                int servings = get_min_choice(1);
                inter.updatelog(date, name, newname, servings, calories);
            }
            else if (choice == 7)
                inter.undo();
            else if (choice == 8)
                continue;
        }
        else if (n == 4)
        {
            cout << "Are you sure you want to exit?(yes/no)";
            bool texit = get_yes_no();
            if (texit)
            {
                inter.saveData();
                cout << "Saving Data...\n";
                cout << "Data saved successfully.\n";
                cout << "Exiting...\n";
                cout << "Goodbye!\n";
                exit(0);
            }
        }
    }
}
