#include <iostream>
using namespace std;

int main() {
    char a[100];  
    cout << "input:";
    cin.getline(a, 100);

    char *prt = a;  

    while (*prt != '\0') {  
        if (*prt >= 'a' && *prt <= 'z') {
            *prt = *prt - ('a' - 'A');  
        }
        cout << *prt;  
        prt++;        
    }

    cout << endl;
    return 0;
}
