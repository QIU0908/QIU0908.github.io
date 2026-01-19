#include<iostream>
using namespace std;

template<typename t>
double times(t a,t b){
	return a*b;
}



int main(void){
	cout<<"times(3,4) ="<<times(3,4)<<endl;
	cout<<"times(3.6,4.6) ="<<times(3.6,4.6)<<endl;

}