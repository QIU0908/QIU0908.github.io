#include<iostream>
#include"head_math.h"
using namespace std;

int main(void){
	double i,j,k,r;
	cin>>i>>j>>k;
	cout<<TRAPEZOID(i,j,k)<<endl;
	cin>>r;
	cout<<PERIPHERY(r)<<endl<<VOLUMN(r);
	
	
return 0;
}
