#include<iostream>
using namespace std;

#define max 5

int main(void){
	int score[max];
	int i=0,num;
	float sum=0.0f;
	cout<<"if you imput number 0 is will stop"<<endl;
	do{
		if(i==max){
			cout<<"if enought"<<endl;
			break;
		}
	cout<<"input a number  ";
	cin>>score[i];	
	}while(score[i++]>0);
	cout<<"i = "<<i<<endl;
	num=i;
	for(i=0;i<num;i++){
	sum+=score[i];
	}
	cout<<"avg = "<<sum/num<<endl;
	return 0;	
}