#include<iostream>
using namespace std;
#define size 6
void reverse(char []);

int main(void){
	char a[size];
	cin.getline(a,size+1);
	reverse(a);
}

void reverse(char a[]){
	char b;
	for(int i=0;i<size/2;i++){
		b=a[size-1-i];
		a[size-1-i]=a[i];
		a[i]=b;
	}
	cout<<a;
}