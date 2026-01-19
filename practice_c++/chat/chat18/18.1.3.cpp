#include<iostream>
using namespace std;

void division(double n,double d){
	
	try{
		if(d==0){
			throw " Denominator equare zero";
		}else{
			cout<<n<<"/"<<d<<"="<<n/d<<endl;
		}	
	}
	catch(const char *str){
		cout<<n<<"/"<<d<<" error"<< str <<endl;
	}
}
int main(void){
	division(3.,6);
	division(5.,0.);
}