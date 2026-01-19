#include<iostream>
using namespace std;

double avg(int ,int ,int );
void show(int ,int ,int );

int main(void){
	int a,b,c;
	cin>>a>>b>>c;
	cout<<avg(a ,b ,c )<<endl;
	show(a ,b ,c);
	return 0;
}

double avg(int a,int b,int c){
	double n=0;
	n=(a+b+c)/3.0f;
	return n;
}

void show(int a,int b,int c){
	cout<<" a = "<<a<<" b = "<<b<<" c = "<<c<<endl;
	return ;
}