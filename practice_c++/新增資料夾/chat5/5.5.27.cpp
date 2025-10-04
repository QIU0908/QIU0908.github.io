#include<iostream>
using namespace std;
int main(void){
	int month;
	cin>>month;
		switch(month){
			case 1:
			case 2:
				cout<<"winter vacation";
				break;
			case 3:
			case 4:
			case 5:
			case 6:
				cout<<"last semester";
				break;
			case 7:
			case 8:
				cout<<"summer vacation";
				break;
			case 9:
			case 10:
			case 11:
			case 12:
				cout<<"next semester";
				break;
			default:
				cout<<"error";
				break;
		}
		return 0;
}