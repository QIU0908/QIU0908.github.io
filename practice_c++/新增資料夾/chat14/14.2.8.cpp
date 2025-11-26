#include<iostream>
using namespace std;
class Caaa{
	private:
		int m,n;
	public:
		
		Caaa(int m1,int n1):m(m1),n(n1){}
		void show(){
			cout<<"m= "<<m<<" n= "<<n<<endl;
		}
		
		Caaa(const Caaa &win){
			cout<<"call capy"<<endl;
			 m=win.m;
			 n=win.n;
		}
		
		~Caaa(){
			cout<<"call delete"<<endl;
			system("pause");
		}
};



int main(void){
	Caaa obj1(10,20);
	Caaa obj2=obj1;
	
	obj1.show();
	obj2.show();
	return 0;
}