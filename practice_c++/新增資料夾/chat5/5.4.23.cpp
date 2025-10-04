#include<iostream>
using namespace std;

int main(void){
	int i;
	bool jug=0;
	
	cin>>i;
	
	for(int j=2;j<i;j++){
		if(i%j==0){
			jug=1;
			continue;
			}
		}
		
		if(jug){
				cout<<"this is not a prime";
			}else{
				cout<<"this is  a prime";
			}
	
	}
