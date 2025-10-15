#include<iostream>
using namespace std;

int power(int ,int );
double power(double ,int );

int main(void){
	double i;
	int j;
	cin>>i>>j;
	cout<<power(i,j);
	
}

int power(int x,int n){
	int a=1;
	for(int i=1;i<=n;i++){
		a=a*x;
	}
	return a;
}

double power(double x,int n){
	double a=1;
	for(int i=1;i<=n;i++){
		a=a*x;
	}
	return a;
}