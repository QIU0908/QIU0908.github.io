#include<iostream>
#include<string>
using namespace std;
class Caaa{
	public:
		int num1,num2;
	Caaa(){
		num1=0;
		num2=0;
	}
	Caaa(int a,int b){
		num1=a;
		num2=b;
	}
	void show(){
		cout<<num1<<endl<<num2<<endl;
	}
};

class Cbbb:public Caaa{
	public:
	void set_num(int a,int b){
		num1=a;
		num2=b;
	}
};

int main(void){
	Caaa obj1;
	Caaa obj2(10,15);
	Cbbb obj3;
	obj3.set_num(10,20);
	obj1.show();
	obj2.show();
	obj3.show();
}