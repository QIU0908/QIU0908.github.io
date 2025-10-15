#include<iostream>
using namespace std;

double cebtigrade(double );

int main(void){
	float a;
		cin >>a;
		cout<<cebtigrade(a);
	return 0;
}

double cebtigrade(double f){
	float t;
		t=(5*f-160)/9;
	return t;
}