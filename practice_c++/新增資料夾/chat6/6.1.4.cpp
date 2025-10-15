#include<iostream>
using namespace std;

int cub(int  );
int main(void){
	
	int i;
	cin>>i;
	cout<<cub(i);
	
	
	return 0 ;
}
int cub(int x){
	return x*x*x;
}