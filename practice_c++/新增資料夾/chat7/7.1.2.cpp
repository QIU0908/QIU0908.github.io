#include<iostream>
using namespace std;

void sort(int &,int&);

int main(void){
	int i,j;
	cin>>i>>j;
	sort(i,j);
	return 0;
	
}

void sort(int &a,int&b){
	if(a>=b)
		cout<<a<<"  "  <<b;
	else
		cout<<b<<"  "<<a;
	
}