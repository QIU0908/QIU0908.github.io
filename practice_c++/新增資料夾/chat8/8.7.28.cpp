 #include<iostream>
#include<string>
using namespace std;
int main(void){
	int b;
	string a[4]={"spring","summer","autumn","winter"};
	
	cin>>b;
	if(b==3||b==4||b==5)
	cout<<a[0];
	else if(b==6||b==7||b==8)
	cout<<a[1];
	else if(b==9||b==10||b==11)
	cout<<a[2];
	else if(b==12||b==1||b==2)
	cout<<a[3];
	else
	cout<<"error";
}