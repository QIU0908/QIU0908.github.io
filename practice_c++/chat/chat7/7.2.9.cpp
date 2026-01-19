#include<iostream>
using namespace std;

int trapezoid(int ,int ,int );
double trapezoid(double ,double ,double );
	
int main(void){
	double i,j,k;
	cin>>i>>j>>k;
	cout<<trapezoid(i ,j ,k );
}

int trapezoid(int upper,int base,int height){
	int area;
	area=(upper+base)*height/2;
	return area;
}

double trapezoid(double upper,double base,double height){
	double area;
	area=(upper+base)*height/2;
	return area;
}