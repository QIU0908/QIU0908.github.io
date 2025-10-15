#include<iostream>
using namespace std;

inline double cebtigrade(double f){
	float t;
		t=(5*f-160)/9;
	return t;
}
int main(void){
	float a;
		cin >>a;
		cout<<cebtigrade(a);
	return 0;
}

