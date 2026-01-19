#include<iostream>
using namespace std;
class Cwin{
	private:
		char id;
		int width,height;
	public:
		Cwin(char i,int w,int h):id(i),width(w),height(h){
			cout<<"hi my man"<<endl;
		}
		
		~Cwin();
		
		void show_member(void){
			cout<<"Window "<<id<<": ";
			cout<<"width= "<<width <<" ,height= "<<height<<endl;
		}
	
};

Cwin::~Cwin(void){
	cout<<"hi"<<endl;
	system("pause");
} 

int main(void){
	Cwin win1('A',50,40);
	Cwin win2('B',40,50);
	Cwin win3('C',60,70);
	Cwin win4('D',90,40);
	
	win1.show_member();
	win2.show_member();
	return 0;
}