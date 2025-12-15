#include<iostream>
using namespace std;

template<typename t1,typename t2>
double times(t1 a,t2 b){
	return a*b;
}



int main(void){
	cout<<"times(3.7,4) ="<<times(3.7,4)<<endl;
	cout<<"times(3,4.2) ="<<times(3,4.2)<<endl;
	cout<<"times(3,4) ="<<times(3,4)<<endl;
}