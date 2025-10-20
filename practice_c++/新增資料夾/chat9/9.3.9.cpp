#include<iostream>
using namespace std;

double transit(int *);


int main(void){
	int a;
	cin>>a;
	cout<<transit(&a);
	
}

double transit(int *a){
	double b;
	b=*a*0.394;
	return b;
}