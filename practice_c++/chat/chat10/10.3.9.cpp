#include<iostream>

using namespace std;

int main(void){
	int *a,*b;
	a=new int;
	cin>>a[0]>>a[1];
	cout<<a[0]<<"\t"<<a[1]<<endl;
	cout<<*a * *(a+1)<<endl;
	cout<<a[0]*a[1]<<endl;
	delete a;
	a=nullptr;
}