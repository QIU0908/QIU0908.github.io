#include <iostream>
using namespace std;

int counter = 0;   // 外部變數，供其他檔案使用

void add() {
    counter++;
    cout << counter << endl;
}
