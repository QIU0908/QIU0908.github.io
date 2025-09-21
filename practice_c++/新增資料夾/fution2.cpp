#include<iostream>
using namespace std;

void square(int i);

int main(void){
	int n;
	cin>>n;
	square(n);
	return 0;
}

void square(int i){
	int squ;
	squ=i*i;
	cout<<squ;
	return ;
}