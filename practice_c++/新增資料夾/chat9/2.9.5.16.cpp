#include<iostream>
using namespace std;

void display(char* ,int );

int main(void){
	char* a="out of sight, out of mind";
	int n=14;
	
	display(a,n);
}

void display(char* prt,int n){
	do{
		cout<<*(prt+n);
		n++;
	}while(*(prt+n) != '\0');
	
}