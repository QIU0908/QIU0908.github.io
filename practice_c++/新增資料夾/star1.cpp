/*
學道如果要用RAW的觀念一定要重0開始 
不然會導致後面跳行
用RAW當自變數時會亂掉
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
