#include<iostream>
using namespace std;
class Caaa{
	private:
		int num;
	public:
		Caaa(int n=5):num(n){
		}
		
		void show(){
			cout<<num<<endl;
		}
		
		void set_num(int a=10){
			num=a;
		}
};

class Cbbb:public Caaa{
};

int main(){
	Cbbb b;
	b.set_num(10);
	b.show();
	return 0;
}