#include <iostream>
using namespace std;

int main() {
    char prt[100];  
    cout << "input:";
    cin.getline(prt, 100);

    char *p = prt;  

    while (*p != '\0') {  
        if (*p ==' ') {
            *p='*';  
        }
        cout << *p;  
        p++;        
    }

    cout << endl;
    return 0;
}
