#include <iostream>
using namespace std;

int counter = 0; // 外部變數

void add() {
    counter++;
    cout << counter << endl;
}
