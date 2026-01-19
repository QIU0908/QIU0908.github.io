#include<iostream>
using namespace std;

void setvalue(int &,int&);

int main(void){
	int i,j;
	cin>>i>>j;
	setvalue(i,j);
	cout<<"i="<<i<<endl<<"j="<<j;
	
	
}

void setvalue(int &a,int&b){
	if(a>=b){
		a=10;
		b=100;
	}else{
		a=100;
		b=10;
	}
	return ;	
}