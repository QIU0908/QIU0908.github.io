#include<iostream>
using namespace std;

int* max(int* ,int * );

int main(void){
	int* prt,a=5,b=3;
	prt=max(&a,&b);//prt=&a||&b
	cout<<*prt;//*prt=a|b
}

int* max(int* i,int * j){
	if(*i > *j)
		return i;//i=&a
	else
		return j;
}