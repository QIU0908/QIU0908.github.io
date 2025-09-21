#include<iostream>
using namespace std;
int main(void){
	int n,i=1,sum=0;
	
	do{cout<<"give me a positive number ";
	cin>>n;
	}
	while(n<1||n%2==0);
	
	while(i<=n){
		sum+=i;
		i+=2;
	}
	cout<<"1+3+....+"<<n<<"="<<sum;
	return 0;
	
	
	
}