#include<iostream>
using namespace std;

int main(void){
	int a[10];
	int b;
	for(int i=0;i<10;i++){
		cout<<&a[i]<<endl;
	}
	cout<<&b<<endl;
	int c=&b-a;
	cout<<c;
}