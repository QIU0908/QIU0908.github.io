#include<iostream>
using namespace std;

#define size 26 

int main (void){
	char alphabet[size];
	int a;
	
	for(int i=0;i<size;i++){
		alphabet[i]='a'+i;
	
	}	
	cout<<endl<<"input 1 or 2 ";
	cin>>a;
	
	for(int i=0;i<size/2;i++){
	if(a==1){
		cout<<alphabet[2*i]<<" ";
	}
	else if(a==2){
		
		cout<<alphabet[2*i+1]<<" ";
	}else
	 cout<<" error "<<endl;
	}
}