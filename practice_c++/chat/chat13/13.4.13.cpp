#include<iostream>
using namespace std;
class Cwin{
	private :
		char id;
		int width, height;
		static int num;
	public:
		Cwin(char i,int w,int h):id(i),width(w),height(h){
			num++;
		}
		Cwin(){
			num++;
		}
		static void count(void);
};

void Cwin::count(void){
	cout<<"already create"<<num<<endl;
}

int Cwin::num=0;

int main(void){
	Cwin::count();
	
	Cwin c1('A',50,40);
	Cwin c2('B',60,80);
	
	Cwin::count();
	Cwin my_win[5];
	Cwin::count();
	
	return 0;
}