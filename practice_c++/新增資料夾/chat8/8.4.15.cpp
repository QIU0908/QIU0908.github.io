#include<iostream>
using namespace std;

#define size 26 

int main (void){
	char alphabet[size];
	for(int i=0;i<size;i++){
		alphabet[i]='A'+i;
		cout<<alphabet[i]<<" ";
		
	}	
}