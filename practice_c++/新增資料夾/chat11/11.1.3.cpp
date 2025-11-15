#include<iostream>
using namespace std;

struct Temperture{
	float f;
	float c;
}tem;

int main(void){
	int chose=0;
	cout<<"which do you want \n"<<"(1) f to c\n"<<"(2) c to f\n";
	cin>>chose;
	switch(chose){
		case 1: 
			cout<<"input f = ";
			cin>>tem.f;
			cout<<tem.f<<" f to c // c = "<<(5./9.)*tem.f-(160./9.);
			break;
		case 2: 
			cout<<"input c = ";
			cin>>tem.c;
			cout<<tem.c<<" c to f // f = "<<(9./5.)*tem.c+32;
			break;
		default:
			cout<<"error";
	}

}