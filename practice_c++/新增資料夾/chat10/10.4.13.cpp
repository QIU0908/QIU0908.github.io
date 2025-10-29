#include <iostream>
using namespace std;

void sort_desc(int &a, int &b, int &c);

int main(void) {
    int i = 3, j = 5, k = 2;
    sort_desc(i, j, k);
    cout << i << "\t" << j << "\t" << k;
    return 0;
}

void sort_desc(int &a, int &b, int &c) {
    int temp;
    if (a < b) { temp = a; a = b; b = temp; }
    if (a < c) { temp = a; a = c; c = temp; }
    if (b < c) { temp = b; b = c; c = temp; }
}
