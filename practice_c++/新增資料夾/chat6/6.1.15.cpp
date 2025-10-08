#include<iostream>
using namespace std;

inline double f(double x){
	float f;
	f=3*x*x*x+2*x-1;
	return f;
}

int main(void){
	char b;
	do{
		float x;
		cin>>x;
		cout<<f(x)<<endl;
		cin>>b;
	}while(b != 'n');
	return 0;
	
}


