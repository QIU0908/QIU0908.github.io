#include<iostream>

using namespace std;

union Num{
	int a;
	float b;
};

int main(void){
	int swi;
	Num num;
	cout<<"(1) int \n"<<"(2) float \n";
	cin>>swi;
	
	if(swi==1){
		cin>>(num.a);
		cout<<(num.a)*(num.a);
	}else if(swi==2){
		cin>>(num.b);
		cout<<(num.b)*(num.b);
	}else{
		cout<<"error";
	}
	return 0;
}
