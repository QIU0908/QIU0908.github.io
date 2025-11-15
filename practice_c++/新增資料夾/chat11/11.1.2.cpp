#include<iostream>
using namespace std;

struct date{
	int yyyy;
	int mm;
	int dd;
};


int main(void){
	date date;
	cin>>date.yyyy;
	cin>>date.mm;
	cin>>date.dd;
	
	cout<<date.mm<<"/"<<date.dd<<"/"<<date.yyyy;
}