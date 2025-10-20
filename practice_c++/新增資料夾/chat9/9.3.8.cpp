#include<iostream>
using namespace std;

void kam(int *,int *,int *);

int main(void){
	int a=8;
	int b=5;
	int c=16;
	cout<<a<<" "<<b<<" "<<c<<endl;
	kam(&a,&b,&c);
	
	cout<<a<<" "<<b<<" "<<c<<" ";
}

void kam(int *a,int *b,int *c){
	int t;
	if (*a < *b) { int t = *a; *a = *b; *b = t; }
    if (*a < *c) { int t = *a; *a = *c; *c = t; }
    if (*b < *c) { int t = *b; *b = *c; *c = t; }
}