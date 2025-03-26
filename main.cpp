#include <iostream>
#include <string>
using namespace std;


signed main(){
    Interface i;
    while(1){
        i.showMenu();
        int choice = i.getChoice();
        i.execute(choice);
    }
}
