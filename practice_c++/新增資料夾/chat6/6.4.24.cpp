#include<iostream>
using namespace std;
int fact(int );
int main(void){
	int n;
	cin>>n;
	int i=1;
	double sun=0;
	do{
		sun=sun+fact(i);
		i++;
	}while(i<=n);
	cout<<sun;
	return 0;
}
int fact(int a){
	if(a==1)
		return 1;
	else
		return(a*fact(a-1));
}