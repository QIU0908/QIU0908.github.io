#include<iostream>
using namespace std;

double minn(double ,double );
double minn(double ,double ,double );

int main(void){
		int i=5,j=16,k=7;
	cout<<minn(i,j,k)<<endl<<minn(i,k);
}

double minn(double a,double b){
	if(b<a)
		a=b;	
	return a;
}

double minn(double a,double b,double c){
	if(b<a)
		a=b;
	if(c<a)
		a=c;	
	return a;
}