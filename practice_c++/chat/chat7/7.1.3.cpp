#include<iostream>
using namespace std;

double gcb(int &,int &,int &);


int main(void){
	int i,j,g=0;
	cin>>i>>j;
	cout<<gcb(i,j,g);
}

double gcb(int &a,int &b,int &g){
	int in=1;
	while(in!=0){
		in=a%b;
		a=b;
		b=in;
		
	}
	g=a;
	return g;
}




