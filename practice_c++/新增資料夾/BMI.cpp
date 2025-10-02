#include<iostream>
using namespace std;

int main(void){
	float height,weight,bmi;
		cout<<"count out your BMI \n";
	
	cout<<"in put your height(m)\n";
	cin>>height;
	
	cout<<"in put your weight(kg)\n";
	cin>>weight;
	
	bmi=weight/(height*height);
	
	cout<<"your BMI are" <<bmi<<endl;
	
	if(bmi>24)
		cout<<"you are too fat";	
	else if(bmi<18.5)
		cout<<"you are too thin";
	else 
		cout<<"you are normal";
	return 0;
}