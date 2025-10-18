#include<iostream>
#include<string>
using namespace std;

int main(void){
	string a;
	int num=0;
	for(int i=0;i<5;i++){
		cout<<"input string #"<<i+1<<":";
		getline(cin,a);
		num+=(a.length());
	}
	cout<<"all element nember are "<<num;
}