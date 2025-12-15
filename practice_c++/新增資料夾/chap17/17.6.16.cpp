#include<iostream>
using namespace std;

int times(int a,int b){
	return a*b;
}

double times(double a,double b){
	return a*b;
}

int main(void){
	cout<<"times(3,4) ="<<times(3,4)<<endl;
	cout<<"times(3.6,4.6) ="<<times(3.6,4.6)<<endl;
	cout<<"times(3.1154,3.1169) ="<<times(3.1154,3.1169)<<endl;
	cout<<"times(3.3,4.4) ="<<times(3.3,4.4)<<endl;
}