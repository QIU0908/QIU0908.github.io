#include<iostream>
using namespace std;

int power(int x=1,int n=1);

int main(void){
	cout<<power()<<endl<<power(5)\
	<<endl<<power(3,2);
}

int power(int x,int n){
	int ans=1;
	for(int i=1;i<=n;i++){
		ans=ans*x;
	}
	return ans;
}