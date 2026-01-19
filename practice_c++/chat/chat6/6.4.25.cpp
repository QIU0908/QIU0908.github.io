#include<iostream>
using namespace std;


int fib(int );

int main(void){
	int n=48;
	cout<<fib(n);
}


int fib(int n){
	int a=1,b=1,c;
	
	for(int i=3;i<=n;i++){
		c=a+b;
		a=b;
		b=c;
	}
	return c;
}

/*
int fib(int n){
	
	if(n==1||n==2)
		return 1;
	else
		return(fib(n-1)+fib(n-2));
}
*/