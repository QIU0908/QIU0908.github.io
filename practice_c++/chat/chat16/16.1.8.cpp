#include<iostream>
using namespace std;
class Caaa{
	protected:
		int num;
	public:
		Caaa(){num=5;
		}
		
};

class Cbbb :public Caaa{
	public:
	void show(){
			cout<<num<<endl;
		}
};

int main(void){
	Cbbb b;
	b.show();
	return 0;
}