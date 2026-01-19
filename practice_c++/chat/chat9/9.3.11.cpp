#include<iostream>
using namespace std;

int min(int *,int *,int *);


int main(void){
	int a=23,b=2,c=6;
	cout<<min(&a,&b,&c);
}

int min(int *a,int *b,int *c){
	if(*a<*b&&*a<*c)
		return *a;
	else if(*b<*a&&*b<*c)
		return *b;
	else
		return *c;		
	
}