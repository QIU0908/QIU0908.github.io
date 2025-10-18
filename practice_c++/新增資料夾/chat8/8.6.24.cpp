#include<iostream>
#include<string>
using namespace std;

int main(void){
	string a;
	string b="the";
	cout<<"please input a string ";
	getline(cin,a);
	
	cout<<"the is in string index "<<a.find(b);
	


}

