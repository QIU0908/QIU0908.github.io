#include<iostream>
using namespace std;

void proverb(int);

int main(void){
	int i;
	cin>>i;
	proverb(i);
	return 0 ;
}

void proverb(int i){
	for(int j=0;j<i;j++)
	cout<<"live and learn";
	return  ;
}