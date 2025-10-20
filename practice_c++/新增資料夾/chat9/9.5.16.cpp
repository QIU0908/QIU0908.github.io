#include<iostream>
using namespace std;

void display(const char**,int );

int main(void){
	const char *prt="out of sight, out of mind";
	int n=14;
	cout<<prt<<endl;
	display(&prt,n);
	cout<<prt;
}


void display(const char**prt,int n){
	*prt+=n;
}