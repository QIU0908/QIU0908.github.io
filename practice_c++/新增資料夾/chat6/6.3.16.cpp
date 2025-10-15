#include <iostream>
using namespace std;

static int km;

double miles(void);

int main(void){
	cin>>km;
	cout<<miles();
	return 0;
}

double miles(void){
	float miles;
	miles=1.6*km;
	return miles;
}