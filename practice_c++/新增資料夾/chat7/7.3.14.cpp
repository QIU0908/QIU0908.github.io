#include<iostream>
using namespace std;

double triangle(int base=2,int height=1);

int main(void){
	cout<<triangle()<<endl;
	cout<<triangle(10)<<endl;
	cout<<triangle(12,3)<<endl;
	
}

double triangle(int base,int height){
	double ans;
	ans=base*height/2.0;
	return ans;
}