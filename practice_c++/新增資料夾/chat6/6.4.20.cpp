#include<iostream>
using namespace std;

int fact(int);

int main(void){
	double ans=0;
	for(int i=1;i<=10;i++){
		ans=ans+(1.0f/fact(i));
	}
	cout<<"ans ="<<ans;
}

int fact(int n){
	if(n==1)
		return 1;
	else
		return(n*fact(n-1));
	
}