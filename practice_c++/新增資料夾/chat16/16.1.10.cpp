#include<iostream>
using namespace std;
class Caaa{
	protected:
		int num;
	public:
		Caaa(){
			num=5;
		}
	
};

class Cbbb:protected Caaa{
	public:
		void show(){
			cout<<num<<endl;
		}
};

class Cccc:public Cbbb{
};

int main(void){
	Cccc c;
	c.show();
	return 0;
}