#include<iostream>
using namespace std;

class Calculator{
	public:
		float a;
		float b;
		
		float add(void){
			return a+b;
		}
		float sub(void){
			return a-b;
		}
		float mul(void){
			return a*b;
		}
		float div(void){
			return a/b;
		}	
};

int main(void){
	Calculator c;
	cin>>c.a>>c.b;
	cout<<c.add()<<endl<<c.sub()<<endl<<c.mul()<<endl<<c.div()<<endl;
}


