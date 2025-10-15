#include<iostream>
using namespace std;


void sum(int &,int&);

int main(void){
	int i,j;
	cin>>i>>j;
	sum(i,j);
	return 0;
}

void sum(int &a,int&b){
	a=a+b;
	cout<<a;
}