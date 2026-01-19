#include<iostream>
using namespace std;

struct Squbody{
	float high;
	float wide;
	float Long;
};

float Wbody(Squbody );

int main(){
	Squbody squ;
	cin>>squ.high>>squ.Long>>squ.wide;
	cout<<Wbody(squ);
}

float Wbody(Squbody a){
	float all=a.high*a.Long*a.wide;
	return all;
	
}