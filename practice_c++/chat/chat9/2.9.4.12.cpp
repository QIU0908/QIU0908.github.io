#include<iostream>
using namespace std;

int main(void){
	int a=5,b=3;
	int* ptr1=&a;
	int* ptr2=&b;
	
	cout<<*ptr1<<endl;
	
	*ptr1+=*ptr2;
	
	cout<<*ptr1;
}