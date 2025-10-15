#include<iostream>
using namespace std;

int max (int a=10,int b=10);

int main(void){
	int i;
	cin>>i;
	cout<<max(i);	
}

int max (int a,int b){
	if(a>b)
		return a;
	else
		return b;
}