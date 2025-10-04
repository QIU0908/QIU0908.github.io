#include<iostream>
using namespace std;

float power(float ,int );

int main(void){
	float x;
	int n;
	cin>>x>>n;
	cout<<power(x,n);
	return 0 ;
}
float power(float x,int n){
	int a=1;
	//x^n=x*x*x....;
	for(int i=1;i<=n;i++){
		a=a*x;
	}
	return a;
}