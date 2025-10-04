#include<iostream>
using namespace std;

bool primeQ(int );

int main(void){
	
	int i;
	
	for(int i=1;i<=100;i++){
		if(primeQ(i)){
			cout<<i<<endl;
		}
		
	}
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