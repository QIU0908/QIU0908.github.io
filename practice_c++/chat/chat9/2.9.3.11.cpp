#include<iostream>
using namespace std;

int* strd(int* ,int* ,int* );

int main (void){
	int a=23,b=2,c=6;
	cout<<a<<"\t"<<b<<"\t"<<c<<endl;
	cout<<*strd(&a, &b, &c);

	
}


int* strd(int* a,int* b,int* c){
	
	if(*a<*b&&*a<*c){return a;}
	if(*b<*a&&*b<*c){return b;}
	if(*c<*b&&*c<*a){return c;}
	else
	return 0;
}