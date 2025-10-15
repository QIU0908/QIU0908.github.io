#include<iostream>
using namespace std;

bool primeQ(int );

int main(void){
	
	int n;
	cin>>n;
	cout<<     primeQ(n);
	return 0 ;
}
bool primeQ(int n){
	for(int i=2;i<n;i++){
		if(n%i==0){
			return false;	
		}		
	}
	return true;
}