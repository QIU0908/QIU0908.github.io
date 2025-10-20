#include<iostream>
using namespace std;

void square(int *);

int main(void){
	int a[5]={1,2,3,4,5};
	for(int i=0;i<5;i++){
	cout<<a[i]<< " ";
	}
	cout<<endl;
	square(a);
	for(int i=0;i<5;i++){
	cout<<a[i]<< " ";
	}
}

void square(int *arr){
	for(int i=0;i<5;i++){
		*(arr+i)=*(arr+i)* *(arr+i);
	}
}