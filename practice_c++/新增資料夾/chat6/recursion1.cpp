#include<iostream>
using namespace std;

int fan(int);
int pls(int );

int main(void){
	int a;
	cin>>a;
	cout<<fan(a)<<endl<<pls(a);
	
}

int fan(int a){
		if(a<=0)
			return 1;
		else
			return (a*fan(a-1));
	}
int pls(int a){
		if(a<=0)
			return 0;
		else
			return (a+pls(a-1));
	}