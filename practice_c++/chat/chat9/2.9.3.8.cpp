#include<iostream>
using namespace std;

void strd(int* ,int* ,int* );

int main (void){
	int a=8,b=5,c=16;
	cout<<a<<"\t"<<b<<"\t"<<c<<endl;
	strd(&a, &b, &c);
	cout<<a<<"\t"<<b<<"\t"<<c;
	
}


void strd(int* a,int* b,int* c){
	int temp;
	if(*b>*a){
		temp=*a;
		*a=*b;
		*b=temp;
	}
	if(*c>*a){
		temp=*a;
		*a=*c;
		*c=temp;
	}
	if(*c>*b){
		temp=*b;
		*b=*c;
		*c=temp;
	}
	return;
}