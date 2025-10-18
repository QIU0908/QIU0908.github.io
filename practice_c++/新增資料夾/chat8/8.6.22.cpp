#include<iostream>
#include<string>
using namespace std;

int main(void){
	string a;
	string b;
	
	getline(cin,a);
	getline(cin,b);
	cout<<"first  input ="<<a<<endl;
	cout<<"second input ="<<b<<endl;
	cout<<"first   length ="<<a.length()<<endl;
	cout<<"second  length ="<<b.length()<<endl;
	if(a==b){
		cout<<"they are same";
	}else{
		cout<<"they are different";
	}
}

