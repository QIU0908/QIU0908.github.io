#include<iostream>
using namespace std;

float power(float ,int );

int main(void){
	float x;
	int n;
	cin>>x>>n;
	cout<<power(x,n);//x^n=x*x*x....;
	return 0;
}
/*
float power(float x ,int n){
	float a=1;
	for(int i=1;i<=n;i++){
		a=a*x;
	}
	return a;
}
*/
float power(float x ,int n){
	if(n==0)
		return 1;
	else
		return(x*(power(x,n-1)));
}