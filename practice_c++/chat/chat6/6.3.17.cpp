#include<iostream>
using namespace std;

int total(int );

int main(void){
	int n;
	cin>>n;
	cout<<total(n); 
}

int total(int n){
	static int sum;
	for(int i=1;i<=n;i++){
		sum=sum+i;
	}
	return sum;
}