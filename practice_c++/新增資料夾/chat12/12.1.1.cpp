#include<iostream>
using namespace std;

class caaa{
	public:
		int a;
		int b;
		int c;
};

int main(void){
	caaa obj;
	obj.a=1;
	obj.b=3;
	obj.c=obj.a+obj.b;
	cout<<obj.a<<endl<<obj.b<<endl<<obj.c<<endl;
}