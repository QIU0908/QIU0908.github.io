#include<iostream>
using namespace std;

int &max(int&,int&);

int main(void){
	int i ,j;
	cin>>i>>j;
	cout<<max(i,j);
	
}


int &max(int&a,int&b){
	if(a>b)
		return a;
	else
		return b;
}