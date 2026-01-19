#include<iostream>
using namespace std;

float power(float ,int );
int fact(int );


int main(void){
	float x=0.1;
	float n=0.0;
	
	
	
	for(int i=1;i<=10;i++){
		n=n+(power(x,i)/fact(i));
	}
	cout<<n;
	
	return 0 ;
}

float power(float x,int n){
	float a=1;
	//x^n=x*x*x....;
	for(int i=1;i<=n;i++){
		a=a*x;
	}
	return a;
}

int fact(int n){
	if(n==0)
		return 1;
	else
		return(n*fact(n-1));
	
}