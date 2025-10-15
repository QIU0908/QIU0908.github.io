#include<iostream>
using namespace std;

void mod(int ,int );
int main(void){
	
	int i,j;
	cin>>i>>j;
	mod(i,j);
	return 0 ;
}
void mod(int x,int y){
	int a,b;
	a=x/y;
	b=x%y;
	cout<<a<<endl<<b;
	return ;
}