#include<iostream>
using namespace std;

int main(void){
	int i=0;
	do{
		i++;
		int j=1;
		do{
			cout<<i<<"*"<<j<<"="<<i*j<<endl;
			j++;
		}while(j<=9);
		
	}while(i<=9);
}