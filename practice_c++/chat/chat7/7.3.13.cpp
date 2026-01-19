#include<iostream>
using namespace std;

double avg(int a,int b=5,int c=7);

int main(void){
	cout<<avg(13)<<endl;
	cout<<avg(9,16)<<endl;
	cout<<avg(8,17,3)<<endl;
}

double avg(int a,int b,int c){
	double ans;
	ans=(a+b+c)/3.0;
	return ans;
}