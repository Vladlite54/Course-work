#include <iostream>
#include "List.h"
#include "Menu.h"

using namespace std;

int main() {
    try {
       menu(); 
    } catch(ListException& e) {
        cout << "Error: "; 
        e.ShowInfo();
        cout << endl;
        
    }
    
    return 0;
}