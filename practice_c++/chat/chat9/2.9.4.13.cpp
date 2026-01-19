#include<iostream>
using namespace std;

int main(void){
	int a[10];
	int* prt=a;
	double b=0;
	for(int i=0;i<10;i++){
		cin>>a[i];
	}
	for(int i=0;i<10;i++){
		b+=*(prt+i);
	}
	cout<<b<<"\t"<<b/10;
}
