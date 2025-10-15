#include<iostream>
using namespace std;

int cot(int );

int main(void){
	int n;
	cin>>n;
	cout<<cot(n);
	
return 0;	
}

int cot(int n){
	
	if(n==1)
		return 1;
	else
		return(n+cot(n-1));
}
