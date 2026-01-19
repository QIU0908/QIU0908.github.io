#include<iostream>
using namespace std;
class Caaa{
	protected:
		int num;
	public:
		Caaa(){num=5;
		}
		void show(){
			cout<<num<<endl;
		}
};

class Cbbb :public Caaa{
};

int main(void){
	Cbbb b;
	b.show();
	return 0;
}