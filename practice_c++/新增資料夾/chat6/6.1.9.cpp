#include<iostream>
using namespace std;

float power(float ,int );

int main(void){
	float ans=0;
		for(int i=1;i<=10;i++){
			ans=ans+power(0.5,i);
		}
	cout<<ans;
	return 0 ;
}

float power(float x,int n){
	float a=1.;
		for(int i=1;i<=n;i++){
		   a=a*x;      
		}
	return a;
}