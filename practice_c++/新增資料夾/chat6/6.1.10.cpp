#include<iostream>
using namespace std;

float power(float ,float ,int );

int main(void){
	float p,r,n;
	cin>>p>>r>>n;
	cout<<power(p,r,n);
	return 0 ;
}

float power(float p,float r,int n){
	
	float t=1,a=1;
		for(int i=1;i<=n;i++){
		   a=a*(1+r);      
		}
		t=p*a;
		
	return t;
}