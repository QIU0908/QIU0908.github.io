#include<iostream>
using namespace std;

int max(int ,int );
int max(int ,int ,int );

int main(void){
	int i=5,j=16,k=7;
	cout<<max(i,j,k)<<endl<<max(i,k);	
}

int max(int a,int b){
	if(b>a)
		a=b;	
	return a;
}

int max(int a,int b,int c){
	if(b>a)
		a=b;
	if(c>a)
		a=c;	
	return a;
}