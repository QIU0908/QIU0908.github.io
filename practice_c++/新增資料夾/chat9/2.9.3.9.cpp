#include<iostream>
using namespace std;

double change(int* );

int main(void){
	int a;
	cin>>a;
	cout<<change(&a);
	
}

double change(int* a){
	double b;
	b=*a * 0.394;
	return b;
}