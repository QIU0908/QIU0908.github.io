#include<iostream>
using namespace std;


int main(void){
	int a=5,b=3;
	int *ptr1,*ptr2;
	ptr1=&a;
	ptr2=&b;
	*ptr1+=*ptr2;
	
	cout<<*ptr1;
}

