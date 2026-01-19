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
	
	void display(){
		cout<<"print from Caaa class"<<endl;
	}
};

class Cbbb:public Caaa{
	public:
	void set_num(int a,int b){
		num1=a;
		num2=b;
	}
	void display(){
		cout<<"print from Cbbb class"<<endl;
	}
};

int main(void){
	Caaa obj1;
	Cbbb obj2;
	obj1.display();
	obj2.display();
}