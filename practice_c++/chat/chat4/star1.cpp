/*
in put a num 
ex  3 and you got

*
**
***
**
*

*/


#include <iostream>
using namespace std;

int main() {
	int num;
	cin >> num;
	int a = 1, c =0;

	for (a = 1; a <= num + (num - 1); a++) {
		c += 1;
		if (c <= num) {
			for (int b = 1; b <= c; b++) {
				cout << '*';
			}cout << endl;
		}
		else {
			for (int d=0; d < num - (c - num); d++) {
				cout << '*';
			}cout << endl;
		}
	}
	return 0;
}
