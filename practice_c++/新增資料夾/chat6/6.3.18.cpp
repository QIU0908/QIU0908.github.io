#include<iostream>
using namespace std;

double miles(void);

float km;

int main(void){
	cin>>km;
	cout<<miles();
}

double miles(void){
	float miles;
	miles = km*1.6;
	return miles;
}