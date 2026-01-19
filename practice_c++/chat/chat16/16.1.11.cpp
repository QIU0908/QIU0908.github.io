#include<iostream>
using namespace std;
class Caaa{
	public:
		int num1,num2;
		Caaa(){
		num1=1;
		num2=1;
		}
		void show(){
			cout<<num1<<endl<<num2<<endl;
		}
};

class Cbbb:public Caaa{
	
};

int main(void){
	Cbbb obj;
	obj.show();
}