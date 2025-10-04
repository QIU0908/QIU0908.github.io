#include<iostream>
using namespace std;

void repeat(int);

int main(void){
	int i;
	cin>>i;
	repeat(i);
	return 0 ;
}

void repeat(int i){
	for(int j=0;j<i;j++)
	cout<<"Hello c++\n";
	return  ;
}