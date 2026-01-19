#include<iostream>
using namespace std;
class Caaa{
	public:
		int num1,num2;
		Caaa(){
		num1=1;
		num2=1;
		}
		
		Caaa(int a,int b):num1(a),num2(b){
			
		}
		
		void show(){
			cout<<num1<<endl<<num2<<endl;
		}
};

class Cbbb:public Caaa{
	public:
		Cbbb(int a,int b):Caaa(a,b){
		}
};

int main(void){
	Cbbb obj(10,25);
	obj.show();
}